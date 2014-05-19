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

Brain::Brain(const Brain &br) : neurons_(br.neurons_) {
	num_neurons_ = br.num_neurons_;
	num_input_neurons_ = br.num_input_neurons_; num_output_neurons_ = br.num_output_neurons_;
	fitness_score_ = br.fitness_score_;
}

void Brain::give_input(const deque<bool> &input_vals) {
	if (input_vals.size() != num_input_neurons_) {
		std::cerr << std::endl << "Error! Number of input neurons is not the same as number of input signal bits!\n";
	}
	for (int i = 0; i < num_input_neurons_; i++) 		//the first few neurons are input
		neurons_[i].set_activation(input_vals[i] * MAX_ACTIVATION);
}

deque<bool> Brain::get_output() const {
	deque<bool> output;
	for (int i = num_output_neurons_; i < num_input_neurons_ + num_output_neurons_; i++) 		//output neurons are the one coming after the input ones
		output.push_back(neurons_[i].ActivationFunction());		//return 1 of activation > threshold, and 0 else
	return output;
}

void Brain::MutateSynapses(const int &num_mutated_neurons, const int &num_mutated_synapses) {
	std::random_device generator;
	std::uniform_int_distribution<int> neuron_distro(0, num_neurons_);
	for (int i = 0; i < num_mutated_neurons; i++) {
		Neuron rand_neuron = neurons_[neuron_distro(generator)];
		rand_neuron.MutateSynapses(num_mutated_synapses, num_neurons_);
	}
}

void Brain::Cycle() {
	//First calculate the new activation
	for (int neur_it = neurons_.begin(); neur_it != neurons_.end(); neur_it++) {
		neur_it->Cycle();
	}
	//then update all activations of the neurons
	for (int neur_it = neurons_.begin(); neur_it != neurons_.end(); neur_it++) {
		neur_it.update_activation();
	}
}


