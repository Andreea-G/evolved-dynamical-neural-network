/*
 * Brain.h
 *
 *  Created on: May 15, 2014
 *      Author: Andreea
 */

#ifndef BRAIN__BRAIN_H_
#define BRAIN__BRAIN_H_

#include <deque>

using std::deque;

class Brain {

public:
	//TODO: why do we have this constructor, when would it be useful? It also doesn't define neurons_ so invalid.
	//Brain() { num_neurons_ = 0; num_input_neurons_ = 0; num_output_neurons_ = 0; fitness_score_ = 0; }

	//Creates brain where neuron are created with the most basic neuron constructor
	//(see constructors in Neuron.h for details)
	Brain(const int num_neurons, const int num_input_neurons, const int num_output_neurons);
	//Gives more control over average activation, average number of synapses per neuron, etc.
	Brain(const int num_neurons, const int num_input_neurons, const int num_output_neurons, const int av_num_syn,
				const float av_syn_strength, const float av_active_threshold, const float av_start_activation);

	//TODO: get rid of this.  No need to explicitly write out the implicit copy constructor
	//Brain(const Brain &br);	//copy constructor;

	deque<Neuron> neurons_;

	void set_fitness_score(const int &fitness_score) { fitness_score_ = fitness_score; }
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
	int num_input_neurons_, num_output_neurons_;	//number of input and output neurons
	float fitness_score_;		//describes how well the brain has performed at the given task
};


#endif /* BRAIN__BRAIN_H_ */
