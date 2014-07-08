/*
 * GameMaster.cc
 *
 *  Created on: June 7, 2014
 *      Author: Andreea
 */

#include <iostream>
#include "GameMaster.h"
#include "../Globals.h" //TODO: find better way for this include
//#include <algorithm> //std::transform

using std::deque;
using std::map;
//using std::unordered_map;
using std::multimap;
using std::pair;


void GameMaster::ObtainBrainFitnesses() {
   for (auto brain_it = brains_.begin(); brain_it != brains_.end(); brain_it++) {
	   //Default to worst outcome. If the brain doesn't finish the maze in max_decisions_ time then it receives the worst score.
		int num_decisions = max_decisions_;

        MazeTask maze_task(maze_map_file_, maze_random_start_);

        //Loop through every decision the brain must make
		for (int decision = 0; decision < max_decisions_; decision++) {
			//Advance position through the maze (either from the starting line or from the previous decision)
            if (!maze_task.AdvancePosition()) {
				//Brain tried to enter a wall; receive worst fitness score
                break;
            }

            //Check if brain has finished the maze
            if (maze_task.IsFinished()) {
                num_decisions = decision;
                break;
            }

			//Get brain input (which are the possible directions from this position)
            deque<bool> brain_input = maze_task.GetBrainInput();

            //Let the brain decide on an action
			//The first element in the map is an output of the brain, while the second is counting how many times
                //the brain has given this output
			//TODO: this doesn't need to be an ordered map, but if I try to make it unordered_map I get errors later. Don't fully understand why.
			map<deque<bool>, int> brain_output_frequency;
            for (int cycle = 0; cycle < (input_output_delay_ + output_duration_); cycle++) {
                if (cycle < input_duration_) {
					brain_it->give_input(brain_input); //give input to brain at each cycle
                }
                brain_it->Cycle();
				if (cycle >= input_output_delay_) {
					deque<bool> brain_output = brain_it->get_output();	//output given at the current cycle
					if (brain_output_frequency.count(brain_output)) { //this brain_output is already in the map
                        brain_output_frequency[brain_output]++; //increase the frequency
					} else { //this output appears for the first time
                        brain_output_frequency[brain_output] = 1;
                    }
                }
            }

			//Test the brain_outputs in order of the frequency, and try to find the first (namely most common) valid output (that doesn't send the brain into a wall)
			//flip the map of <brain_output, frequency> to a multimap <frequency, brain_output> (which is now sorted by its frequency
			multimap<int, deque<bool>> brain_output_sorted;
			for (auto map_it = brain_output_frequency.begin(); map_it != brain_output_frequency.end(); map_it++) {
				brain_output_sorted.insert( pair<int, deque<bool> >(map_it->second, map_it->first) );
			}
			bool found_valid_decision = false;
			deque<bool> brain_decision; //final (most common and valid) brain output will correspond to the decision
            for (auto output_it = brain_output_sorted.begin(); output_it != brain_output_sorted.end(); output_it++) {
				if (maze_task.ActOnDecision(output_it->second)) { //succes! the brain has found a valid decision, and the brain has turned in the new direction
                    found_valid_decision = true;
					brain_decision = output_it->second;
                    break;
                }
            }

			//If no valid decision has been found, the brain decided to go into a wall, so it gets the worst fitness score
            if (!found_valid_decision) {
                break;
            }
		} //end for loop through decisions

        //Set fitness score to 1/num_decisions
		brain_it->set_fitness_score(1.0/num_decisions);

	} //end for loop through every brain
}


