#include <src/testing/GameMasterTest.hpp>
#include <src/gamemaster/GameMaster.hpp>
#include <src/brain/Brain.hpp>
#include <src/evolution/Evolution.hpp>
#include <src/tasks/MazeTask.hpp>
#include <src/Globals.hpp>
#include <iostream>
#include <fstream>


using std::cout;
using std::cerr;
using std::endl;
using std::string;

void GameMasterTest::Test1() {

	size_t num_brains = 3;
	size_t num_neurons = 800;  //These settings gave a non-repeating brain!
	const float av_active_threshold = 0.25; const float st_dev_active_threshold = 0.04;
	const float av_start_activation = 0.25 ; const float st_dev_start_activation = 0.05;
	const float av_decay_rate = 0.001; const float st_dev_decay_rate = 0.0003;
	const int av_num_syn = 10; const int st_dev_num_syn = 2;
	const float av_syn_strength = 0.05; const float st_dev_syn_strength = 0.04;

	const int max_decisions = 1000;
	const int input_duration = 10;
	const int input_output_delay = 5;
	const int output_duration = 10;

	const string maze_map_file = "maze_files/test_maze1";
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

	output::PrintGenerationInfo(test_GameMaster1.brains_);

	int test = test_GameMaster1.MasterControl();
	if (test == -1) {
		std::cerr << "-1 returned by MasterControl!\n";
	}
}

void GameMasterTest::Test2() {
	//This one is done by Garry

	size_t num_brains = 5;
	size_t num_neurons = 800;  //These settings gave a non-repeating brain!
	const float av_active_threshold = 0.25; const float st_dev_active_threshold = 0.04;
	const float av_start_activation = 0.25 ; const float st_dev_start_activation = 0.05;
	const float av_decay_rate = 0.001; const float st_dev_decay_rate = 0.0003;
	const int av_num_syn = 10; const int st_dev_num_syn = 2;
	const float av_syn_strength = 0.05; const float st_dev_syn_strength = 0.04;

	const int max_decisions = 1000;
	const int input_duration = 10;
	const int input_output_delay = 5;
	const int output_duration = 10;

	//const string maze_map_file = "maze_files/test_maze1";
	//const string maze_map_file = "maze_files/test_maze2"; //Garrett's testing maze
	const string maze_map_file = "maze_files/example_maze1"; //Garrett's testing maze
	const bool maze_random_start = false;

	const int num_generations = 3;
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

	output::PrintGenerationInfo(test_GameMaster1.brains_);

	int test = test_GameMaster1.MasterControl();
	if (test == -1) {
		std::cerr << "-1 returned by MasterControl!\n";
	}
}

