/*
 * GameMaster.cc
 *
 *  Created on: June 7, 2014
 *      Author: Andreea
 */

#include <iostream>
#include "gamemaster.h"
#include "../Globals.h" //TODO: find better way for this include
#include <unordered_map>
#include <map>
#include <algorithm> //std::sort

using std::deque;
using std::unordered_map;

//Ref: http://stackoverflow.com/questions/5056645/sorting-stdmap-using-value
namespace flipMap {
    //Flip a pair
    template<typename A, typename B>
    std::pair<B, A> flip_pair(const std::pair<A, B> &input_pair)
    {
        return std::pair<B, A>(input_pair.second, input_pair.first);
    }

    //Turn an unordered map into a flipped multimap, sorted in decreasing order
    template<typename A, typename B>
    std::multimap<B, A> flip_unordered_map(const std::unordered_map<A,B> &input_map)
    {
        std::multimap<B, A, std::greater<B>> output_map;
        std::transform(input_map.begin(), input_map.end(), std::inserter(output_map, output_map.begin()),
                       flip_pair<A, B>);
        return output_map;
    }
}

void ObtainBrainFitnesses() {
    for (auto brain_it = brains_.begin(); brain_it != brains_.end(); brain_it++) {
        int num_decisions = max_decisions;
        MazeTask maze_task(maze_map_file_, maze_random_start_);

        //Loop through every decision the brain must make
        for (int decision = 0; decision < max_decisions_; decision++) {
            //Advance position from the starting line
            if (!maze_task.AdvancePosition()) {
                //Brain couldn't go anywhere from the start; receive worst fitness score
                break;
            }

            //Check if brain has finished the maze
            if (maze_task.IsFinished()) {
                num_decisions = decision;
                break;
            }

            //Get brain input
            deque<bool> brain_input = maze_task.GetBrainInput();

            //Let the brain decide on an action
            //The first element in the map is an output of the brain, while the second is counting how many times times
                //the brain has given this output
            unordered_map<deque<bool>,int> brain_output_frequency;
            for (int cycle = 0; cycle < (input_output_delay_ + output_duration_); cycle++) {
                if (cycle < input_duration_) {
                    brain_it->give_input(brain_input) //give input to brain
                }
                brain_it->Cycle();
                if (cycle >= input_output_delay) {
                    deque<bool> brain_output = brain_it->get_output();
                    if (brain_output_frequency[brain_output].count()) { //this brain_output is already in the map
                        brain_output_frequency[brain_output]++; //increase the frequency
                    } else {
                        brain_output_frequency[brain_output] = 1;
                    }
                }
            }

            //Test the brain_outputs in order of the frequency, and try to find the first valid output (that doesn't send the brain into a wall)
            //flip the unordered_map of <brain_output,frequency> to a multimap <frequency,brain_output> (which is now sorted by its frequency
            multimap<int, deque<bool>> brain_output_sorted = flipMap::flip_unordered_map(brain_output_frequency);
            bool found_valid_decision = false;
            deque<bool> brain_output;
            for (auto output_it = brain_output_sorted.begin(); output_it != brain_output_sorted.end(); output_it++) {
                if (maze_task.ActOnDecision(output_it->second)) { //succes! the brain has found a valid decision
                    found_valid_decision = true;
                    brain_output = output_it->second;
                    break;
                }
            }

            //If no valid decision has been found, brain decided to go into a wall, so it gets the worst fitness score
            if (!found_valid_decision) {
                break;
            }
        } //end for loop through decisions

        //Set fitness score to 1/num_decisions
        brain_it->fitness_score_ = 1/num_decisions;

    } //end for loop through every brain
}

