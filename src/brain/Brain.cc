/*
 * Brain.cc
 *
 *  Created on: May 15, 2014
 *      Author: Andreea
 */

#include <vector>
#include <random>

#include "Neuron.h"
#include "Brain.h"


using std::vector;

void Brain::give_input(const vector<bool> &input_vals) {
	if (input_vals.size() != num_input_neurons_) {
		std:cerr << std::endl << "Error! Number of input neurons is not the same as number of input signal bits!\n";
	}
	for (int i = 0; i < num_input_neurons_; i++) 		//the first few neurons are input
		neurons_[i].set_activation(input_vals[i] * MAX_ACTIVATION);
}

vector<bool> Brain::get_output() const {
	vector<bool> output;
	output.reserve(num_output_neurons_);
	for (int i = num_output_neurons_; i < num_input_neurons_ + num_output_neurons_; i++) 		//output neurons are the one coming after the input ones
		output.push_back(neurons_[i].get_activation() > neurons_[i].get_activ_treshold());		//return 1 of activation > threshold, and 0 else
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

void Brain::Cycle() {	//TODO
}


