/*
 *	Evolution.h
 *
 *	Created on: May 16, 2014
 *	Author: Andreea, Garrett
 */

#ifndef EVOLUTION__EVOLUTION_H_
#define EVOLUTION__EVOLUTION_H_

#include <deque>
#include "../brain/Brain.h"

using std::deque;

class Evolution {

public:
	Evolution(const float prob_asexual=0) : prob_asexual_(prob_asexual) {};

	//Takes current brains and randomly selects some for asexual reproduction (which calls MutateBrain on that brain)
	//and some for sexual reproduction (which calls MateBrains on two brains and MutateBrain on the result)
	deque<Brain> GetNextGeneration(const deque<Brain> &brains, const int num_mutated_neurons,
																	const int num_mutated_synapses) const;

	//Mutate a brain and returns the mutated brain
	Brain MutateBrain(Brain parent_brain, const int num_mutated_neurons,   //TODO: shouldn't this be const Brain& parent_brain?
									 const int num_mutated_synapses) const;
	//Mate two different brains to get one child. No mutations (since the MutateBrain function can afterwards be
	//called on the resulting child)
	//Random cross-over point x is selected and the first 1 to x neurons are taken from parent 1,
	//and the rest from Parent 2
	//(TODO: in the future we could be more random about which neurons from which parents survive)
	Brain MateBrains(const Brain &parent1, const Brain &parent2) const;

private:
	//Look at fitness scores to choose the most_fit_brains_
	void ChooseMostFitBrains(const deque<Brain> &brains);

	//The probability of a brain being selected for mating will be proportional to the FitnessWeighting function.
	int FitnessWeighting(const int fitness);

	//Probability for each brain to undergo asexual reproduction (vs. sexual reproduction) inside GetNextGeneration(.)
	float prob_asexual_;

	//most_fit_brains_ is a list of the most fit brains, where very fit brains can appear more than once.
	//the more times brain i appears in this deque, the more likely it'll get chosen.  The size of the deque is
	//the same size as the population of brains, so if brain i appears twice, it'll have twice the average amount of
	//progeny.
	//The number of times a brain appears here will be proportional to the FitnessWeighting.
	//The proportionality is chosen s.t. the length of the deque is equal to the total number of brains.
	//For each member of next generation, a number rand will be drawn (at random) between 0 and (length of this deque)
	//(namely the last element in the deque). The brain selected will then be most_fit_brains_[rand]
	deque<int> most_fit_brains_;

	//grant access to EvolutionTest for unit-testing
	friend class EvolutionTest;
};





#endif /* EVOLUTION__EVOLUTION_H_ */
