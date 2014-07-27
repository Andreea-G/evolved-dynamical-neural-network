/*
 * MazeMaster.cc
 *
 *  Created on: June 7, 2014
 *      Author: Andreea
 */

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

#include <tclap/CmdLine.h>
#include <src/mazemaster/MazeMaster.hpp>
#include <src/Globals.hpp>

using std::deque;
using std::map;
using std::multimap;
using std::pair;
using std::cout;
using std::endl;

//Don't change these - the maze task passes 3 bits to the brain and expects 2 bits back (see MazeTask.hpp for more),
const size_t num_input_neurons = 3;
const size_t num_output_neurons = 2;


int MazeMaster::ParseMazeArgsAndExecute(int argc, char** argv) {
	try {
		//CmdLine parser object
		TCLAP::CmdLine cmd("Evolved Dynamical Neural Net for solving mazes", ' ', "0.1");

		//Collect all arguments
		TCLAP::ValueArg<int> num_brains_arg("N", "num_brains", "Number of brains in each generation", true, 0, "int", cmd);
		TCLAP::ValueArg<int> num_neurons_arg("n", "num_neurons", "Number of neuron in each brain", true, 0, "int", cmd);
//		TCLAP::ValueArg<int> num_input_neurons_arg("i", "num_input_neurons", "Number of input neuron in each brain", true, 0, "int", cmd); TODO delete this
//		TCLAP::ValueArg<int> num_output_neurons_arg("o", "num_output_neurons", "Number of output neuron in each brain", true, 0, "int", cmd);

		TCLAP::ValueArg<float> av_active_threshold_arg("a", "av_active_threshold", "Average activation threshold for each neruon", true, 0, "float", cmd);
		TCLAP::ValueArg<float> st_dev_active_threshold_arg("A", "st_dev_active_threshold", "Standard deviation for activation threshold for each neruon", true, 0, "float", cmd);
		//Don't ask user for st_dev_start_activation since that's dangerous, see declaration of st_dev_start_activation_ in MazeMaster.hpp for details.
		TCLAP::ValueArg<float> av_start_activation_arg("s", "start_activation", "Start activation for each neruon (at beginning of maze)", true, 0, "float", cmd);
		TCLAP::ValueArg<float> av_decay_rate_arg("d", "av_decay_rate", "Average decay rate for each neruon", true, 0, "float", cmd);
		TCLAP::ValueArg<float> st_dev_decay_rate_arg("D", "st_dev_decay_rate", "Standard deviation for decay rate for each neruon", true, 0, "float", cmd);
		TCLAP::ValueArg<float> av_num_syn_arg("y", "av_num_syn", "Average number of synapses for each neruon", true, 0, "float", cmd);
		TCLAP::ValueArg<float> st_dev_num_syn_arg("Y", "st_dev_num_syn", "Standard deviation of number of synapses for each neruon", true, 0, "float", cmd);
		TCLAP::ValueArg<float> av_syn_strength_arg("r", "av_syn_strength", "Average synapse strength for each neruon", true, 0, "float", cmd);
		TCLAP::ValueArg<float> st_dev_syn_strength_arg("R", "st_dev_syn_strength", "Standard deviation of synapse strength for each neruon", true, 0, "float", cmd);

		TCLAP::ValueArg<int> max_decisions_arg("m", "max_decisions", "Maximum allowed decision before a brain receives worst fitness score", true, 0, "int", cmd);
		TCLAP::ValueArg<int> input_duration_arg("I", "input_duration", "Duration of input signal in cycles", true, 0, "int", cmd);
		TCLAP::ValueArg<int> input_output_delay_arg("e", "input_output_delay", "Number of cycles between start of input and start of output", true, 0, "int", cmd);
		TCLAP::ValueArg<int> output_duration_arg("O", "output_duration", "Duration of output signal in cycles", true, 0, "int", cmd);

		TCLAP::ValueArg<std::string> maze_map_file_arg("M", "maze_map_file", "The maze filepath, see docs for expected file format", true, "", "string", cmd);
		TCLAP::SwitchArg maze_random_start_arg("x", "maze_random_start", "Have players start at random points in maze (you should probably not use this)", cmd, false);

		TCLAP::ValueArg<int> num_generations_arg("g", "num_generations", "Number of generations", true, 0, "int", cmd);
		TCLAP::ValueArg<size_t> num_mutated_neurons_arg("u", "num_mutated_neurons", "Number of mutated neurons each time a brain is mutated", true, 0, "int", cmd);
		TCLAP::ValueArg<size_t> num_mutated_synapses_arg("U", "num_mutated_synapses", "Number of mutated synapses in each mutated neuron", true, 0, "int", cmd);
		TCLAP::ValueArg<float> prob_asexual_arg("X", "prob_asexual", "Probability of each brain coming from asexual reproduction", true, 0, "float", cmd);
		TCLAP::SwitchArg mutate_decay_rate_arg("v", "mutate_decay_rate", "Mutate the decay rate everytime a neuron gets mutated", cmd, false);
		TCLAP::SwitchArg mutate_active_threshold_arg("V", "active_threshold", "Mutate the active threshold everytime a neuron gets mutated", cmd, false);

		TCLAP::ValueArg<int> max_num_threads_arg("t", "max_num_threads", "Max number of threads to use", false, 1, "int", cmd);


		cmd.parse(argc, argv);

		//rename arguments
		const size_t num_brains = num_brains_arg.getValue();
		const size_t num_neurons = num_neurons_arg.getValue();
		const float av_active_threshold = av_active_threshold_arg.getValue();
		const float st_dev_active_threshold = st_dev_active_threshold_arg.getValue();
		const float av_start_activation = av_start_activation_arg.getValue();
		//See note in the declaration of st_dev_start_activation_ in MazeMaster.hpp for reason why this is 0.0
		const float st_dev_start_activation = 0.0;
		const float av_decay_rate = av_decay_rate_arg.getValue();
		const float st_dev_decay_rate = st_dev_decay_rate_arg.getValue();
		const int av_num_syn = av_num_syn_arg.getValue();
		const int st_dev_num_syn = st_dev_num_syn_arg.getValue();
		const float av_syn_strength = av_syn_strength_arg.getValue();
		const float st_dev_syn_strength = st_dev_syn_strength_arg.getValue();
		const int max_decisions = max_decisions_arg.getValue();
		const int input_duration = input_duration_arg.getValue();
		const int input_output_delay = input_output_delay_arg.getValue();
		const int output_duration = output_duration_arg.getValue();
		const string maze_map_file = maze_map_file_arg.getValue();
		const bool maze_random_start = maze_random_start_arg.getValue();
		const int num_generations = num_generations_arg.getValue();
		const size_t num_mutated_neurons = num_mutated_neurons_arg.getValue();
		const size_t num_mutated_synapses = num_mutated_synapses_arg.getValue();
		const float prob_asexual = prob_asexual_arg.getValue();
		const bool mutate_decay_rate = mutate_decay_rate_arg.getValue();
		const bool mutate_active_threshold = mutate_active_threshold_arg.getValue();
		const int max_num_threads = max_num_threads_arg.getValue();

		//TODO error check for limits

		MazeMaster main_maze_master(num_brains,	num_neurons, num_input_neurons, num_output_neurons,	av_active_threshold,
																st_dev_active_threshold, av_start_activation, st_dev_start_activation, av_decay_rate,
																st_dev_decay_rate, av_num_syn, st_dev_num_syn, av_syn_strength, st_dev_syn_strength,
																max_decisions, input_duration, input_output_delay, output_duration,
																maze_map_file, maze_random_start, num_generations, num_mutated_neurons,
																num_mutated_synapses,	prob_asexual, mutate_decay_rate, mutate_active_threshold,
																max_num_threads);

		return main_maze_master.MasterControl();

	} catch (TCLAP::ArgException &e) {
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
	}

	return -1; //program shouldn't get here.
}


