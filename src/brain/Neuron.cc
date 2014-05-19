/*
 * Neuron.cc
 *
 *  Created on: May 15, 2014
 *      Author: Andreea
 */

#include <random>

#include "Neuron.h"

using std::unordered_map;
using std::list;

Neuron::Neuron(const int &num_neurons) {
	activation_ = 0; new_activation_ = 0; 
	std::random_device generator;
	std::uniform_float_distribution<float> unit_distro(0, 1);
	std::uniform_int_distribution<int> neuron_distro(0, num_neurons);
	decay_rate_ = MAX_DECAY_RATE * unit_distro(generator);
	activ_threshold_ = MAX_ACTIVATION * unit_distro(generator);
	int num_synapses = neuron_distro(generator);
	for (int i = 0; i < num_synapses; i++) {
		int orig_neuron = neuron_distro(generator);
		synapses_[neuron_distro(generator)] = MAX_STRENGTH * unit_distro(generator);
	}
}

Neuron::Neuron(const Neuron &neur) : synapses_(neur_.synapses_) {
	activation_ = neur.activation_;
	new_activation_ = neur.new_activation_; 
	decay_rate_ = neur.decay_rate_;
	activ_threshold_ = neur.activ_threshold_;
}

void Neuron::MutateSynapses(const int &num_mutated_synapses, const int &num_neurons) {
	std::random_device generator;
	std::uniform_int_distribution<int> neuron_distro(0, num_neurons);
	std::uniform_float_distribution<float> strength_distro(0, MAX_STRENGTH);

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
		unordered_map<int, float>::iterator syn_it = synapses_.begin();	//loop though existing synapses
		int syn_location = 0;	//location of corresponding synapse in the synapses map
		for (list<int>::iterator rand_loc_it = rand_synapse_locations.begin(); rand_loc_it != rand_synapse_locations.end(); rand_loc_it++) {
			while (syn_location != *rand_loc_it && syn_location < synapses_.size()) {
				syn_location++;	syn_it++;
			}
			if (syn_location == *rand_loc_it) {
				unordered_map<int, float>::iterator old_it = syn_it;
				syn_location++; syn_it++;
				synapses_.erase(old_it);
			}
		}
	}
}

void Neuron::Cycle() {	
	if (decay_rate_ < TIME_STEP) 
		new_activation_ = 0;
	else 
		new_activation_ = activation_ * (1 - TIME_STEP/decay_rate_);	
	for (unordered_map<int, float>::iterator syn_it = synapses_.begin(); syn_it != synapses_.end(); syn_it++) {
		int origin_neuron = syn_it->first(); 
		float syn_strength = syn_it->second();
		new_activation_ = TIME_STEP * syn_strength * neurons_[origin_neuron].ActivationFunction();
		if (new_activation > MAX_ACTIVATION) new_activation = MAX_ACTIVATION;
	}
}




