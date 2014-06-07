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
using std::normal_distribution;
using std::size_t;
using std::min;
using std::max;

Neuron::Neuron(const int num_neurons) {
	activation_ = 0; new_activation_ = 0;
	just_fired = 0;

	my_types::gen_type generator;
	uniform_real_distribution<float> unit_distro(0, 1);
	uniform_int_distribution<int> neuron_distro(0, num_neurons-1);

	decay_rate_ = MAX_DECAY_RATE * unit_distro(generator);
	active_threshold_ = (MAX_ACTIVATION - MIN_ACTIVATION) * unit_distro(generator) + MIN_ACTIVATION;
	//make sure active_threshold_ is not zero, or else neuron will just be constantly firing
	active_threshold_ = max(active_threshold_, 1.f);

	int num_synapses = neuron_distro(generator);
	//Loop through each synapse assigning random strength and origin neuron
	for (int i = 0; i < num_synapses; i++) {
		//get random origin  (where synapse comes from).  If it is a duplicate, then the last one is overwritten.
		int origin_neuron = neuron_distro(generator);
		synapses_[origin_neuron] = MAX_STRENGTH * unit_distro(generator);
	}
}


Neuron::Neuron(const float start_activation, const float decay_rate, const float active_threshold,
					const int num_neurons, const int num_synapses, const float av_syn_strength, const float st_dev_syn_strength) {
	activation_ = start_activation;
	new_activation_ = 0;
	decay_rate_ = decay_rate;
	active_threshold_ = active_threshold;
	just_fired = 0;

	my_types::gen_type generator;
	uniform_int_distribution<int> neuron_distro(0, num_neurons-1);

	//if the default parameters for syn strength are given, then use uniform distribution
	if (av_syn_strength==0 && st_dev_syn_strength==0) {
		uniform_real_distribution<float> strength_uniform_distro(MIN_STRENGTH, MAX_STRENGTH);
		//Loop through each synapse assigning random strength and origin neuron
		for (int i = 0; i < num_synapses; i++) {
			//get random origin neuron (where synapse comes from)
			int origin_neuron = neuron_distro(generator);
			synapses_[origin_neuron] = strength_uniform_distro(generator);
		}
	} else {
		normal_distribution<float> strength_normal_distro(av_syn_strength, st_dev_syn_strength);
		//Loop through each synapse assigning random strength and origin neuron
		for (int i = 0; i < num_synapses; i++) {
			//get random origin neuron (where synapse comes from)
			int origin_neuron = neuron_distro(generator);
			//generate synapse strength and make sure it's within valid range.
			synapses_[origin_neuron] = min(max(strength_normal_distro(generator), MIN_STRENGTH), MAX_STRENGTH);
		}
	}
}


void Neuron::MutateSynapses(int num_mutated_synapses, const int num_neurons) {
	my_types::gen_type generator;
	uniform_int_distribution<int> neuron_distro(0, num_neurons-1); //-1 since the bounds are inclusive
	uniform_real_distribution<float> strength_distro(MIN_STRENGTH, MAX_STRENGTH);

	if (num_mutated_synapses >= 0) {		//add synapses
		//At most num_mutated_synapses will be added (could be less if there are duplicates;
		//in that case the corresponding synapse strength is changed to a random value).
		for (int ii = 0; ii < num_mutated_synapses; ii++) {
			int rand_neuron_id = neuron_distro(generator);
			synapses_[rand_neuron_id] = strength_distro(generator);
		}
	}
	else if (num_mutated_synapses < 0) {	//delete synapses
		//OPINION: the following block is confusing.  If synapses_ had been a vector instead of unordered_map, this would
		//have been trivial. -Garrett

		size_t original_size = synapses_.size();
		//If neuron has no synapses, then we do nothing to it
		if (original_size==0)
			return;

		num_mutated_synapses *= -1;	//make it positive

		//Make a list of random synapse locations such that corresponding synapses in the unsorted_map will be deleted.
		//The list will be sorted and duplicate values removed. This means that at most num_mutated_synapses will be removed
		//(could be less if there are duplicates).
		uniform_int_distribution<int> synapse_location_distro(0, original_size-1);
		list<int> rand_synapse_locations(num_mutated_synapses);
		//Loop through and assign random new origin neurons
		for (list<int>::iterator rand_assign_it = rand_synapse_locations.begin();
							rand_assign_it != rand_synapse_locations.end(); rand_assign_it++) {
			*rand_assign_it = synapse_location_distro(generator);
		}

		rand_synapse_locations.sort();
		rand_synapse_locations.unique();

		//Loop through synapses and delete synapses matching the random locations above
		unordered_map<int, float>::iterator syn_it = synapses_.begin();
		int syn_location = 0;	//location of corresponding synapse in the synapses map
		for (list<int>::iterator rand_loc_it = rand_synapse_locations.begin();
							rand_loc_it != rand_synapse_locations.end(); rand_loc_it++) {
			//Need to set syn_location to our next rand_synapse_location, but must use while loop to go through unordered_map
			while (syn_location != *rand_loc_it && syn_location < static_cast<int>(synapses_.size()) ) {  //TODO: Should we make syn_location size_t to avoid typecast here?
				//Note: rand_synapse_locations is ordered, so we only have to increase syn_location
				syn_location++;
				syn_it++;
			}
			if (syn_location == *rand_loc_it) {
				syn_location++;
				//erase this synapse and move to the next one
				synapses_.erase(syn_it++);
			}
		}

	}
}


bool Neuron::ActivationFunction() const {
	return (activation_ > active_threshold_);
}


void Neuron::AttemptToActivate() {
	if (ActivationFunction())
		just_fired = true;
}


void Neuron::UpdateActivation() {
	//if neuron just fired, it gets depleted.
	if (just_fired) {
		activation_ = 0;
		just_fired = false;
	}	else {
		activation_ = new_activation_;
	}

	new_activation_ = 0;
}
