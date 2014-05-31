#include <iostream>
#include "BrainTest.h"

using std::cout;
using std::cerr;
using std::endl;
using std::min;

void BrainTest::Test1() {
	//Please don't change the numbers in this test suite.
	const int num_neurons=8;
	Brain test_brain1(num_neurons, 3, 2);
	deque<Neuron> & neurons = test_brain1.neurons_;

	//Output the origin synapses and strengths of, at most, the first 10 neurons
	cout << "Current strengths of neurons (origin neuron and strength)" << endl;
	for (int ii=0; ii<min(num_neurons, 10); ii++) {
		Neuron neuron_ii = neurons[ii];
		cout << "\nNeuron " << ii << ": ";
		int count=0;
		for (unordered_map<int,float>::iterator it=neuron_ii.synapses_.begin();
				 it != neuron_ii.synapses_.end(); ++it) {
			cout << it->first << "(" << it->second << ") ";
			count++;
			//report no more than 10 synapses for each neuron
			if (count>10)
				break;
		}
	}
	cout << endl << endl;

	//practice giving input
	deque<bool> brain_input = {1, 0, 1};
	test_brain1.give_input(brain_input);
	if (neurons[0].activation_!=MAX_ACTIVATION ||
			neurons[1].activation_!=MIN_ACTIVATION ||
			neurons[2].activation_!=MAX_ACTIVATION)
		cerr << "After input, there seems to have been an issue";

	//run through a few cycles
	cout << endl << "Here's a few rounds of neuronal activity.";
	for (int ii=0; ii<10; ii++) {
		cout << "\nRound " << ii << ": ";
		//loop through the neurons outputting their activations
		for (int jj=0; jj<num_neurons; jj++) {
			cout << " " << neurons[jj].activation_;
		}
		cout << std::flush;
		test_brain1.Cycle();
	}

	cout << endl << "The test is complete." << endl;

}