MazeMaster::MazeMaster(const size_t num_brains,
					const size_t num_neurons, const size_t num_input_neurons, const size_t num_output_neurons,
					const float av_active_threshold, const float st_dev_active_threshold,
					const float av_start_activation, const float st_dev_start_activation,
					const float av_decay_rate, const float st_dev_decay_rate,
					const int av_num_syn, const int st_dev_num_syn,
					const float av_syn_strength, const float st_dev_syn_strength,
					const int max_decisions, const int input_duration,
					const int input_output_delay, const int output_duration,
					const string maze_map_file, const bool maze_random_start,
					const int num_generations, const size_t num_mutated_neurons, const size_t num_mutated_synapses,
					const float prob_asexual, const bool mutate_decay_rate, const bool mutate_active_threshold,
					const int max_num_threads) :
					num_brains_(num_brains),
					av_start_activation_(av_start_activation), st_dev_start_activation_(st_dev_start_activation),
					max_decisions_(max_decisions),
					input_duration_(input_duration), input_output_delay_(input_output_delay),
					output_duration_(output_duration), maze_map_file_(maze_map_file),
					maze_random_start_(maze_random_start), num_generations_(num_generations),
					num_mutated_neurons_(num_mutated_neurons), num_mutated_synapses_(num_mutated_synapses),
					evolution_(prob_asexual),
					mutate_decay_rate_(mutate_decay_rate), mutate_active_threshold_(mutate_active_threshold),
					max_num_threads_(max_num_threads), num_live_threads_(0) {
	//construct brains
	for (size_t ii = 0; ii < num_brains_; ii++) {
		Brain new_brain(num_neurons, num_input_neurons, num_output_neurons,
						av_active_threshold, st_dev_active_threshold,
						av_start_activation, st_dev_start_activation,
						av_decay_rate, st_dev_decay_rate,
						av_num_syn, st_dev_num_syn,
						av_syn_strength, st_dev_syn_strength);
		brains_.push_back(new_brain);
	}

}


