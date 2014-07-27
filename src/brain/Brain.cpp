/*
 *	Brain.cc
 *
 *	Created on: May 15, 2014
 *	Author: Andreea
 */

#include <deque>
#include <random>
#include <iostream>

//project-specific headers
#include <src/brain/Neuron.hpp>
#include <src/brain/Brain.hpp>
#include <src/Globals.hpp>


using std::deque;
using std::random_device;
using std::normal_distribution;
using std::min;
using std::max;
using std::size_t;

Brain::Brain(const size_t num_neurons, const size_t num_input_neurons,
						 const size_t num_output_neurons) {
	num_neurons_ = num_neurons;
	num_input_neurons_ = num_input_neurons;
	num_output_neurons_ = num_output_neurons;
	fitness_score_ = 0;

	for (size_t ii = 0; ii < num_neurons; ii++) {
		Neuron new_neuron(num_neurons);
		neurons_.push_back(new_neuron);
	}
}

Brain::Brain(const size_t num_neurons, const size_t num_input_neurons, const size_t num_output_neurons,
						 const float av_active_threshold, const float st_dev_active_threshold,
						 const float av_start_activation, const float st_dev_start_activation,
						 const float av_decay_rate, const float st_dev_decay_rate,
						 const int av_num_syn, const int st_dev_num_syn,
						 const float av_syn_strength, const float st_dev_syn_strength) {
	num_neurons_ = num_neurons;
	num_input_neurons_ = num_input_neurons;
	num_output_neurons_ = num_output_neurons;
	fitness_score_ = 0;

	normal_distribution<float> num_syn_distro(av_num_syn, st_dev_num_syn);
	normal_distribution<float> active_threshold_distro(av_active_threshold, st_dev_active_threshold);
	normal_distribution<float> start_activation_distro(av_start_activation, st_dev_start_activation);
	normal_distribution<float> decay_rate_distro(av_decay_rate, st_dev_decay_rate);

	//loop to create each neuron
	for (size_t ii = 0; ii < num_neurons; ii++) {
		//generate number of synapses for current neuron, make sure it's in interval [0, num_neurons]
		int num_syn = min(max( static_cast<size_t>(num_syn_distro(globals::gen)) , static_cast<size_t>(0)), num_neurons);
		//generate active threshold
		float active_threshold = min(max(active_threshold_distro(globals::gen), globals::MIN_ACTIVATION), globals::MAX_ACTIVATION);
		//generate start activation
		float start_activation = min(max(start_activation_distro(globals::gen), globals::MIN_ACTIVATION), globals::MAX_ACTIVATION);
		//generate decay rate
		float decay_rate = min(max(decay_rate_distro(globals::gen), globals::MIN_DECAY_RATE), globals::MAX_DECAY_RATE);

		Neuron new_neuron(start_activation, decay_rate, active_threshold, num_neurons, num_syn,
						  av_syn_strength, st_dev_syn_strength);
		neurons_.push_back(new_neuron);
	}

}

//TODO add exception handling for neurons going out of range.
void Brain::give_input(const deque<bool> &input_vals) {
	if (input_vals.size() != num_input_neurons_)
		std::cerr << "\nError! Number of input neurons is not the same as number of input signal bits!\n" << std::endl;

	for (size_t i = 0; i < num_input_neurons_; i++) 		//the first few neurons are input
		neurons_.at(i).set_activation(input_vals[i] * globals::MAX_ACTIVATION);
}


deque<bool> Brain::get_output() const {
	deque<bool> output;
	//output neurons are the ones coming after the input ones
	for (size_t i = num_input_neurons_; i < num_input_neurons_ + num_output_neurons_; i++)
		//return 1 if activation is greater than threshold, and 0 otherwise
		output.push_back(neurons_.at(i).ActivationFunction());
	return output;
}


void Brain::MutateNeurons(const int num_mutated_neurons, const int num_mutated_synapses,
													const bool mutate_decay_rate, const bool mutate_active_threshold) {
	std::uniform_int_distribution<int> neuron_distro(0, num_neurons_-1);
	std::uniform_real_distribution<> unit_distro(0, 1);

	for (int i = 0; i < num_mutated_neurons; i++) {
		//Randomly pick a neuron
		//(it's possible a neuron could get mutated twice in a small brain, so losing 2x the synapses for example)
		Neuron & rand_neuron = neurons_[neuron_distro(globals::gen)];
		if (mutate_decay_rate) {
			//generate random decay rate using uniform distribution over [MIN_ACTIVATION, MAX_ACTIVATION]
			rand_neuron.set_decay_rate((globals::MAX_DECAY_RATE - globals::MIN_DECAY_RATE) * unit_distro(globals::gen) + globals::MIN_DECAY_RATE);
		}

		if (mutate_active_threshold) {
			//generate random activation using uniform distribution over [MIN_ACTIVATION, MAX_ACTIVATION]
			rand_neuron.set_active_threshold((globals::MAX_ACTIVATION - globals::MIN_ACTIVATION) * unit_distro(globals::gen) + globals::MIN_ACTIVATION);
		}

		rand_neuron.MutateSynapses(num_mutated_synapses, num_neurons_);
	}
}


void Brain::Cycle() {
	//iterator type for our deque
//	typedef std::deque<Neuron>::iterator neur_it_type;  DEL
	//iterator type for synapses
//	typedef std::unordered_map<int, float>::iterator syn_it_type;  DEL

	//loop through neurons to see which are firing this round
	for (auto neur_activate_it = neurons_.begin(); neur_activate_it != neurons_.end(); ++neur_activate_it) {
		neur_activate_it->AttemptToActivate();
	}

	//Loop through neurons calculating the new activation
	for (auto neur_it = neurons_.begin(); neur_it != neurons_.end(); ++neur_it) {
		//Neuron's activation decays exponentially, but cannot go into the negative.
		float new_activation = std::max(neur_it->get_activation() * (1-globals::TIME_STEP*neur_it->get_decay_rate()), 0.f);

		neur_it->synapses_.begin();

		//Loop through every (incoming) synapse linked to current neuron.
		for (auto syn_it = neur_it->synapses_.begin(); syn_it != neur_it->synapses_.end(); ++syn_it) {
			int origin_neuron = syn_it->first;
			float syn_strength = syn_it->second;
			//add influence of this synapse to current neuron
			new_activation += globals::TIME_STEP * syn_strength * neurons_[origin_neuron].just_fired;
		}

		//save new activation, but limit it to MAX_ACTIVATION
		neur_it->set_new_activation(min(new_activation, globals::MAX_ACTIVATION));
	}

	//then update all activations of the neurons
	for (auto neur_update_it = neurons_.begin(); neur_update_it != neurons_.end(); ++neur_update_it) {
		neur_update_it->UpdateActivation();
	}
}


void Brain::ResetStartActivations(const float av_start_activation, const float st_dev_start_activation) {

	normal_distribution<float> start_activation_distro(av_start_activation, st_dev_start_activation);

	//loop to reset each neuron
	for (auto neuron_it = neurons_.begin(); neuron_it != neurons_.end(); neuron_it++) {
		//generate start activation
		float start_activation = min(max(start_activation_distro(globals::gen), globals::MIN_ACTIVATION), globals::MAX_ACTIVATION);

		neuron_it->set_activation(start_activation);
		//neuron_it->set_new_activation(0); //TODO:  I'm pretty sure this is unnecessary..
	}
}
