/*
 *	Created on: May 16, 2014
 *	Author: Andreea G, Garrett R
 */

#ifndef EVOLUTION__EVOLUTION_H_
#define EVOLUTION__EVOLUTION_H_

#include <deque>

#include <src/brain/Brain.hpp>

using std::deque;

class Evolution {

public:
	explicit Evolution(const float prob_asexual = 0) : prob_asexual_(prob_asexual) {};
	//Note: we could pass more values to the constructor so that function like GetNextGeneration have more simple
	//signatures, but that would be at the expense of being able to change the evolution process halfway through task.

	//Takes current brains and randomly selects some for asexual reproduction (which calls MutateBrain on that brain)
	//and some for sexual reproduction (which calls MateBrains on two brains and MutateBrain on the result)
	//setting verbose_num_brains to N will print the info on the parents of the first N brains.
	deque<Brain> GetNextGeneration(const deque<Brain> &brains, const size_t num_mutated_neurons,
	                               const size_t num_mutated_synapses, const size_t verbose_num_brains = 0,
	                               const bool mutate_decay_rate = true, const bool mutate_active_threshold = true) const;

	//Mutate a brain and returns the mutated brain
	Brain MutateBrain(const Brain &parent_brain, const size_t num_mutated_neurons, const size_t num_mutated_synapses,
	                  const bool mutate_decay_rate=true, const bool mutate_active_threshold=true) const;
	//Mate two different brains to get one child. No mutations (since the MutateBrain function can afterwards be
	//called on the resulting child)
	//Random cross-over point x is selected and the first 1 to x neurons are taken from parent 1,
	//and the rest from Parent 2
	//(in the future we could be more random about which neurons from which parents survive)
	Brain MateBrains(const Brain &parent1, const Brain &parent2) const;

	//We run the fitness scores through the function FitnessWeigthing, then create a "temporary generation" of brain
	//which is held in most_fit_brains_.  A very successful brain can appear more than once and a very unsuccessful brain
	//may not appear at all.  Because of rounding, if a brain's fitness score (after being transformed by FitnessWeigting)
	//is less than half the mean of the transformed fitness scores, it will have no chance of getting chosen.
	int ChooseMostFitBrains(const deque<Brain> &brains);

private:
	//The probability of a brain being selected for mating will be proportional to the FitnessWeighting function.
	float FitnessWeighting(const float fitness);

	//Probability for each brain to undergo asexual reproduction (vs. sexual reproduction) inside GetNextGeneration(.)
	const float prob_asexual_;

	//most_fit_brains_ is a list of the most fit brains, where very fit brains can appear more than once.
	//the more times brain i appears in this deque, the more likely it'll get chosen.  The size of the deque may be
	//larger than the number of brains in each generation.
	//If brain i appears twice and the number of brains in this "temporary generation" is approx. equal to the number of
	//brains in a generation, it'll have about twice the average amount of progeny.
	//The number of times a brain appears here will be proportional to the FitnessWeighting.
	//For each member of next generation, a number rand will be drawn (at random) between 0 and (length of this deque)
	//(namely the last element in the deque). The brain selected will then be most_fit_brains_[rand]
	deque<int> most_fit_brains_;

	//grant access to EvolutionTest for unit-testing
	friend class EvolutionTest;
};





#endif /* EVOLUTION__EVOLUTION_H_ */
