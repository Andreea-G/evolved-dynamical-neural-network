/*
 *	Evolution.cc
 *
 *	Created on: May 16, 2014
 *	Author: Andreea, Garrett
 */

//DEL #include "../brain/Neuron.h"
#include <iostream>
#include <math.h>	//floor function
#include <algorithm> //for_each
#include "Evolution.h"
#include "../Globals.h" //TODO: find better way for this include

using std::deque;

int Evolution::FitnessWeighting(const int fitness) {
	//For now, using a quadratic function to make sure successful brains get mated often.
	return fitness * fitness;
}

int Evolution::ChooseMostFitBrains(const deque<Brain> &brains) {
	size_t num_brains = brains.size();
	//unnormalized mating priorities.  After normalizing, these values will say each brain's chances of getting selected
	//for the next generation.  For example, if brain 1 gets normalized to 5, then it'll appear 5 times and have a high
	//probability of getting selected to "contribute" to the creation of each new brain.
	deque<float> unnorm_mating_priorities;

	for (auto brain_it = brains.begin(); brain_it != brains.end(); brain_it++) {
		unnorm_mating_priorities.push_back(FitnessWeighting(brain_it->get_fitness_score()) );
	}

	most_fit_brains_.clear();		//reset to empty deque

	//get the sum of mating priorities of all brains to help normalize (implemented with a lambda for practice)
	//	float sum_mating_priorities = unnorm_mating_priority.back();  DEL
	float sum_mating_priorities = 0;
	std::for_each(unnorm_mating_priorities.begin(), unnorm_mating_priorities.end(),
				  [&](float priority) {sum_mating_priorities += priority;});

	for (size_t brain_index = 0; brain_index < num_brains; brain_index++) {
		int mating_priority = floor(unnorm_mating_priorities[brain_index] * num_brains / sum_mating_priorities);		//normalized s.t. summing all the mating_priority values  ~= number of brains
		for (int i = 0; i < mating_priority; i++) {
			most_fit_brains_.push_back(static_cast<int>(brain_index));
		}
	}
	//TODO:  floor function is basically going to cut out all brains below the mean fitness
	//Instead, we could use round(.) and then after that for loop adjust the number of brains by cutting or adding (add by sampling the existing brains)

	//The size of brain_cum_mating_odds_ is at most num_brains; it can be smaller due to the floor function above, but should not be larger...
	if (most_fit_brains_.size() > num_brains) {
		std::cerr << "Error! most_fit_brains_ deque is larger than total number of brains.. What went wrong??\n";
		return -1;
	}
	//The size of brain_cum_mating_odds_ should be greater than zero
	if (most_fit_brains_.size() == 0) {
		std::cerr << "Error! most_fit_brains is empty! There are no parents that can form the next generation...";
		return -1;
	}

	return 0;
}


Brain Evolution::MutateBrain(const Brain &parent_brain, const int num_mutated_neurons,
														 const int num_mutated_synapses) const {
	Brain child(parent_brain);
	child.MutateNeurons(num_mutated_neurons, num_mutated_synapses);
	return child;
}


Brain Evolution::MateBrains(const Brain &parent1, const Brain &parent2) const {
	size_t num_neurons = parent1.get_num_neurons();
	//create an empty brain
	Brain child(0, parent1.get_num_input_neurons(), parent1.get_num_output_neurons());

	std::uniform_int_distribution<size_t> cross_over_distro(0, num_neurons-1);
	//neurons 0 to (cross_over) will come from brain 1 and the rest from brain 2
	size_t cross_over = cross_over_distro(globals::gen);

	for (size_t i = 0; i < cross_over; i++) {
		child.neurons_.push_back(parent1.neurons_[i]);
	}
	for (size_t i = cross_over; i < num_neurons; i++) {
		child.neurons_.push_back(parent2.neurons_[i]);
	}
	return child;
}


deque<Brain> Evolution::GetNextGeneration (const deque<Brain> &brains, const int num_mutated_neurons,
																					 const int num_mutated_synapses) const {

	size_t num_brains = brains.size();

	std::uniform_int_distribution<int> mating_distro(0, most_fit_brains_.size()-1);
	std::uniform_real_distribution<float> asexual_distro(0.0, 1.0);

	deque<Brain> next_gen;
	//Create a new generation of num_brains children
	for (size_t br = 0; br < num_brains; br++) {
		//Randomly pick parent 1
		int parent1_index = most_fit_brains_[mating_distro(globals::gen)];
		if (asexual_distro(globals::gen) < prob_asexual_) {	//asexual reproduction
			Brain new_brain = MutateBrain(brains[parent1_index], num_mutated_neurons, num_mutated_synapses);
			next_gen.push_back(new_brain);
		} else {		//sexual reproduction
			//Randomly pick parent 2
			int parent2_index = most_fit_brains_[mating_distro(globals::gen)];
			//if both parents the same, do asexual reproduction
			if (parent2_index == parent1_index) {
				Brain new_brain = MutateBrain(brains[parent1_index], num_mutated_neurons, num_mutated_synapses);
				next_gen.push_back(new_brain);
			} else {
				//first mate two brains to get one child
				Brain new_brain = MateBrains(brains[parent1_index], brains[parent2_index]);
				//then mutations occur
				new_brain = MutateBrain(new_brain, num_mutated_neurons, num_mutated_synapses);
				next_gen.push_back(new_brain);
			}
		}
	}
	return next_gen;
}

