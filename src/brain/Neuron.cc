/*
 * Neuron.cc
 *
 *  Created on: May 15, 2014
 *      Author: Andreea
 */

#include <vector>
#include <random>

#include "Neuron.h"

using std::vector;
using std::unordered_map;

void Neuron::MutateSynapses(const int &num_mutated_synapses, const int &num_neurons) {
	std::random_device generator;
	std::uniform_int_distribution<int> neuron_distro(0, num_neurons);
	std::uniform_int_distribution<int> strength_distro(0, MAX_STRENGTH);

	if (num_mutated_synapses > 0) {		// add synapses
		for (int i = 0; i < num_mutated_synapses; i++) {
			int rand_neuron_id = neuron_distro(generator);
			int rand_strength = strength_distro(generator);
			synapses_[rand_neuron_id] = rand_strength;
		}
	}
	else if (num_mutated_synapses < 0) {	//delete synapses
		int orig_size = synapses_.size();
		if (-num_mutated_synapses > orig_size)		//clear all synapses
			synapses_.clear();
		else {				//make a vector of random synapse positions in the unsorted_map which will then be deleted
			std::uniform_int_distribution<int> synapse_location_distro(0, orig_size);		
			vector<int> rand_synapse_locations(-num_mutated_synapses, synapse_location_distro(generator));	//TODO erm... not a clue if this will work..
			unordered_map<int, int>::iterator iter = synapses_.begin();
			for (int location = 0; location < orig_size; location++) {
				if (location == rand_synapse_locations) synapses_.erase(iter);
				iter++;		//TODO make sure this doesn't give an error after the synapse element has been deleted...
			}
		}
	}


}
