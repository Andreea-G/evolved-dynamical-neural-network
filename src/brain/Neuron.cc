/*
 * Neuron.cc
 *
 *  Created on: May 15, 2014
 *      Author: Andreea
 */

#include <random>
#include <list>

#include "Neuron.h"

using std::unordered_map;
using std::list;
using std::random_device;
using std::uniform_real_distribution;
using std::uniform_int_distribution;
using std::size_t;

Neuron::Neuron(const int num_neurons) {
	activation_ = 0; new_activation_ = 0;

	random_device generator;
	uniform_real_distribution<> unit_distro(0, 1);
	uniform_int_distribution<int> neuron_distro(0, num_neurons);

	decay_rate_ = MAX_DECAY_RATE * unit_distro(generator);
	active_threshold_ = (MAX_ACTIVATION - MIN_ACTIVATION) * unit_distro(generator) - MIN_ACTIVATION;

	int num_synapses = neuron_distro(generator);
	//Loop through each synapse assigning random strength and origin neuron
	for (int i = 0; i < num_synapses; i++) {
		//get random origin  (where synapse comes from)
		int origin_neuron = neuron_distro(generator);
		synapses_[origin_neuron] = MAX_STRENGTH * unit_distro(generator);
	}
}

Neuron::Neuron(const float start_activation, const float decay_rate, const float active_threshold,
					const int num_neurons, const int num_synapses) {
	activation_ = start_activation;
	new_activation_ = 0;
	decay_rate_ = decay_rate;
	active_threshold_ = active_threshold;

	random_device generator;
	uniform_real_distribution<> unit_distro(0, 1);
	uniform_int_distribution<int> neuron_distro(0, num_neurons);

	//Loop through each synapse assigning random strength and origin neuron
	for (int i = 0; i < num_synapses; i++) {
		//get random origin neuron (where synapse comes from)
		int origin_neuron = neuron_distro(generator);
		synapses_[origin_neuron] = MAX_STRENGTH * unit_distro(generator);
	}
}


void Neuron::MutateSynapses(int num_mutated_synapses, const int num_neurons) {
	random_device generator;
	uniform_int_distribution<int> neuron_distro(0, num_neurons);
	uniform_real_distribution<float> strength_distro(MIN_STRENGTH, MAX_STRENGTH);

	if (num_mutated_synapses > 0) {		//add synapses
		//At most num_mutated_synapses will be added (could be less if there are duplicates;
		//in that case the corresponding synapse strength is changed to a random value).
		for (int ii = 0; ii < num_mutated_synapses; ii++) {
			int rand_neuron_id = neuron_distro(generator);
			synapses_[rand_neuron_id] = strength_distro(generator);
		}
	}
	else if (num_mutated_synapses < 0) {	//delete synapses
		size_t original_size = synapses_.size();
		num_mutated_synapses *= -1;	//make it positive
		//Make a list of random synapse locations such that corresponding synapses in the unsorted_map will be deleted.
		//The list will be sorted and duplicate values removed. This means that at most num_mutated_synapses will be removed
		//(could be less if there are duplicates).
		uniform_int_distribution<int> synapse_location_distro(0, original_size);
		list<int> rand_synapse_locations(num_mutated_synapses, synapse_location_distro(generator));	//TODO erm... not a clue if this will work.. Make sure the generator is called every time, and different random values are passed to each element of the list!!
		rand_synapse_locations.sort();
		rand_synapse_locations.unique();
		//Loop through synapses and delete synapses matching the random locations above
		unordered_map<int, float>::iterator syn_it = synapses_.begin();	//loop though existing synapses
		int syn_location = 0;	//location of corresponding synapse in the synapses map
		for (list<int>::iterator rand_loc_it = rand_synapse_locations.begin();
				 rand_loc_it != rand_synapse_locations.end(); ++rand_loc_it) {
			while (syn_location != *rand_loc_it && syn_location < synapses_.size()) { //TODO: fix the types here in the comparison to be the same
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