int MazeMaster::MasterControl() {
	for (int generation = 0; generation < num_generations_; generation++) {
		cout << "Generation " << generation << std::endl;
		int exit_status = ObtainAllBrainFitnesses();
		if (exit_status < 0) {
			return -1;
		}

		PrintGenerationInfo();

		//find the list of most fit brains
		exit_status = evolution_.ChooseMostFitBrains(brains_);
		if (exit_status < 0) {
			return -1;
		}

		//Obtain the next generation of brains, and print info on the parents
		brains_ = evolution_.GetNextGeneration(brains_, num_mutated_neurons_, num_mutated_synapses_, num_brains_,
																					 mutate_decay_rate_, mutate_active_threshold_);

		ResetAllBrainStartActivations();
	}

	return 0;
}


int MazeMaster::ObtainAllBrainFitnesses() {
	//threads, each one will calculate the fitness for 1 brain
	std::vector<std::thread> threads;
	//Loop through each brain
	for (Brain& brain : brains_) {
		std::unique_lock<std::mutex> num_threads_lock(mtx_);
		num_threads_cv_.wait(num_threads_lock, [&](){
					return num_live_threads_ < max_num_threads_;
		});

		threads.push_back(std::thread(&MazeMaster::ObtainBrainFitness, this, std::ref(brain)));
		num_live_threads_++;
	}

	for (auto& thread : threads) {
		thread.join();
	}

	return 0;  //TODO: should we just set this to void return?  We're not actually returning any useful exit code.
}


