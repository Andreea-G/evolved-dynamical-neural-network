/*
 * Neuron.h
 *
 *  Created on: May 15, 2014
 *      Author: Andreea
 */

#ifndef BRAIN__NEURON_H_
#define BRAIN__NEURON_H_

#include <vector>

using std::vector;
using std::unordered_map;

const int MAX_STRENGTH = 100;		//TODO find better way to define this somewhere...
const int MAX_ACTIVATION = 100;		//TODO find better way to define this somewhere...

class Neuron {

public:
	Neuron() { activation_ = 0; decay_rate_ = 0; activ_treshold_ = 0; max_strength_ = MAX_STRENGTH; };
	Neuron(const int &activation, const int &decay_rate) { activation_ = activation; decay_rate_ = decay_rate; };
	~Neuron() {};
	void set_activation(const int &activation) { activation_ = activation; }; 
	int get_activation() const { return activation_; }; 
	void set_activ_threshold(const int &activ_threshold) { activ_threshold_ = activ_threshold; }; 
	int get_activ_threshold() const { return activ_threshold_; }; 
	void set_decay_rate(const int &decay_rate) { decay_rate_ = decay_rate; }; 
	int get_decay_rate() const { return decay_rate_; }; 

private:
	unordered_map<int, int> synapses_;		//map of synapses where the first element is the destination neuron and the second element is the connection strength
	int activation_;				//current activation of the neuron
	int activ_treshold_;
	int decay_rate_;				//strength of each neuron decays exponentially with a certain decay rate
	int max_strength_;			//maximum strength a synapse can have
	//Randomly mutates synapses. num_mutated_synapses is the number of synapses that will undergo a mutation. If it is positive, new connections will be formed or the strengths of existing ones will be changed. If it is negative, random connections will be removed. num_neurons is the total number of neurons in the brain.
	void MutateSynapses(const int &num_mutated_synapses, const int &num_neurons);
};


#endif /* BRAIN__NEURON_H_ */
