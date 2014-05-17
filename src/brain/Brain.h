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

constexpr int TIME_STEP = 0.001;		//TODO find better way to define this somewhere...

class Brain {

public:
	Brain() { num_neurons_ = 0; num_input_neurons_ = 0; num_output_neurons_ = 0; fitness_score_ = 0; }
	Brain(const int &num_neurons, const int &num_input_neurons, const int &num_output_neurons) {
		num_neurons_ = num_neurons; num_input_neurons_ = num_input_neurons; num_output_neurons_ = num_output_neurons; fitness_score_ = 0; 
	} 
	Brain(const int &num_neurons, const int &num_input_neurons, const int &num_output_neurons, const Neuron &neurons) {
		num_neurons_ = num_neurons; num_input_neurons_ = num_input_neurons; num_output_neurons_ = num_output_neurons; fitness_score_ = 0; 
		neurons_ = neurons;
	} 
	Brain(const Brain&);	//copy constructor;
	~Brain () {};
	deque<Neuron> neurons_;	//deque of neurons
	void set_fitness_score(const int &fitness_score) { fitness_score_ = fitness_score; }
	float get_fitness_score() const { return fitness_score_; }
	//The input neurons take in a signal from the outside, in the form of a binary signal. The first few neurons will be input neurons, each taking in one bit of signal.
	void give_input(const deque<bool>&);		
	//The output neurons give the result, also in the form of a binary signal. The next few neurons will be output neurons.
	deque<bool> get_output() const;
	//Randomly mutates num_mutated_synapses inside of randomly selected neurons. The number of neurons selected for mutation is num_mutated_neurons. 
	//See also MutateSynapses inside of the Neuron class.
	void MutateSynapses(const int&, const int&);
	//Causes one network firing inside the brain.
	void Cycle();

private:
	int num_neurons_;	//total number of neurons
	int num_input_neurons, num_output_neurons;	//number of input and output neurons
	float fitness_score_;		//describes how well the brain has performed on the given task
};


#endif /* BRAIN__BRAIN_H_ */
