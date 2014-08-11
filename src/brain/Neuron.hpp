/*
 *	Neuron.h
 *
 *	Note: the synapses of a neuron can connect back to the same neuron.
 *
 *	Created on: May 15, 2014
 *	Author: Andreea
 */

#ifndef BRAIN__NEURON_H_
#define BRAIN__NEURON_H_

#include <unordered_map>
#include <random>

using std::unordered_map;


class Neuron {
friend class BrainTest;
public:
	//generate neuron with random active_threshold and decay_rate and with synapses (with random strengths) coming from
	//random origin neurons.  It needs to know how many neurons are in the brain.  The number of synapses is given by
	//uniform distribution: [0,num_neurons].
	explicit Neuron(const int num_neurons);
	//Assigns the synapses to random originating neurons
	//If the syn_strength parameters aren't specified (or set to zero), a uniform distribution is used
	Neuron(const float start_activation, const float decay_rate, const float active_threshold,
					const int num_neurons, const int num_synapses,
				 const float av_syn_strength = 0, const float st_dev_syn_strength = 0);

	void set_activation(const float &activation) { activation_ = activation; }
	float get_activation() const { return activation_; }
	void set_new_activation(const float &new_activation) { new_activation_ = new_activation; }
	float get_new_activation() const { return new_activation_; }
	void set_active_threshold(const float &active_threshold) { active_threshold_ = active_threshold; }
	float get_active_threshold() const { return active_threshold_; }
	void set_decay_rate(const float &decay_rate) { decay_rate_ = decay_rate; }
	float get_decay_rate() const { return decay_rate_; }

	//set activation to be the activation after current cycle (or zero if neuron just fired)
	//and sets the future new_activation to zero
	void UpdateActivation();
	//return true if neuron's activation is high enough to fire.
	bool ActivationFunction() const;
	//set just_fired to true if neuron can fire.
	void AttemptToActivate();

	//Randomly mutates synapses. num_mutated_synapses is the number of synapses
	//that will undergo a mutation. If it is positive, new connections will be formed
	//or the strengths of existing ones will be changed. If it is negative,
	//random connections will be removed. num_neurons is the total number of neurons in the brain.
	void MutateSynapses(int num_mutated_synapses, const int num_neurons);

	//map of synapses where the first element is the origin neuron and the second element is the connection strength
	unordered_map<int, float> synapses_;

	bool just_fired; //during a brain cycle, remember if a neuron fired, and if so we set it to zero after cycle's over.

private:
	float activation_;				//current activation of the neuron
	//temporary variable to activation for next round (since we don't want it to affect other neurons in this round)
	float new_activation_;

	float active_threshold_;
	float decay_rate_;				//strength of each neuron decays exponentially with a certain decay rate

};


#endif /* BRAIN__NEURON_H_ */
