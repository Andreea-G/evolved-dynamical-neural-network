#include <iostream>
#include <iomanip>
#include <fstream>

#include <src/testing/BrainTest.hpp>
#include <src/Globals.hpp>

using std::cout;
using std::cerr;
using std::endl;
using std::min;

void BrainTest::Test1() {
	//Please don't change the numbers in this test suite.
	int num_neurons = 8;
	Brain test_brain1(num_neurons, 3, 2);
	deque<Neuron> & neurons1 = test_brain1.neurons_;

	this->DisplaySynapses(neurons1, 8);

	//practice giving input
	deque<bool> brain_input1 = {1, 0, 1};
	test_brain1.give_input(brain_input1);
	if (neurons1[0].activation_ != globals::MAX_ACTIVATION ||
	    neurons1[1].activation_ != globals::MIN_ACTIVATION ||
	    neurons1[2].activation_ != globals::MAX_ACTIVATION)
		cerr << "After input, there seems to have been an issue";

	//run through a few cycles
	cout << endl << "Here's a few rounds of neuronal activity for your visual inspection.";
	//set precision for reporting activation
	cout << std::setprecision(4) << std::fixed;
	for (int ii = 0; ii < 5; ii++) {
		cout << "\nRound " << ii << ": ";
		//loop through the neurons outputting their activations
		for (int jj = 0; jj < num_neurons; jj++) {
			cout << " " << neurons1[jj].activation_;
		}
		cout << std::flush;
		test_brain1.Cycle();
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	///// Brain 2 using the more detailed constructor
	num_neurons = 800;  //These settings gave a non-repeating brain!
	const float av_active_threshold = 0.25; const float st_dev_active_threshold = 0.04;
	const float av_start_activation = 0.25 ; const float st_dev_start_activation = 0.05;
	const float av_decay_rate = 0.001; const float st_dev_decay_rate = 0.0003;
	const int av_num_syn = 10; const int st_dev_num_syn = 2;
	const float av_syn_strength = 0.05; const float st_dev_syn_strength = 0.04;
//	num_neurons = 10;
//	const float av_active_threshold = 0.25; const float st_dev_active_threshold = 0.04;
//	const float av_start_activation = 0.25 ; const float st_dev_start_activation = 0.05;
//	const float av_decay_rate = 0.05; const float st_dev_decay_rate = 0.02;
//	const int av_num_syn = 6; const int st_dev_num_syn = 2;
//	const float av_syn_strength = 0.40; const float st_dev_syn_strength = 0.04;
	Brain test_brain2(num_neurons, 3, 2,
	                  av_active_threshold, st_dev_active_threshold,
	                  av_start_activation, st_dev_start_activation,
	                  av_decay_rate, st_dev_decay_rate,
	                  av_num_syn, st_dev_num_syn,
	                  av_syn_strength, st_dev_syn_strength);

	deque<Neuron> & neurons2 = test_brain2.neurons_;

	//give input
//	deque<bool> brain_input2 = {1, 1, 0};
//	test_brain2.give_input(brain_input2);

	//I'll send all the output to a temporary file.
	std::ofstream outputFile("tmp_output.txt");
	if (outputFile.good() == false) {
		cerr << "ERROR: problem opening temporary file!";
	}

	this->DisplaySynapses(neurons2, 8);

	//run through a few cycles
	outputFile << endl << "Here's a few rounds of neuronal activity for your visual inspection.";
	//set precision for reporting activation
	outputFile << std::setprecision(2) << std::fixed;
	for (int ii = 0; ii < 100; ii++) {
		outputFile << "\nRound " << ii << ": ";
		//loop through the neurons outputting their activations, but max cout at reporting 10 activations
		for (int jj = 0; jj < min(num_neurons,10); jj++) {
			outputFile << " " << neurons2[jj].activation_;
		}
		outputFile << std::flush;
		test_brain2.Cycle();
		//now just provoke the brain and see if it finds the same steady state sol'n
//		if (3000 <= ii && ii < 3005) {
////			test_brain2.give_input(brain_input2);
////			test_brain2.neurons_[4].set_activation(globals::MAX_ACTIVATION);
////			test_brain2.neurons_[5].set_activation(globals::MAX_ACTIVATION);
////			test_brain2.neurons_[6].set_activation(globals::MAX_ACTIVATION);
////			test_brain2.neurons_[7].set_activation(globals::MAX_ACTIVATION);
////			test_brain2.neurons_[8].set_activation(globals::MAX_ACTIVATION);
////			test_brain2.neurons_[9].set_activation(globals::MAX_ACTIVATION);
//			//Hold a bunch of neurons at MAX_ACTIVATION
//			for (int jj = 0; jj < 100; ++jj) {
//				test_brain2.neurons_[jj].set_activation(globals::MAX_ACTIVATION);
//			}
//		}
//		int tmp_stopper = ii % 2000;
//		if (0 <= tmp_stopper && tmp_stopper < 5) {
////			test_brain2.give_input(brain_input2);
////			test_brain2.neurons_[4].set_activation(globals::MIN_ACTIVATION);
////			test_brain2.neurons_[5].set_activation(globals::MIN_ACTIVATION);
////			test_brain2.neurons_[6].set_activation(globals::MIN_ACTIVATION);
////			test_brain2.neurons_[7].set_activation(globals::MIN_ACTIVATION);
////			test_brain2.neurons_[8].set_activation(globals::MIN_ACTIVATION);
////			test_brain2.neurons_[9].set_activation(globals::MIN_ACTIVATION);
////			test_brain2.neurons_[14].set_activation(globals::MAX_ACTIVATION);
////			test_brain2.neurons_[15].set_activation(globals::MAX_ACTIVATION);
////			test_brain2.neurons_[16].set_activation(globals::MAX_ACTIVATION);
////			test_brain2.neurons_[17].set_activation(globals::MAX_ACTIVATION);
////			test_brain2.neurons_[18].set_activation(globals::MIN_ACTIVATION);
////			test_brain2.neurons_[19].set_activation(globals::MIN_ACTIVATION);
//			//Hold a bunch of neurons at MAX_ACTIVATION
//			for (int jj = 0; jj < 100; ++jj) {
//				test_brain2.neurons_[jj].set_activation(globals::MAX_ACTIVATION);
//			}
//		}
	}

	//practice brain output
	deque<bool> output2 = test_brain2.get_output();
	deque<bool> expected_output2 = {(test_brain2.neurons_[3].get_activation() > test_brain2.neurons_[3].get_active_threshold()),
	                                (test_brain2.neurons_[4].get_activation() > test_brain2.neurons_[4].get_active_threshold())};
	if (output2 != expected_output2)
		cerr << "\n\nERROR: brain output 2 differs from expected output!!!";

	///////////////////////////////////
	////Brain 3

	cout << "Starting tests on Brain 3";

	int num_neurons3 = 8;
	Brain test_brain3(num_neurons3, 2, 2);
	deque<Neuron> & neurons3 = test_brain3.neurons_;

	this->DisplaySynapses(neurons3, 8);

	test_brain3.MutateNeurons(8, -1);
	cout << "OK, I just mutated them!";
	this->DisplaySynapses(neurons3, 8);

	cout << endl << "The test is complete." << endl;
}



void BrainTest::DisplaySynapses(const deque<Neuron> & neurons, int num_neuron_to_display) {
	//Output the origin synapses and strengths for these neurons
	cout << "\n\nCurrent strengths of neurons (origin neuron and strength)" << endl;
	for (int ii = 0; ii < num_neuron_to_display; ii++) {
		Neuron neuron_ii = neurons[ii];
		cout << "\nNeuron " << ii << ": ";
		int count = 0;
		for (auto it = neuron_ii.synapses_.begin();
		     it != neuron_ii.synapses_.end(); it++) {
			cout << it->first << "(" << it->second << ") ";
			count++;
			//report no more than 10 synapses for each neuron
			if (count > 10)
				break;
		}
		cout << endl << "   Activation:" << neuron_ii.activation_ << "  activation_thresh:" << neuron_ii.active_threshold_;
		cout << "  Decay:" << neuron_ii.decay_rate_;
	}
	cout << endl << endl;
}
