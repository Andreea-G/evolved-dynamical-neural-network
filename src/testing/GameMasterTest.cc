#include "GameMasterTest.h"
#include "../gamemaster/GameMaster.h"
#include "../brain/Brain.h"
#include "../evolution/Evolution.h"
#include "../tasks/MazeTask.h"
#include "../Globals.h"
#include <iostream>
#include <fstream>


using std::cout;
using std::cerr;
using std::endl;
using std::string;

void GameMasterTest::Test1() {
	size_t num_brains = 10;
	size_t num_neurons = 1000;

	const float av_active_threshold = 25; const float st_dev_active_threshold = 4;
	const float av_start_activation = 25 ; const float st_dev_start_activation = 5;
	const float av_decay_rate = 0.05; const float st_dev_decay_rate = 0.02;
	const int av_num_syn = 4; const int st_dev_num_syn = 2;
	const float av_syn_strength = 28; const float st_dev_syn_strength = 4;

	const int max_decisions = 100000;
	const int input_duration = 10;
	const int input_output_delay = 10;
	const int output_duration = 10;

	const string maze_map_file = "maze_files/test_maze";
	const bool maze_random_start = false;

	const int num_generations = 100;
	const size_t num_mutated_neurons = 1;
	const size_t num_mutated_synapses = 2;

	const float prob_asexual = 0.1;

	GameMaster test_GameMaster1(num_brains, num_neurons, 3, 2,
								av_active_threshold, st_dev_active_threshold,
								av_start_activation, st_dev_start_activation,
								av_decay_rate, st_dev_decay_rate,
								av_num_syn, st_dev_num_syn,
								av_syn_strength, st_dev_syn_strength,
								max_decisions,
								input_duration, input_output_delay, output_duration,
								maze_map_file, maze_random_start,
								num_generations, num_mutated_neurons, num_mutated_synapses,
								prob_asexual);

//	test_GameMaster1.ObtainBrainFitnesses();
//	std::cout << "Finished ObtainBrainFitnesses\n";

	PrintGenerationInfo(test_GameMaster1.brains_);

	int test = test_GameMaster1.MasterControl();
	if (test == -1) {
		std::cerr << "-1 returned by MasterControl!\n";
	}

}