void MazeMaster::ObtainBrainFitness(Brain& brain) {
	//Default to worst outcome. If the brain doesn't finish the maze in max_decisions_ time then it receives the worst score.
	int num_decisions = max_decisions_;

	//TODO: after profiling code, determine if creating this object and loading the maze each time costing us too much?
	//if so, we could make a single maze_task and implement a "reset" function that puts the player back to start.
	//Although the disadvantage to having a single loading map file would be that we'd have to add a bunch of mutexes to
	//avoid access conflicts.
	MazeTask maze_task(maze_map_file_, maze_random_start_);

	//Loop through every decision the brain must make
	for (int decision = 0; decision < max_decisions_; decision++) {
		//Advance position through the maze (either from the start or from the previous loop's decision)
		if (!maze_task.AdvancePosition()) {
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
		map<deque<bool>, int> brain_output_frequencies;

		//Loop through brain cycles, looping enough times to collect all the input and all the output for one decision
		for (int cycle = 0; cycle < (input_output_delay_ + output_duration_); cycle++) {
			//if we're still in the input period, give input to brain at each cycle
			if (cycle < input_duration_) {
				brain.give_input(brain_input);
			}

			brain.Cycle();

			//if we're in the output period, store the output for each cycle into brain_output
			if (cycle >= input_output_delay_) {
				deque<bool> brain_output = brain.get_output();

				//check if this brain_output is already in the map and if so add 1 to its current frequency,
				//otherwise add it to the map
				if (brain_output_frequencies.count(brain_output)) {
					brain_output_frequencies[brain_output]++;
				} else {
					brain_output_frequencies[brain_output] = 1;
				}
			}
		}

		//Test the brain_outputs in order of the frequency, and try to find the most common valid output
		//(that doesn't send the brain into a wall)
		//flip the map of <brain_output, frequency> to a multimap <frequency, brain_output>
		//(which gets automatically sorted by its frequency)
		multimap<int, deque<bool>> brain_output_sorted;
		for (auto map_it = brain_output_frequencies.begin(); map_it != brain_output_frequencies.end(); map_it++) {
			brain_output_sorted.insert( pair<int, deque<bool> >(map_it->second, map_it->first) );
		}
		bool found_valid_decision = false;
		deque<bool> brain_decision; //final (most common and valid) brain output will correspond to the decision
		//loop through all outputs, checking if brain has found a valid decision,
		//and turn the brain in that direction if it has.
		//Note: the output is order from lowest frequency output to highest, so we loop in reverse order
		for (auto output_it = brain_output_sorted.rbegin(); output_it != brain_output_sorted.rend(); output_it++) {
			if (maze_task.ActOnDecision(output_it->second)) {
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
	//Test if the brain solved the maze in zero decisions
	if (num_decisions == 0) {
		//print error, no need to lock with mutex since cerr/cout in C++11 is thread-safe
		std::cerr << "The maze used allows brains to solve it with zero decisions!" << endl;
		return;
	}
	brain.set_fitness_score(1.0/num_decisions);
	//Decrease number of live threads and notify the waiting threads so another thread can start
	std::lock_guard<std::mutex> num_threads_lock(mtx_);
	num_live_threads_--;
	num_threads_cv_.notify_all();
} //end ObtainBrainFitness(.)


void MazeMaster::ResetAllBrainStartActivations() {
	for (auto brain_it = brains_.begin(); brain_it != brains_.end(); brain_it++) {
		brain_it->ResetStartActivations(av_start_activation_, st_dev_start_activation_);
	}
}


void MazeMaster::PrintGenerationInfo() {

	cout << "Moves required for brains: ";
	float best_score=0;
	//save total score to calculate average
	float total_score=0;
	for (auto brain_it = brains_.begin(); brain_it != brains_.end(); brain_it++) {
		float fitness_score = brain_it->get_fitness_score();
		cout << 1/fitness_score << " ";
		total_score += fitness_score;
		if(fitness_score > best_score) {
			best_score = fitness_score;
		}
	}

	cout << "\nLeast Moves: " << 1/best_score << "     Average Moves: " << 1/(total_score / num_brains_);
	cout << endl;
}

