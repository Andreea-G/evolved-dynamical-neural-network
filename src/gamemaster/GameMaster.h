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

using std::deque;

class GameMaster {

public:
	void ObtainBrainFitnesses();

private: //TODO: many of these should be const
    deque<Brain> brains_;
    Evolution evolution_;
    int max_decisions_;
	std::string maze_map_file_;
    bool maze_random_start_;
    int input_duration_, input_output_delay_, output_duration_;

};

//std::multimap<int, deque<bool>> FlipMap(const std::map<deque<bool>, int> &input_map);




#endif /* GAMEMASTER__MAGEMASTER_H_ */
