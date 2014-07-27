#!/usr/bin/env bash

num_brains=16
num_neurons=500
av_active_threshold=0.25
st_dev_active_threshold=0.04
start_activation=0.25
av_decay_rate=0.001
st_dev_decay_rate=0.0003
av_num_syn=10
st_dev_num_syn=2
av_syn_strength=0.05
st_dev_syn_strength=0.04
max_decisions=100
input_duration=10
input_output_delay=5
output_duration=10
maze_map_file=maze_files/test_maze4
maze_random_start=false
num_generations=10
num_mutated_neurons=1
num_mutated_synapses=1
prob_asexual=1
mutate_decay_rate=false
mutate_active_threshold=false
max_num_threads=8

############################################## Don't edit beyond here ######################################

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

echo -e "Command to execute is:\n\n   ./pinn  $flags  --num_brains ${num_brains} --num_neurons $num_neurons --av_active_threshold $av_active_threshold --st_dev_active_threshold $st_dev_active_threshold --start_activation $start_activation --av_decay_rate $av_decay_rate --st_dev_decay_rate $st_dev_decay_rate --av_num_syn $av_num_syn --st_dev_num_syn $st_dev_num_syn --av_syn_strength $av_syn_strength --st_dev_syn_strength $st_dev_syn_strength --max_decisions $max_decisions --input_duration $input_duration --input_output_delay $input_output_delay --output_duration $output_duration --maze_map_file $maze_map_file --num_generations $num_generations --num_mutated_neurons $num_mutated_neurons --num_mutated_synapses $num_mutated_synapses --prob_asexual $prob_asexual --max_num_threads $max_num_threads"

echo -e "\n\n____________________________________________"

./pinn  $flags  --num_brains ${num_brains} --num_neurons $num_neurons --av_active_threshold $av_active_threshold --st_dev_active_threshold $st_dev_active_threshold --start_activation $start_activation --av_decay_rate $av_decay_rate --st_dev_decay_rate $st_dev_decay_rate --av_num_syn $av_num_syn --st_dev_num_syn $st_dev_num_syn --av_syn_strength $av_syn_strength --st_dev_syn_strength $st_dev_syn_strength --max_decisions $max_decisions --input_duration $input_duration --input_output_delay $input_output_delay --output_duration $output_duration --maze_map_file $maze_map_file --num_generations $num_generations --num_mutated_neurons $num_mutated_neurons --num_mutated_synapses $num_mutated_synapses --prob_asexual $prob_asexual --max_num_threads $max_num_threads

