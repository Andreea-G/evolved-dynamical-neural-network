/*
 *  Created on: July 7, 2014
 *  Authors: Andreea G, Garrett R
 */

#ifndef MAZEMASTER__MAZEMASTER_H_
#define MAZEMASTER__MAZEMASTER_H_

#include <deque>
#include <src/brain/Brain.hpp>
#include <src/evolution/Evolution.hpp>
#include <src/tasks/MazeTask.hpp>
#include <mutex>
#include <condition_variable>

using std::deque;
using std::string;

class MazeMaster {

public:
	//For now, main() will only call this constructor.  In the future, we may allow the above constructor to be invoked.
	MazeMaster(const size_t num_brains,
	           const size_t num_neurons, const size_t num_input_neurons, const size_t num_output_neurons,
	           const float av_active_threshold, const float st_dev_active_threshold,
	           const float av_start_activation, const float st_dev_start_activation,
	           const float av_decay_rate, const float st_dev_decay_rate,
	           const int av_num_syn, const int st_dev_num_syn,
	           const float av_syn_strength, const float st_dev_syn_strength,
	           const int max_decisions, const int input_duration,
	           const int input_output_delay, const int output_duration,
	           const int deadtime_duration,
	           const string maze_map_file, const bool maze_random_start,
	           const int num_generations, const size_t num_mutated_neurons, const size_t num_mutated_synapses,
	           const float prob_asexual, const bool mutate_decay_rate, const bool mutate_active_threshold,
	           const int max_num_threads);

	//Loop through all brains calling ObtainBrainFitness(.) to get calculate the fitness_score_ for each brain.
	//Returns -1 if it fails and 0 otherwise.
	void ObtainAllBrainFitnesses();
	void ObtainBrainFitness(Brain& brain);

	//This is the function that main() will call.  We don't parse args in main(), because the args here are specific to
	//the maze task and in the future, we may have additional tasks in which case, we'll need different argument parsing.
	static int ParseMazeArgsAndExecute(int argc, char** argv);

	//Loop through the number of generations. For each generation, get the fitness scores of brains,
	//find the most fit brains, and get the next generation. Return 0 if no errors were found, or -1 otherwise
	int MasterControl();


private:
	//for brains:
	const size_t num_brains_;

	//These parameters get used when we reset a brain's current activation
	const float av_start_activation_;
	//WARNING: st_dev_start_activation_ parameter should probably be zero.  If it's non-zero, then each time the brain
	//resets, it resets to something different, so unless you know what you're doing, then keep it at zero.
	// see the declaration of Brain::ResetStartActivations(.) for details.
	const float st_dev_start_activation_;  //for our argument parsing, let's not allow the user to specify this...

	//for brain cycles:
	const int max_decisions_;
	//number of cycles that input is given to brain for, for each input from the task
	const int input_duration_;
	//number of cycles between start of input and start of recording the output
	const int input_output_delay_;
	//number of cycles that output is read for
	const int output_duration_;
	//number of cycles after the brain finished giving output, and before the next input
	const int deadtime_duration_;

	//for the task
	const string maze_map_file_;
	const bool maze_random_start_;

	//for evolution:
	Evolution evolution_;
	const int num_generations_;
	const size_t num_mutated_neurons_;
	const size_t num_mutated_synapses_;

	//during evolution, these say if the decay rate and active_threshold of a mutated neuron also get mutated
	const bool mutate_decay_rate_, mutate_active_threshold_;

	//The max number of threads to be used (ObtainAllBrainFitnesses spawns new threads)
	//const int max_num_threads_;
	int max_num_threads_;

	deque<Brain> brains_;

	std::mutex mtx_;
	int num_live_threads_;
	//In order to limit the number of concurrent threads, we use condition variable
	std::condition_variable num_threads_cv_;	

	//Reset the activation of all brains.  This is important to do because if you don't, then a brain that did well
	//in the last round may do poorly in the following round (supposing they somehow got to the next generation w/o
	//mutations) just due to the fact that it's starting the maze in a different "state of mind"
	void ResetAllBrainStartActivations();

	void PrintGenerationInfo();
};

#endif /* MAZEMASTER__MAZEMASTER_H_ */
