/*
 * Evolution.h
 *
 *  Created on: May 16, 2014
 *      Author: Andreea
 */

#ifndef EVOLUTION__EVOLUTION_H_
#define EVOLUTION__EVOLUTION_H_

#include <deque>

using std::deque;

class Evolution {

public:
	Evolution() { prob_asexual_ = 0; prob_mutated_neurons_ = 0; }
	Evolution(const float &prob_asexual, const float &prob_mutated_neurons) { prob_asexual_ = prob_asexual; prob_mutated_neurons_ = prob_mutated_neurons; }
	//The odds of a brain beying selected for mating will be proportional to the FitnessWeighting function. 
	int FitnessWeighting(const int &fitness) { return fitness * fitness; }
	void set_brain_cum_mating_odds(const deque<Brain> &brains);
	//From one parent, obtain a child that may be the same or have some mutations.
	Brain MutateBrain(const Brain &parent_brain, const int &num_mutated_neurons, const int &num_mutated_synapses) const;
	//Mate two different brains to get one child. No mutations (since the MutateBrain function can afterwards be called on the resulting child)
	Brain MateBrains(const Brain &parent1, const Brain &parent2) const;
	//Get a new generations of brains
	deque<Brain> GetNextGeneration (const deque<Brain> &brains) const;

private:
	float prob_asexual_;		
	float prob_mutated_neurons_;
	//brain_cum_mating_odds is a deque used for decided which brain will be selected for mating. It is organized as follows:
	//the key (or indexing parameter) is an integer representing the cumulative mating odds, and the mapped value is a brain corresponding to those odds.
	//The mating odds of each brain will be proportional to the FitnessWeighting, and then normalized s.t. the sum of all odds is equal to the total number of brains.
	//A number rand will be drawn (at random) between 0 and max cumulative odds (namely the last element in the deque). 
	//The brain selected will then be brain_cum_mating_odds[rand]
	deque<int> brain_cum_mating_odds_;
};





#endif /* EVOLUTION__EVOLUTION_H_ */
