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
using std::list;

void Neuron::MutateSynapses(const int &num_mutated_synapses, const int &num_neurons) {
	std::random_device generator;
	std::uniform_int_distribution<int> neuron_distro(0, num_neurons);
	std::uniform_int_distribution<float> strength_distro(0, MAX_STRENGTH);

	if (num_mutated_synapses > 0) {		//add synapses
		//At most num_mutated_synapses will be added (could be less if there are duplicates; in that case the corresponding synapse strength is changed to a random value).
		for (int i = 0; i < num_mutated_synapses; i++) {
			int rand_neuron_id = neuron_distro(generator);
			synapses_[rand_neuron_id] = strength_distro(generator);
		}
	}
	else if (num_mutated_synapses < 0) {	//delete synapses
		int original_size = synapses_.size();
		num_mutated_synapses = -num_mutated_synapses;	//make it positive
		//Make a list of random synapse locations such that corresponding synapses in the unsorted_map will be deleted. 
		//The list will be sorted and duplicate values removed. This means that at most num_mutated_synapses will be removed (could be less if there are duplicates).
		std::uniform_int_distribution<int> synapse_location_distro(0, original_size);		
		list<int> rand_synapse_locations(num_mutated_synapses, synapse_location_distro(generator));	//TODO erm... not a clue if this will work.. Make sure the generator is called every time, and different random values are passed to each element of the list!!
		rand_synapse_locations.sort();
		rand_synapse_locations.unique();
		//Loop through synapses and delete synapses matching the random locations above
		unordered_map<int, float>::iterator syn_iter = synapses_.begin();	//loop though existing synapses
		int syn_location = 0;	//location of corresponding synapse in the synapses map
		for (list<int>::iterator rand_loc_iter = rand_synapse_locations.begin(); rand_loc_iter != rand_synapse_locations.end(); rand_loc_iter++) {
			while (syn_location != *rand_loc_iter && syn_location < synapses_.size()) {
				syn_location++;	syn_iter++;
			}
			if (syn_location == *rand_loc_iter) {
				unordered_map<int, float>::iterator old_iter = syn_iter;
				syn_location++; syn_iter++;
				synapses_.erase(old_iter);
			}
		}
	}
}

//Friend funcion of Neuron class. Decides if activation is above threshold, in order for the neuron to fire.
bool ActivationFunction(const Neuron &neur) {
	return (neur.activation_ > neur.activ_threshold);
}

void Neuron::Cycle() {	
	new_activation_ = activation_ * (1 - TIME_STEP/decay_rate_);		//TODO check if decay_rate_ < TIME_STEP! 
	for (unordered_map<int, float>::iterator syn_iter = synapses_.begin(); syn_iter != synapses_.end(); syn_iter++) {
		int origin_neuron = (*syn_iter).first(); 
		float syn_strength = (*syn_iter).second();
		new_activation_ = TIME_STEP * syn_strength * ActivationFunction(neurons_[origin_neuron]);
	}
}




