/*
 * GameMaster.h
 *
 *  Created on: July 7, 2014
 *      Author: Andreea
 */

#ifndef GAMEMASTER__GAMEMASTER_H_
#define GAMEMASTER__GAMEMASTER_H_

#include <deque>
#include <src/brain/Brain.hpp>
#include <src/evolution/Evolution.hpp>
#include <src/tasks/MazeTask.hpp>
//#include <unordered_map>

using std::deque;
using std::string;

class GameMaster {

public:
	//TODO: should we delete this constructor if main() won't be using it?
	/*
	GameMaster(const size_t num_brains,
			   const size_t num_neurons, const size_t num_input_neurons, const size_t num_output_neurons,
			   const int max_decisions,
			   const int input_duration, const int input_output_delay, const int output_duration,
			   const string maze_map_file, const int maze_random_start,
			   const int num_generations, const size_t num_mutated_neurons, const size_t num_mutated_synapses,
			   const float prob_asexual);
	*/

	//For now, main() will only call this constructor.  In the future, we may allow the above constructor to be invoked.
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
	//Returns -1 if it fails and 0 otherwise.
	int ObtainBrainFitnesses();

	//Loop through the number of generations. For each generation, get the fitness scores of brains,
	//find the most fit brains, and get the next generation. Return 0 if no errors were found, or -1 otherwise
	int MasterControl();

	deque<Brain> brains_;

private:
	//for brains:
	const size_t num_brains_;

	//for brain cycles:
	const int max_decisions_;
	//number of cycles that input is given to brain for, for each input from the task
	const int input_duration_;
	//number of cycles between start of input and start of recording the output
	const int input_output_delay_;
	//number of cycles that output is read for
	const int output_duration_;

	//for the task
	const string maze_map_file_;
	const bool maze_random_start_;

	//for evolution:
	Evolution evolution_;
	const int num_generations_;
	const size_t num_mutated_neurons_, num_mutated_synapses_;

	//friend void PrintGenerationInfo(const deque<Brain> brains);
};

namespace output {
	void PrintGenerationInfo(const deque<Brain> brains);
}


#endif /* GAMEMASTER__MAGEMASTER_H_ */
