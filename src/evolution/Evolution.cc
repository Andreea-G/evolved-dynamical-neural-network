/*
 * Evolution.cc
 *
 *  Created on: May 16, 2014
 *      Author: Andreea
 */

#include "../brain/Neuron.h"		//TODO: find better way for this include
#include "../brain/Brain.h"
#include "Evolution.h"
#include <iostream>
#include <math.h>	//for floor function

using std::deque;

Evolution::Evolution() {
	prob_asexual_ = 0;
	prob_mutated_neurons_ = 0;
}


Evolution::Evolution(const float prob_asexual, const float prob_mutated_neurons) {
	prob_asexual_ = prob_asexual;
	prob_mutated_neurons_ = prob_mutated_neurons;
}

int Evolution::FitnessWeighting(const int fitness) {
	//For now, using a quadratic function to make sure successful brains get mated often.
	return fitness * fitness;
}

void Evolution::set_brain_cum_odds(const deque<Brain> &brains) {
	size_t num_brains = brains.size();
	deque<float> unnorm_cum_odds;		//unnormalized cummulated mating odds;
	unnorm_cum_odds.push_back(0);
	for (deque<Brain>::iterator brain_it = brains.begin(); brain_it != brains.end(); brain_it++) {
		unnorm_cum_odds.push_back(unnorm_cum_odds.end() + FitnessWeighting(brain_it->get_fitness_score()));
	}
	unnorm_cum_odds.pop_front();		//get rid of useless 0 in the begining
	brain_cum_mating_odds_.clear();		//reset to empty deque
	float sum_odds = unnorm_cum_odds.back();
	for (size_t br = 0; br < num_brains; br++) {
		int mating_odds = floor(unnorm_cum_odds[i] * num_brains / sum_odds);		//normalized s.t. sum over mating_odds ~ number of brains
		for (int i = 0; i < mating_odds; i++) {
			brain_cum_mating_odds_.push_back(br);
		}
	}

	//The size of brain_cum_mating_odds_ is at most num_brains; it can be smaller due to the floor function above, but should not be larger...
	if (brain_cum_mating_odds_.size() > num_brains) {
		std::cerr << std::cout << "Error! Cumulating odds deque is larger than total number of brains... What went wrong??\n";
	}
}


Brain Evolution::MutateBrain(Brain parent_brain, const int num_mutated_neurons, const int num_mutated_synapses) const {
	parent_brain.MutateNeurons(num_mutated_neurons, num_mutated_synapses);
	return parent_brain;  //TODO: I'm a bit confused here, does this return reference or invoke copy constructor?
}


Brain Evolution::MateBrains(const Brain &parent1, const Brain &parent2) const {
	size_t num_neurons = parent1.get_num_neurons();
	Brain child(num_neurons, parent1.get_num_input_neurons(), parent1.get_num_output_neurons());

	std::random_device generator;
	std::uniform_int_distribution<size_t> cross_over_distro(0, num_neurons-1);
	size_t cross_over = cross_over_distro(generator);

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

	std::random_device generator;
	std::uniform_int_distribution<int> mating_distro(0, brain_cum_mating_odds_.size()-1);
	std::uniform_real_distribution<float> asexual_distro(0.0, 1.0);

	deque<Brain> next_gen;
	//Create a new generation of num_brains children
	for (size_t br = 0; br < num_brains; br++) {
		//Randomly pick parent 1
		int parent1_index = brain_cum_mating_odds_[mating_distro(generator)];
		if (asexual_distro(generator) < prob_asexual_) {	//asexual reproduction
			Brain new_brain = MutateBrain(brains[parent1_index], num_mutated_neurons, num_mutated_synapses);
			next_gen.push_back(new_brain);
		} else {		//sexual reproduction
			int parent2_index = brain_cum_mating_odds_[mating_distro(generator)];
			//if both parents the same, do asexual reproduction
			if (parent2_index == parent1_index) {
				Brain new_brain = MutateBrain(brains[parent1_index], num_mutated_neurons, num_mutated_synapses);
				next_gen.push_back(new_brain);
			} else {
				Brain new_brain = MateBrains(brains[parent1_index], brains[parent2_index]);		//first mate two brains to get one child
				new_brain = MutateBrain(new_brain, num_mutated_neurons, num_mutated_synapses);  //then mutations occur
				next_gen.push_back(new_brain);
			}
		}
	}
	return next_gen;
}

