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
	Evolution();
	Evolution(const float prob_asexual, const float prob_mutated_neurons);

	//The odds of a brain being selected for mating will be proportional to the FitnessWeighting function.
	int FitnessWeighting(const int fitness);

	//Set brain cumulative odds
	void set_brain_cum_odds(const deque<Brain> &brains);

	//Mutate a brain and returns the mutated brain
	Brain MutateBrain(Brain parent_brain, const int num_mutated_neurons,
									 const int num_mutated_synapses) const;
	//Mate two different brains to get one child. No mutations (since the MutateBrain function can afterwards be
	//called on the resulting child)
	//Random cross-over point x is selected and first 1 to x neurons are taken from parent 1, and the rest from Parent 2
	//(TODO: in the future we could be more random about which neurons from which parents survive)
	Brain MateBrains(const Brain &parent1, const Brain &parent2) const;

	//Takes current brains and randomly selects some for asexual reproduction (which calls MutateBrain on that brain)
	//and some for sexual reproduction (which calls MateBrains on two brains and MutateBrain on the result)
	deque<Brain> GetNextGeneration (const deque<Brain> &brains, const int num_mutated_neurons,
																	const int num_mutated_synapses) const;

private:
	//Probability for each brain to undergo asexual reproduction (vs. sexual reproduction) inside GetNextGeneration(.)
	float prob_asexual_;		
	float prob_mutated_neurons_;
	//brain_cum_mating_odds is a deque used to decide which brain will be selected for mating. It is organized as follows:
	//the key (or indexing parameter) is an integer representing the cumulative mating odds,
	//and the mapped value is a brain corresponding to those odds.
	//The mating odds of each brain will be proportional to the FitnessWeighting, and then normalized s.t.
	//the sum of all odds is equal to the total number of brains.
	//A number rand will be drawn (at random) between 0 and max cumulative odds (namely the last element in the deque). 
	//The brain selected will then be brain_cum_mating_odds[rand]
	deque<int> brain_cum_mating_odds_;
};





#endif /* EVOLUTION__EVOLUTION_H_ */
