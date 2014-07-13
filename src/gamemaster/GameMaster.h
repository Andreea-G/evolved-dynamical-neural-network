/*
 * GameMaster.h
 *
 *  Created on: July 7, 2014
 *      Author: Andreea
 */

#ifndef GAMEMASTER__GAMEMASTER_H_
#define GAMEMASTER__GAMEMASTER_H_

#include <deque>
#include "../brain/Brain.h"
#include "../evolution/Evolution.h"
#include "../tasks/MazeTask.h"
#include <map>
//#include <unordered_map>

using std::deque;
using std::string;

class GameMaster {

public:
	GameMaster(const size_t num_brains,
			   const size_t num_neurons, const size_t num_input_neurons, const size_t num_output_neurons,
			   const int max_decisions,
			   const int input_duration, const int input_output_delay, const int output_duration,
			   const string maze_map_file, const int maze_random_start,
			   const int num_generations, const size_t num_mutated_neurons, const size_t num_mutated_synapses,
			   const float prob_asexual);

	GameMaster(const size_t num_brains,
			   const size_t num_neurons, const size_t num_input_neurons, const size_t num_output_neurons,
			   const float av_active_threshold, const float st_dev_active_threshold,
			   const float av_start_activation, const float st_dev_start_activation,
			   const float av_decay_rate, const float st_dev_decay_rate,
			   const int av_num_syn, const int st_dev_num_syn,
			   const float av_syn_strength, const float st_dev_syn_strength,
			   const int max_decisions,
			   const int input_duration, const int input_output_delay, const int output_duration,
			   const string maze_map_file, const int maze_random_start,
			   const int num_generations, const size_t num_mutated_neurons, const size_t num_mutated_synapses,
			   const float prob_asexual);

	//Loop through all brains, and find the fitness_score_ for each brain.
	void ObtainBrainFitnesses();

	//Loop through the number of generations. For each generation, get the fitness scores of brains,
		//find the most fit brains, and get the next generation. Return 0 if no errors were found, or -1 otherwise
	int MasterControl();

	deque<Brain> brains_;

private: //TODO: many of these should be const
	//for brains:
	size_t num_brains_;

	//for brain cycles:
	int max_decisions_;
	int input_duration_, input_output_delay_, output_duration_;

	//for the task
	string maze_map_file_;
    bool maze_random_start_;

	//for evolution:
	Evolution evolution_;
	int num_generations_;
	size_t num_mutated_neurons_, num_mutated_synapses_;

	//friend void PrintGenerationInfo(const deque<Brain> brains);
};



#endif /* GAMEMASTER__MAGEMASTER_H_ */
