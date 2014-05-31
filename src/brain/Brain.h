/*
 * Brain.h
 *
 *  Created on: May 15, 2014
 *      Author: Andreea
 */

#ifndef BRAIN__BRAIN_H_
#define BRAIN__BRAIN_H_

#include <deque>
#include "Neuron.h"

using std::deque;

class Brain {

public:
	//Creates brain where neuron are created with the most basic neuron constructor
	//(see constructors in Neuron.h for details)
	Brain(const int num_neurons, const size_t num_input_neurons, const size_t num_output_neurons);
	//Gives more control over average activation, average number of synapses per neuron, etc.
	//For example, this will use a Gaussian distribution to with the specified average and standard deviation to set
	//the active threshold of each neuron.  The active threshold is also enforced to be in the
	//interval [MIN_ACTIVATION, MAX_ACTIVATION].
	//For now, you can't set the synapse strength.  Instead, each synapse has strength chosen from uniform distro on
	//the interval [MIN_STRENGTH, MAX_STRENGTH].
	Brain(const int num_neurons, const size_t num_input_neurons, const size_t num_output_neurons,
				const int av_num_syn, const int st_dev_num_syn,
				const float av_active_threshold, const float st_dev_active_threshold,
				const float av_start_activation, const float st_dev_start_activation,
				const float av_decay_rate, const float st_dev_decay_rate);

	//neurons comprising brain, each with incoming synapses from other neurons
	deque<Neuron> neurons_;

	void set_fitness_score(const int fitness_score) { fitness_score_ = fitness_score; }
	float get_fitness_score() const { return fitness_score_; }

	//The input neurons take in a signal from the outside, in the form of a binary signal.
	//The first few neurons will be input neurons, each taking in one bit of signal.
	void give_input(const deque<bool> &input_vals);
	//The output neurons give the result, also in the form of a binary signal. The next few neurons will be output neurons.
	deque<bool> get_output() const;

	//Randomly mutates num_mutated_synapses synapses inside of randomly selected neurons, as well as the activation threshold and decay rate.
	//The number of neurons selected for mutation is num_mutated_neurons.
	//See also MutateSynapses inside of the Neuron class.
	void MutateNeurons(const int num_mutated_neurons, const int num_mutated_synapses);

	//Causes one network firing inside the brain.
	void Cycle();

private:
	int num_neurons_;	//total number of neurons
	//number of input and output neurons.  The type was 'int', but if looking where it's used, this type makes more sense.
	size_t num_input_neurons_, num_output_neurons_;
	//describes how well the brain has performed at the given task.  This is used by evolution class for choosing brains.
	float fitness_score_;

	//grant access for unit testing
	friend class BrainTest;
};


#endif /* BRAIN__BRAIN_H_ */
