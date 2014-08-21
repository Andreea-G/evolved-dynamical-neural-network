#!/usr/bin/env bash

######################################################################
############User-defined parameters (please edit these to your liking)
######################################################################

#Number of brains in each generation
num_brains=15
#Number of neurons in each brain
num_neurons=500
#verage activation threshold for each neruon
av_active_threshold=0.25
#Standard deviation for activation threshold for each neruon
st_dev_active_threshold=0.04
#Start activation for each neruon (at beginning of maze)
start_activation=0.25
#Average decay rate for each neruon
av_decay_rate=0.001
#Standard deviation for decay rate for each neruon
st_dev_decay_rate=0.0003
#Average number of synapses for each neruon
av_num_syn=10
#Standard deviation of number of synapses for each neruon
st_dev_num_syn=2
#Average synapse strength for each neruon
av_syn_strength=0.05
#Standard deviation of synapse strength for each neruon
st_dev_syn_strength=0.04
#Maximum allowed decision before a brain receives worst fitness score
max_decisions=100
#Duration of input signal in cycles
input_duration=10
#Number of cycles between start of input and start of output
input_output_delay=5
#Duration of output signal in cycles
output_duration=10
#Duration between end of output and start of next input in cycles
deadtime_duration=0
#The maze filepath, see docs for expected file format
maze_map_file=maze_files/example_maze
#Have players start at random points in maze (you should probably not use this)
maze_random_start=false
#Number of generations
num_generations=10
#Number of mutated neurons each time a brain is mutated
num_mutated_neurons=1
#Number of mutated synapses in each mutated neuron
num_mutated_synapses=1
#Probability of each brain coming from asexual reproduction
prob_asexual=1
#Mutate the decay rate everytime a neuron gets mutated
mutate_decay_rate=false
#Mutate the active threshold everytime a neuron gets mutated
mutate_active_threshold=false
#Max number of threads to use
max_num_threads=8


############################################################################################################
############################################## Don't edit beyond here ######################################
############################################################################################################

#Prepare flags
flags=""
if [ "$maze_random_start" == "true" ]; then
    flags="${flags}-x "
fi
if [ "$mutate_decay_rate" == "true" ]; then
    flags="${flags}-v "
fi
if [ "$maze_active_threshol" == "true" ]; then
    flags="${flags}-V "
fi

echo -e "Command to execute is:\n\n   ./pinn  $flags  --num_brains ${num_brains} --num_neurons $num_neurons --av_active_threshold $av_active_threshold --st_dev_active_threshold $st_dev_active_threshold --start_activation $start_activation --av_decay_rate $av_decay_rate --st_dev_decay_rate $st_dev_decay_rate --av_num_syn $av_num_syn --st_dev_num_syn $st_dev_num_syn --av_syn_strength $av_syn_strength --st_dev_syn_strength $st_dev_syn_strength --max_decisions $max_decisions --input_duration $input_duration --input_output_delay $input_output_delay --output_duration $output_duration --deadtime_duration $deadtime_duration --maze_map_file $maze_map_file --num_generations $num_generations --num_mutated_neurons $num_mutated_neurons --num_mutated_synapses $num_mutated_synapses --prob_asexual $prob_asexual --max_num_threads $max_num_threads"

echo -e "\n\n____________________________________________"

./pinn  $flags  --num_brains ${num_brains} --num_neurons $num_neurons --av_active_threshold $av_active_threshold --st_dev_active_threshold $st_dev_active_threshold --start_activation $start_activation --av_decay_rate $av_decay_rate --st_dev_decay_rate $st_dev_decay_rate --av_num_syn $av_num_syn --st_dev_num_syn $st_dev_num_syn --av_syn_strength $av_syn_strength --st_dev_syn_strength $st_dev_syn_strength --max_decisions $max_decisions --input_duration $input_duration --input_output_delay $input_output_delay --output_duration $output_duration --deadtime_duration $deadtime_duration --maze_map_file $maze_map_file --num_generations $num_generations --num_mutated_neurons $num_mutated_neurons --num_mutated_synapses $num_mutated_synapses --prob_asexual $prob_asexual --max_num_threads $max_num_threads

