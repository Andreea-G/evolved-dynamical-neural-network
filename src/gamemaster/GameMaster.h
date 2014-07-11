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

class GameMaster {

public:
	//Loop through all brains, and find the fitness_score_ for each brain.
	void ObtainBrainFitnesses();

	//Loop through the number of generations. For each generation, get the fitness scores of brains,
		//find the most fit brains, and get the next generation. Return 0 if no errors were found, or -1 otherwise
	int MasterControl();

	friend void PrintGenerationInfo();

private: //TODO: many of these should be const
	//for brains:
    deque<Brain> brains_;

	//for brain cycles:
	int max_decisions_;
	int input_duration_, input_output_delay_, output_duration_;

	//for the task
	std::string maze_map_file_;
    bool maze_random_start_;

	//for evolution:
	Evolution evolution_;
	int num_generations_;
	int num_mutated_neurons_, num_mutated_synapses_;
};



#endif /* GAMEMASTER__MAGEMASTER_H_ */
