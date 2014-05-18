/*
 * Evolution.cc
 *
 *  Created on: May 16, 2014
 *      Author: Andreea
 */

#include "/../Brain/Neuron.h"		//TODO is that how you go back??
#include "/../Brain/Brain.h"
#include "Evolution.h"
#include <math.h>	//for floor function

using std::deque;

void Evolution::set_brain_cum_mating_odds(const deque<Brain>& brains) {
	int num_brains = brains.size();
	deque<float> unnorm_cum_odds;		//unnormalized cummulated mating odds;
	unnorm_cum_odds.push_back(0);
	for (deque<Brain>::iterator brain_it = brains.begin(); brain_it != brains.end(); brain_it++) {
		unnorm_cum_odds.push_back(unnorm_cum_odds.end() + FitnessWeighting(brain_it->get_fitness_score()));
	}
	unnorm_cum_odds.pop_front();		//get rid of useless 0 in the begining
	brain_cum_mating_odds_.clear();		//reset to empty deque
	float sum_odds = unnorm_cum_odds.back();
	for (int br = 0; br < num_brains; br++) {
		int mating_odds = floor(unnorm_cum_odds[i] * num_brains / sum_odds);		//normalized s.t. sum over mating_odds ~ number of brains
		for (int i = 0; i < mating_odds; i++) {
			brain_cum_mating_odds_.push_back(br);
	}

	//The size of brain_cum_mating_odds_ is at most num_brains; it can be smaller due to the floor function above, but should not be larger...
	if (brain_cum_mating_odds_.size() > num_brains) {
		std::cout <<"Error! Cumulating odds deque is larger than total number of brains... What went wrong??\n";
	}
}


deque<Brain> Evolution::GetNextGeneration (const deque<Brain>& brains) {
	int num_brains = brains.size();
	std::random_device generator;
	std::uniform_int_distribution<int> mating_distro(0, brain_cum_mating_odds_.size());
	std::uniform_float_distribution<float> asexual_distro(0.0, 1.0);
	deque<Brain> next_gen;
	//Create a new generation of num_brains children
	for (int br = 0; br < num_brains; br++) {
		//Randomly pick parent 1 by picking a random integer between 0 and brain_cum_mating_odds_.size().
		int parent1 = brain_cum_mating_odds_[mating_distro(generator)];
		if (asexual_distro(generator) < prob_asexual_) {	//asexual reproduction;
			next_gen.push_back(MutateBrain(brains[parent1]));
		} else {		//sexual reproduction
			int parent2 = brain_cum_mating_odds_[mating_distro(generator)];
			Brain child(MateBrains(brains[parent1], brains[parent2]));		//first mate two brains to get one child
			next_gen.push_back(MutateBrain(child));		//then mutations can occur
		}
	}
	return next_gen;
}


Brain Evolution::MutateBrain(const Brain &parent_brain) {		//TODO
	return parent_brain;
}

Brain Evolution::MateBrains(const Brain &parent1, const Brain &parent2) {
	int num_neurons = parent1.get_num_neurons();
	Brain child(num_neurons, parent1.get_num_input_neurons(), parent1.get_num_output_neurons());
	std::random_device generator;
	std::uniform_int_distribution<int> cross_over_distro(0, num_neurons);
	int cross_over = cross_over_distro(generator);
	for (int i = 0; i < cross_over; i++) {
		child.neurons_.push_back(parent1.neurons_[i]);
	}
	for (int i = cross_over; i < num_neurons; i++) {
		child.neurons_.push_back(parent2.neurons_[i]);
	}
	return child;
}







