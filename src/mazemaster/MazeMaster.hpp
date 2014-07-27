/*
 * MazeMaster.h
 *
 *  Created on: July 7, 2014
 *      Author: Andreea
 */

#ifndef MAZEMASTER__MAZEMASTER_H_
#define MAZEMASTER__MAZEMASTER_H_

#include <deque>
#include <src/brain/Brain.hpp>
#include <src/evolution/Evolution.hpp>
#include <src/tasks/MazeTask.hpp>
//#include <unordered_map>

using std::deque;
using std::string;

class MazeMaster {

public:
	//TODO: should we delete this constructor if main() won't be using it?
	/*
	MazeMaster(const size_t num_brains,
			   const size_t num_neurons, const size_t num_input_neurons, const size_t num_output_neurons,
			   const int max_decisions,
			   const int input_duration, const int input_output_delay, const int output_duration,
			   const string maze_map_file, const int maze_random_start,
			   const int num_generations, const size_t num_mutated_neurons, const size_t num_mutated_synapses,
			   const float prob_asexual);
	*/

	//For now, main() will only call this constructor.  In the future, we may allow the above constructor to be invoked.
	MazeMaster(const size_t num_brains,
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
						const float prob_asexual, const bool mutate_decay_rate = true, const bool mutate_active_threshold = true);

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

	//These parameters get used when we reset a brain's current activation
	const float av_start_activation_;
	//WARNING: this parameter should probably be zero.  If it's non-zero, then each time the brain resets,
	//it resets to something different, so unless you know what you're doing, then keep it at zero.
	const float st_dev_start_activation_;  //TODO: for our argument parsing, let's not allow the user to specify this...
	//Reset the activation of all brains.  This is important to do because if you don't, then a brain that did well
	//in the last round may do poorly in the following round (supposing they somehow got to the next generation w/o
	//mutations) just due to the fact that it's starting the maze in a different "state of mind"
	void ResetAllBrainStartActivations();

	//for brain cycles:
	const int max_decisions_;
	//number of cycles that input is given to brain for, for each input from the task
	const int input_duration_;
	//number of cycles between start of input and start of recording the output
	const int input_output_delay_;
	//number of cycles that output is read for
	const int output_duration_;

	//TODO: add deadtime_duration_

	//for the task
	const string maze_map_file_;
	const bool maze_random_start_;

	//for evolution:
	Evolution evolution_;
	const int num_generations_;
	const size_t num_mutated_neurons_, num_mutated_synapses_;
	//during evolution, these say if the decay rate and active_threshold of a mutated neuron also get mutated
	const bool mutate_decay_rate_, mutate_active_threshold_;

	void PrintGenerationInfo();
};


#endif /* MAZEMASTER__MAZEMASTER_H_ */
