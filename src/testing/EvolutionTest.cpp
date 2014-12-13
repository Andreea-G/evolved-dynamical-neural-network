#include <iostream>
#include <algorithm>

#include <src/testing/EvolutionTest.hpp>
#include <src/evolution/Evolution.hpp>
#include <src/testing/BrainTest.hpp>

using std::cout;
using std::endl;

void EvolutionTest::test1() {
	Evolution evolution1(0);

	const int num_neurons = 10;
	const float av_active_threshold = 25; const float st_dev_active_threshold = 0;
	const float av_start_activation = 25 ; const float st_dev_start_activation = 0;
	const float av_decay_rate = 0.05; const float st_dev_decay_rate = 0.0;
	const int av_num_syn = 4; const int st_dev_num_syn = 0;
	const float av_syn_strength = 28; const float st_dev_syn_strength = 0;
	Brain brain1(num_neurons, 3, 2,
	             av_active_threshold, st_dev_active_threshold,
	             av_start_activation, st_dev_start_activation,
	             av_decay_rate, st_dev_decay_rate,
	             av_num_syn, st_dev_num_syn,
	             av_syn_strength, st_dev_syn_strength);

	const int num_neurons2 = 10;
	const float av_active_threshold2 = 35; const float st_dev_active_threshold2 = 0;
	const float av_start_activation2 = 35 ; const float st_dev_start_activation2 = 0;
	const float av_decay_rate2 = 0.1; const float st_dev_decay_rate2 = 0.0;
	const int av_num_syn2 = 2; const int st_dev_num_syn2 = 0;
	const float av_syn_strength2 = 22; const float st_dev_syn_strength2 = 0;
	Brain brain2(num_neurons2, 3, 2,
	             av_active_threshold2, st_dev_active_threshold2,
	             av_start_activation2, st_dev_start_activation2,
	             av_decay_rate2, st_dev_decay_rate2,
	             av_num_syn2, st_dev_num_syn2,
	             av_syn_strength2, st_dev_syn_strength2);

	////Test mutating brains
//		BrainTest::DisplaySynapses(brain1.neurons_, 10);

//		cout << "OK, mutating..." << endl;
//		Brain mutated_brain = evolution1.MutateBrain(brain1, 1, 2);

//		BrainTest::DisplaySynapses(mutated_brain.neurons_, 10);

	////Test mating brains
//		cout << "Brain 1:\n\n";
//		BrainTest::DisplaySynapses(brain1.neurons_,10);
//		cout << "Brain 2:\n\n";
//		BrainTest::DisplaySynapses(brain2.neurons_,10);

//		Brain brain3 = evolution1.MateBrains(brain1, brain2);

//		cout << "Mated Brain:\n";
//		BrainTest::DisplaySynapses(brain3.neurons_,10);

	////Test choose most fit brains
	Brain brain3 = brain1;
	brain1.set_fitness_score(2);
	brain2.set_fitness_score(1);
	brain3.set_fitness_score(0);
	deque<Brain> brain_population = {brain1, brain2, brain3, brain3, brain3};
	evolution1.ChooseMostFitBrains(brain_population);
	//Due to quadratic scaling of fitness scores, brain1 should appear 4 times
	//and brain2 only 1 time
	if (std::count(evolution1.most_fit_brains_.begin(), evolution1.most_fit_brains_.end(), 0) != 4 or
	    std::count(evolution1.most_fit_brains_.begin(), evolution1.most_fit_brains_.end(), 1) != 1)
		std::cerr << "ERROR: most_fit_brains_ was not as expected!!\n";

}
