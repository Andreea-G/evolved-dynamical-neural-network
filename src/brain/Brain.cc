/*
 * Brain.cc
 *
 *  Created on: May 15, 2014
 *      Author: Andreea
 */

#include <deque>
#include <random>
#include <iostream>

#include "Neuron.h"
#include "Brain.h"


using std::deque;
using std::random_device;
using std::normal_distribution;
using std::min;
using std::max;
using std::size_t;

Brain::Brain(const int num_neurons, const size_t num_input_neurons,
						 const size_t num_output_neurons) {
	num_neurons_ = num_neurons;
	num_input_neurons_ = num_input_neurons;
	num_output_neurons_ = num_output_neurons;
	fitness_score_ = 0;

	for (int ii = 0; ii < num_neurons; ii++) {
		Neuron new_neuron(num_neurons);
		neurons_.push_back(new_neuron);
	}
}

Brain::Brain(const int num_neurons, const size_t num_input_neurons, const size_t num_output_neurons,
						 const int av_num_syn, const int st_dev_num_syn,
						 const float av_active_threshold, const float st_dev_active_threshold,
						 const float av_start_activation, const float st_dev_start_activation,
						 const float av_decay_rate, const float st_dev_decay_rate) {
	//TODO: implement this.  For randomizing the floats, we could use Gaussian and use std::max/std::min to make sure it doesn't
	//go out of bounds.  The other option is a Beta distribution, but we'd have to rely on someone else's code.
		num_neurons_ = num_neurons;
		num_input_neurons_ = num_input_neurons;
		num_output_neurons_ = num_output_neurons;

		random_device gen;
		normal_distribution<float> num_syn_distro(av_num_syn, st_dev_num_syn);
		normal_distribution<float> active_threshold_distro(av_active_threshold, st_dev_active_threshold);
		normal_distribution<float> start_activation_distro(av_start_activation, st_dev_start_activation);
		normal_distribution<float> decay_rate_distro(av_decay_rate, st_dev_decay_rate);

		//loop to create each neuron
		for (int ii = 0; ii < num_neurons; ii++) {
			//generate number of synapses for current neuron, make sure it's in interval [0, num_neurons]
			int num_syn = min(max( static_cast<int>(num_syn_distro(gen)) , 0), num_neurons);
			//generate active threshold
			float active_threshold = min(max(active_threshold_distro(gen), MIN_ACTIVATION), MAX_ACTIVATION);
			//generate start activation
			float start_activation = min(max(start_activation_distro(gen), MIN_ACTIVATION), MAX_ACTIVATION);
			//generate decay rate
			float decay_rate = min(max(decay_rate_distro(gen), MIN_DECAY_RATE), MAX_DECAY_RATE);

			Neuron neuron_ii(start_activation, decay_rate, active_threshold, num_neurons, num_syn);
		}

}


void Brain::give_input(const deque<bool> &input_vals) {
	if (input_vals.size() != num_input_neurons_) {
		std::cerr << "\nError! Number of input neurons is not the same as number of input signal bits!\n" << std::endl;
	}
	for (size_t i = 0; i < num_input_neurons_; i++) 		//the first few neurons are input
		neurons_[i].set_activation(input_vals[i] * MAX_ACTIVATION);
}


deque<bool> Brain::get_output() const {
	deque<bool> output;
	//output neurons are the ones coming after the input ones
	for (size_t i = num_output_neurons_; i < num_input_neurons_ + num_output_neurons_; i++)
		//return 1 if activation is greater than threshold, and 0 otherwise
		output.push_back(neurons_[i].ActivationFunction());
	return output;
}


void Brain::MutateNeurons(const int num_mutated_neurons, const int num_mutated_synapses) {
	random_device generator;
	std::uniform_int_distribution<int> neuron_distro(0, num_neurons_);
	std::uniform_real_distribution<> unit_distro(0, 1);	//returns number from 0 to 1

	for (int i = 0; i < num_mutated_neurons; i++) {
		Neuron rand_neuron = neurons_[neuron_distro(generator)];  //TODO: Possible bug, shouldn't we pass by reference, not invoke copy assignment here?
		rand_neuron.set_decay_rate(MAX_DECAY_RATE * unit_distro(generator));

		//generate random activation using uniform distribution over [MIN_ACTIVATION, MAX_ACTIVATION].
		rand_neuron.set_active_threshold((MAX_ACTIVATION - MIN_ACTIVATION) * unit_distro(generator) - MIN_ACTIVATION);
		rand_neuron.MutateSynapses(num_mutated_synapses, num_neurons_);
	}
}


void Brain::Cycle() {
	//iterator type for our vector
	typedef std::deque<Neuron>::iterator neur_it_type;
	//iterator type for synapses
	typedef std::unordered_map<int, float>::iterator syn_it_type;

	//First calculate the new activation
	for (neur_it_type neur_it = neurons_.begin(); neur_it != neurons_.end(); ++neur_it) {
		//Neuron's activation decays exponentially, but cannot go into the negative.
		float new_activation = std::max(neur_it->get_activation() * (1-TIME_STEP/neur_it->get_decay_rate()), 0.f);

		neur_it->synapses_.begin();
		neur_it->synapses_.begin();

		//Loop through every (incoming) synapse linked to current neuron.
		for (syn_it_type syn_it = neur_it->synapses_.begin(); syn_it != neur_it->synapses_.end(); ++syn_it) {
			int origin_neuron = syn_it->first;
			float syn_strength = syn_it->second;
			//add influence of this synapse to current neuron
			new_activation += TIME_STEP * syn_strength * neurons_[origin_neuron].ActivationFunction();
		}

		//save new activation, but limit it to MAX_ACTIVATION
		neur_it->set_activation(std::min(new_activation, MAX_ACTIVATION));
	}

	//then update all activations of the neurons
	for (neur_it_type neur_it = neurons_.begin(); neur_it != neurons_.end(); ++neur_it) {
		neur_it->update_activation();
	}
}


