/*
 * Neuron.h
 *
 *  Created on: May 15, 2014
 *      Author: Andreea
 */

#ifndef BRAIN__NEURON_H_
#define BRAIN__NEURON_H_

#include <unordered_map>

using std::unordered_map;

constexpr float MAX_STRENGTH = 100;		//TODO find better way to define this somewhere...
constexpr float MAX_ACTIVATION = 100;		//TODO find better way to define this somewhere...

class Neuron {

public:
	Neuron() { activation_ = 0; new_activation_ = 0; decay_rate_ = 0; activ_threshold_ = 0; };
	Neuron(const float &activation, const float &decay_rate, const float &activ_threshold) {
		activation_ = activation; new_activation_ = 0; decay_rate_ = decay_rate; activ_threshold_ = activ_threshold;
	};
	Neuron(const Neuron& other);		//copy constructor
	~Neuron() {};
	void set_activation(const float &activation) { activation_ = activation; }
	float get_activation() const { return activation_; }
	void set_new_activation(const float &new_activation) { new_activation_ = new_activation; }
	float get_new_activation() const { return new_activation_; }
	void set_activ_threshold(const float &activ_threshold) { activ_threshold_ = activ_threshold; }
	float get_activ_threshold() const { return activ_threshold_; }
	void set_decay_rate(const float &decay_rate) { decay_rate_ = decay_rate; }
	float get_decay_rate() const { return decay_rate_; }
	//Decides if activation is above threshold, in order for the neuron to fire.
	bool ActivationFunction() const { return (activation_ > activ_threshold_); }
	//Computes the updated activation of the neuron after one time-step
	void Cycle();
	//Updates the current activation to be the new activation at time t + delta t, and sets the future new_activation to zero
	void update_activation() { activation_ = new_activation_; new_activation_ = 0; }

private:
	unordered_map<int, float> synapses_;		//map of synapses where the first element is the origin neuron and the second element is the connection strength
	float activation_;				//current activation of the neuron
	float new_activation_;
	float activ_threshold_;
	float decay_rate_;				//strength of each neuron decays exponentially with a certain decay rate
	//Randomly mutates synapses. num_mutated_synapses is the number of synapses that will undergo a mutation. If it is positive, new connections will be formed or the strengths of existing ones will be changed. If it is negative, random connections will be removed. num_neurons is the total number of neurons in the brain.
	void MutateSynapses(const int&, const int&);
};


#endif /* BRAIN__NEURON_H_ */
