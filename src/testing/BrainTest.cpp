#include <iostream>
#include <iomanip>
#include "BrainTest.h"

using std::cout;
using std::cerr;
using std::endl;
using std::min;

void BrainTest::Test1() {
	//Please don't change the numbers in this test suite.
	int num_neurons=8;
	Brain test_brain1(num_neurons, 3, 2);
	deque<Neuron> & neurons1 = test_brain1.neurons_;

	this->DisplaySynapses(neurons1, 8);

	//practice giving input
	deque<bool> brain_input1 = {1, 0, 1};
	test_brain1.give_input(brain_input1);
	if (neurons1[0].activation_!=MAX_ACTIVATION ||
			neurons1[1].activation_!=MIN_ACTIVATION ||
			neurons1[2].activation_!=MAX_ACTIVATION)
		cerr << "After input, there seems to have been an issue";

	//run through a few cycles
	cout << endl << "Here's a few rounds of neuronal activity for your visual inspection.";
	//set precision for reporting activation
	cout << std::setprecision(4) << std::fixed;
	for (int ii=0; ii<5; ii++) {
		cout << "\nRound " << ii << ": ";
		//loop through the neurons outputting their activations
		for (int jj=0; jj<num_neurons; jj++) {
			cout << " " << neurons1[jj].activation_;
		}
		cout << std::flush;
		test_brain1.Cycle();
	}

	//////////////////Brain 2 using the more detailed constructor
	num_neurons=8;
	const int av_num_syn=5; const int st_dev_num_syn=2;
	const float av_active_threshold=25; const float st_dev_active_threshold=5;
	const float av_start_activation=0; const float st_dev_start_activation=0;
	const float av_decay_rate=4; const float st_dev_decay_rate=2;
	Brain test_brain2(num_neurons, 3, 2,
										av_num_syn, st_dev_num_syn,
										av_active_threshold, st_dev_active_threshold,
										av_start_activation, st_dev_start_activation,
										av_decay_rate, st_dev_decay_rate);

	deque<Neuron> & neurons2 = test_brain2.neurons_;

	//give input
	deque<bool> brain_input2 = {1, 1, 0};
	test_brain2.give_input(brain_input2);

	this->DisplaySynapses(neurons2, 8);

	//run through a few cycles
	cout << endl << "Here's a few rounds of neuronal activity for your visual inspection.";
	//set precision for reporting activation
	cout << std::setprecision(4) << std::fixed;
	for (int ii=0; ii<10000; ii++) {
		cout << "\nRound " << ii << ": ";
		//loop through the neurons outputting their activations
		for (int jj=0; jj<num_neurons; jj++) {
			cout << " " << neurons2[jj].activation_;
		}
		cout << std::flush;
		test_brain2.Cycle();
		//now just provoke the brain and see if it finds same steady-state sol'n
		if (ii==5000) {
			test_brain2.give_input(brain_input2);
			test_brain2.neurons_[4].set_activation(MAX_ACTIVATION);
			test_brain2.neurons_[5].set_activation(MAX_ACTIVATION);
			test_brain2.neurons_[6].set_activation(MAX_ACTIVATION);
		}

	}

	//practice brain output
	deque<bool> output2 = test_brain2.get_output();
	deque<bool> expected_output2 = {(test_brain2.neurons_[3].get_activation() > test_brain2.neurons_[3].get_active_threshold()),
																	(test_brain2.neurons_[4].get_activation() > test_brain2.neurons_[4].get_active_threshold())};
	if (output2 != expected_output2)
		cerr << "\n\nERROR: brain output 2 differs from expected output!!!";


	cout << endl << "The test is complete." << endl;
}


void BrainTest::DisplaySynapses(const deque<Neuron> & neurons, int num_neuron_to_display) {
	//Output the origin synapses and strengths for these neurons
	cout << "\n\nCurrent strengths of neurons (origin neuron and strength)" << endl;
	for (int ii=0; ii<num_neuron_to_display; ii++) {
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
		cout << endl << "   Activation:" << neuron_ii.activation_ << "  activation_thresh:" << neuron_ii.active_threshold_;
		cout << "  Decay:" << neuron_ii.decay_rate_;
	}
	cout << endl << endl;
}
