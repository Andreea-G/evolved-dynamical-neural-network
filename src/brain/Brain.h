/*
 * Brain.h
 *
 *  Created on: May 15, 2014
 *      Author: Andreea
 */

#ifndef BRAIN__BRAIN_H_
#define BRAIN__BRAIN_H_

#include <vector>

using std::vector;

class Brain {

public:
	int fitness_score_;		//describes how well the brain has performed on the given task
	Brain() {num_neurons_ = 0; fitness_score_ = 0; };
	Brain(const int &num_neurons) { num_neurons_ = num_neurons; fitness_score_ = 0; };
	~Brain () {};
	//The input neurons take in a signal from the outside, in the form of a binary signal. The first few neurons will be input neurons, each taking in one bit of signal.
	void give_input(const vector<bool> &input_vals);		
	//The output neurons give the result, also in the form of a binary signal. The next few neurons will be output neurons.
	vector<bool> get_output() const;
	//Randomly mutates num_mutated_synapses inside of randomly selected neurons. The number of neurons selected for mutation is num_mutated_neurons. 
	//See also MutateSynapses inside of the Neuron class.
	void MutateSynapses(const int &num_mutated_neurons, const int &num_mutated_synapses);
	//Causes one network firing inside the brain.
	void Cycle();

private:
	int num_neurons_;	//total number of neurons
	vector<Neuron> neurons_;	//vector of neurons
	int num_input_neurons, num_output_neurons;	//number of input and output neurons

};


#endif /* BRAIN__BRAIN_H_ */
