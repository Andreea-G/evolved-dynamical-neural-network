#include <iostream>
#include "EvolutionTest.h"
#include "../evolution/Evolution.h"
#include "../testing/BrainTest.h"

using std::cout;
using std::endl;

EvolutionTest::EvolutionTest()
{
}

void EvolutionTest::test1() {
	Evolution evolution1;

		const int num_neurons=10;
		const float av_active_threshold=25; const float st_dev_active_threshold=0;
		const float av_start_activation=25 ; const float st_dev_start_activation=0;
		const float av_decay_rate=0.05; const float st_dev_decay_rate=0.0;
		const int av_num_syn=4; const int st_dev_num_syn=0;
		const float av_syn_strength=28; const float st_dev_syn_strength=0;
		Brain brain1(num_neurons, 3, 2,  //Problem: creating variable number of synapses!!
									av_active_threshold, st_dev_active_threshold,
									av_start_activation, st_dev_start_activation,
									av_decay_rate, st_dev_decay_rate,
									av_num_syn, st_dev_num_syn,
									av_syn_strength, st_dev_syn_strength);

		const int num_neurons2=10;
		const float av_active_threshold2=35; const float st_dev_active_threshold2=0;
		const float av_start_activation2=35 ; const float st_dev_start_activation2=0;
		const float av_decay_rate2=0.1; const float st_dev_decay_rate2=0.0;
		const int av_num_syn2=6; const int st_dev_num_syn2=0;
		const float av_syn_strength2=22; const float st_dev_syn_strength2=0;
		Brain brain2(num_neurons2, 3, 2,
									av_active_threshold2, st_dev_active_threshold2,
									av_start_activation2, st_dev_start_activation2,
									av_decay_rate2, st_dev_decay_rate2,
									av_num_syn2, st_dev_num_syn2,
									av_syn_strength2, st_dev_syn_strength2);

		goto skip_to;

//		BrainTest::DisplaySynapses(brain1.neurons_, 10);

//		cout << "OK, mutating..." << endl;
//		Brain mutated_brain = evolution1.MutateBrain(brain1, 1, 2);

//		BrainTest::DisplaySynapses(mutated_brain.neurons_, 10);

	skip_to:
		{}

		cout << "Brain 1:\n\n";
		BrainTest::DisplaySynapses(brain1.neurons_,10);
		cout << "Brain 2:\n\n";
		BrainTest::DisplaySynapses(brain2.neurons_,10);

}
