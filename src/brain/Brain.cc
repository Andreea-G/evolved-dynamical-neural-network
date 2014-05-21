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

Brain::Brain(const int num_neurons, const int num_input_neurons, const int num_output_neurons) {
	num_neurons_ = num_neurons;
	num_input_neurons_ = num_input_neurons;
	num_output_neurons_ = num_output_neurons;
	fitness_score_ = 0;

	for (int ii = 0; ii < num_neurons; ii++) {
		Neuron new_neuron(num_neurons);
		neurons_.push_back(new_neuron);
	}
}

Brain::Brain(const int num_neurons, const int num_input_neurons, const int num_output_neurons, const int av_num_syn,
			const float av_syn_strength, const float av_active_threshold, const float av_start_activation) {
	//TODO: implement this.  For randomizing the floats, we could use Gaussian and use std::max/std::min to make sure it doesn't
	//go out of bounds.  The other option is a Beta distribution, but we'd have to rely on someone else's code.


}

//TODO: get rid of this.  No need to explicitly write out the implicit copy constructor
/*Brain::Brain(const Brain &br) : neurons_(br.neurons_) {
	num_neurons_ = br.num_neurons_;
	num_input_neurons_ = br.num_input_neurons_; num_output_neurons_ = br.num_output_neurons_;
	fitness_score_ = br.fitness_score_;
}*/

void Brain::give_input(const deque<bool> &input_vals) {
	if (input_vals.size() != num_input_neurons_) {
		std::cerr << std::endl << "Error! Number of input neurons is not the same \
																as number of input signal bits!\n";
	}
	for (int i = 0; i < num_input_neurons_; i++) 		//the first few neurons are input
		neurons_[i].set_activation(input_vals[i] * MAX_ACTIVATION);
}


deque<bool> Brain::get_output() const {
	deque<bool> output;
	//output neurons are the one coming after the input ones
	for (int i = num_output_neurons_; i < num_input_neurons_ + num_output_neurons_; i++)
		//return 1 of activation > threshold, and 0 else
		output.push_back(neurons_[i].ActivationFunction());
	return output;
}


void Brain::MutateNeurons(const int num_mutated_neurons, const int num_mutated_synapses) {
	std::random_device generator;
	std::uniform_int_distribution<int> neuron_distro(0, num_neurons_);
	std::uniform_real_distribution<> unit_distro(0, 1);	//returns number from 0 to 1

	for (int i = 0; i < num_mutated_neurons; i++) {
		Neuron rand_neuron = neurons_[neuron_distro(generator)];
		rand_neuron.set_decay_rate(MAX_DECAY_RATE * unit_distro(generator));
		rand_neuron.set_active_threshold(MAX_ACTIVATION * unit_distro(generator));
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


