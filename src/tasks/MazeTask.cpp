/*
 *	MazeTask.cc
 *
 *	Created on: May 4, 2014
 *	Authors: Garrett R, Andreea G
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <assert.h>

#include <src/tasks/MazeTask.hpp>
#include <src/Globals.hpp>

using std::deque;
using std::cerr;
using std::endl;

MazeTask::MazeTask(const std::string& map_file, const bool random_start) {

	//Load map file into map_ member variable
	if (LoadMap(map_file) == false) {
		cerr << endl << "Error loading map!";
	}

	height_ = map_.size();
	width_ = map_[0].size();

	//temporarily initialize these
	row_ = 0;
	col_ = 0;

	if (random_start) {
		//generate two random coordinates and check if it's a valid start point,
		//if not, try again.

		std::uniform_int_distribution<int> row_distro(0, height_-1);
		std::uniform_int_distribution<int> col_distro(0, width_-1);

		int rand_row = 0;
		int rand_col = 0;
		while(true) {
			rand_row = row_distro(globals::gen);
			rand_col = col_distro(globals::gen);
			//Check if this position is valid, and if so, set it as player's position
			if (map_[rand_row][rand_col] == MazeTile::NORMAL || map_[rand_row][rand_col] == MazeTile::START ) {
				row_ = rand_row;
				col_ = rand_col;
				break;
			}
		}//end while

	}	else {	 //if start is not random, then search for the start position
		for (size_t row_i = 0; row_i < height_; row_i++) {
			for (size_t col_j = 0; col_j < width_; col_j++)	{
				if (map_[row_i][col_j] == MazeTile::START) {
					row_ = row_i;
					col_ = col_j;
					goto stop_search;
				}
			}

		}
		stop_search: {} //label to break to after finding the START tile.

		if (map_[row_][col_] != MazeTile::START) {
			cerr << "\nERROR: We were not able to find a start position in map! (a position with value 2)";
		}

	}//end of else


	//go through the 4 directions and stop when we find a valid one.
	MazeTile tile_above = map_[row_-1][col_];
	MazeTile tile_right = map_[row_][col_+1];
	MazeTile tile_below = map_[row_+1][col_];
	MazeTile tile_left  = map_[row_][col_-1];

	if (tile_above == MazeTile::NORMAL || tile_above == MazeTile::START)
		player_direction_ = Direction::UP;
	else if (tile_right == MazeTile::NORMAL || tile_right == MazeTile::START)
		player_direction_ = Direction::RIGHT;
	else if (tile_below == MazeTile::NORMAL || tile_below == MazeTile::START)
		player_direction_ = Direction::DOWN;
	else if (tile_left == MazeTile::NORMAL || tile_left == MazeTile::START)
		player_direction_ = Direction::LEFT;
	else
		cerr << "\nNo valid starting direction was found!";

}



bool MazeTask::LoadMap(const std::string& map_file) {

	std::ifstream in_file(map_file.c_str());

	//Make sure it opened successfully
	if (!in_file.is_open()) {
		cerr << "ERROR: The file " << map_file << " was not found.";
		return false;
	}


	//variable to hold each line of the map textfile
	std::string line;

	while (getline(in_file, line)) {

		//the file may have some empty lines at the end, and we stop reading if we get to empty line
		if (line == "") {
			break;
		}

		//temporary var to hold the individual numbers from the map file
		int num;

		std::istringstream line_stream(line);

		//save current row into temporary deque
		deque<MazeTile> temp_row_vec;
		while (line_stream >> num)
			{
			MazeTile temp_tile = static_cast<MazeTile>(num);
			//Make sure temp_tile is a valid tile
			if (temp_tile != MazeTile::WALL && temp_tile != MazeTile::NORMAL &&
							temp_tile != MazeTile::START && temp_tile != MazeTile::FINISH) {
				cerr << "The current tile is not valid since it has a value of " << int(temp_tile) << std::endl;
			}
			temp_row_vec.push_back(temp_tile);
		}
		//Add this row to our map
		map_.push_back(temp_row_vec);
	}

	return true;

}


bool MazeTask::ActOnDecision(const deque<bool>& decision) {


  if (decision[0] == true) { //corresponds to decision to stay straigh, i.e. not turn

		if (GetTileFront() == MazeTile::WALL) {
			return false; //invalid move so return false
		} else {
			//just return since we're keeping facing straigh
			return true;
		}

	} else {

		if (decision[1] == false) { //corresponds to decision to turn left
			if (GetTileLeft() == MazeTile::WALL) {
				return false;
			} else {
				TurnLeft();
				return true;
			}
		} else {
			if (GetTileRight() == MazeTile::WALL) {
				return false;
			} else {
				TurnRight();
				return true;
			}
		}

	}

	assert(false);
}


deque<bool> MazeTask::GetBrainInput() const {

	bool can_turn_left = (GetTileLeft() !=  MazeTile::WALL);
	bool can_turn_right = (GetTileRight() !=  MazeTile::WALL);
	bool can_go_forward = (GetTileFront() !=  MazeTile::WALL);

	deque<bool> input_for_brain = {can_turn_left, can_go_forward, can_turn_right};
	return input_for_brain;
}


int MazeTask::IsFinished() const {

	//Check current location, plus the neighboring 4 locations for the finish
	if (map_[row_][col_]==MazeTile::FINISH || map_[row_][col_] == MazeTile::FINISH ||
		map_[row_][col_]==MazeTile::FINISH || map_[row_][col_] == MazeTile::FINISH ||
		map_[row_][col_]==MazeTile::FINISH) {
		return 1;
	} else {
		return 0;
	}

}


bool MazeTask::AdvancePosition() {

	//the player should always be able to advance at least once, so we remember
	//if we're on first move.
	bool first_move = true;
	//remember if we just turned a corner or reversed direction so that player doesn't get fooled into thinking
	//it's at a decision (since, for example, it would see a left and straight option after turning left)
	bool just_turned = false;

	//Loop until we hit a wall in which case we break
	while (true) {

		//if player is standing on the finish, just stop there.
		if (map_[row_][col_] == MazeTile::FINISH) {
			return true;
		}

		//get the tiles to the left and right of current position (given direction).
		MazeTile tile_left = GetTileLeft();
		MazeTile tile_right = GetTileRight();
		//find next position (in direction that player's pointing) and find what's to the sides
		int next_row = row_, next_col = col_; //initializing these, they'll be modified
		switch (player_direction_)
			{
			case Direction::UP: {
				next_row -= 1;
//				tile_left = map_[row_][col_-1];
//				tile_right = map_[row_][col_+1];
				break;
			}
			case Direction::RIGHT: {
				next_col += 1;
//				tile_left = map_[row_-1][col_];
//				tile_right = map_[row_+1][col_];
				break;
			}
			case Direction::DOWN: {
				next_row += 1;
//				tile_left = map_[row_][col_+1];
//				tile_right = map_[row_][col_-1];
				break;
			}
			case Direction::LEFT: {
				next_col -= 1;
//				tile_left = map_[row_+1][col_];
//				tile_right = map_[row_-1][col_];
				break;
				}
			}//end switch
		MazeTile tile_next = map_[next_row][next_col];

		//If it's the first move, just do it.
		if (first_move) {
			//if player is facing a wall on first move, we return false.
			if (tile_next == MazeTile::WALL) {
				return false;
			} else {
				row_ = next_row;
				col_ = next_col;
				first_move = false;
				continue;
			}
		}

		//if the player just turned a corner or turned around, then take the next step
		if (just_turned) {
			assert(tile_next != MazeTile::WALL);
			row_ = next_row;
			col_ = next_col;
			just_turned = false;
			continue;
		}

		//check if we can even move forward
		if (tile_next == MazeTile::WALL) {
			//we can't move forward, so check what options we have (we deal with a T intersection decision below)
			if (tile_left == MazeTile::WALL && tile_right != MazeTile::WALL) {
				TurnRight();
				just_turned = true;
				continue;
			} else if (tile_left != MazeTile::WALL && tile_right == MazeTile::WALL) {
				TurnLeft();
				just_turned = true;
				continue;
			} else if (tile_left == MazeTile::WALL && tile_right == MazeTile::WALL) {
				TurnAround();
				just_turned = true;
				continue;
			}
		}

		//move forward if the next tile along our path is valid and there's no decision to be made,
		//i.e. to the left and right are walls.  Otherwise, stop there.
		if ( (tile_next == MazeTile::NORMAL || tile_next == MazeTile::START || tile_next == MazeTile::FINISH) &&
				 (tile_left == MazeTile::WALL && tile_right == MazeTile::WALL) ) {
			row_ = next_row;
			col_ = next_col;
			continue;
		} else {
			return true;
		}
	} //end while loop

	return true;

}//end of MazeTask::AdvancePosition()


MazeTile MazeTask::GetTileLeft() const {
	//Initialize MazeTile to arbitrary value
	MazeTile tile_left = MazeTile::WALL;
	switch (player_direction_)
		{
		case Direction::UP: {
			tile_left = map_[row_][col_-1];
			break;
		}
		case Direction::RIGHT: {
			tile_left = map_[row_-1][col_];
			break;
		}
		case Direction::DOWN: {
			tile_left = map_[row_][col_+1];
			break;
		}
		case Direction::LEFT: {
			tile_left = map_[row_+1][col_];
			break;
			}
		}//end switch

	return tile_left;
}


MazeTile MazeTask::GetTileRight() const {
	//Initialize MazeTile to arbitrary value
	MazeTile tile_right = MazeTile::WALL;
	switch (player_direction_)
		{
		case Direction::UP: {
			tile_right = map_[row_][col_+1];
			break;
		}
		case Direction::RIGHT: {
			tile_right = map_[row_+1][col_];
			break;
		}
		case Direction::DOWN: {
			tile_right = map_[row_][col_-1];
			break;
		}
		case Direction::LEFT: {
			tile_right = map_[row_-1][col_];
			break;
			}
		}//end switch

	return tile_right;

}


MazeTile MazeTask::GetTileFront() const {
	//Initialize MazeTile to arbitrary value
	MazeTile tile_front = MazeTile::WALL;
	switch (player_direction_)
		{
		case Direction::UP: {
			tile_front = map_[row_-1][col_];
			break;
		}
		case Direction::RIGHT: {
			tile_front = map_[row_][col_+1];
			break;
		}
		case Direction::DOWN: {
			tile_front = map_[row_+1][col_];
			break;
		}
		case Direction::LEFT: {
			tile_front = map_[row_][col_-1];
			break;
			}
		}//end switch

	return tile_front;

}


void MazeTask::TurnLeft() {

	switch (player_direction_)
		{
		case Direction::UP: {
			player_direction_ = Direction::LEFT;
			break;
		}
		case Direction::RIGHT: {
			player_direction_ = Direction::UP;
			break;
		}
		case Direction::DOWN: {
			player_direction_ = Direction::RIGHT;
			break;
		}
		case Direction::LEFT: {
			player_direction_ = Direction::DOWN;
			break;
			}
	}//end switch
}//end TurnLeft(.)


void MazeTask::TurnRight() {

	switch (player_direction_)
		{
		case Direction::UP: {
			player_direction_ = Direction::RIGHT;
			break;
		}
		case Direction::RIGHT: {
			player_direction_ = Direction::DOWN;
			break;
		}
		case Direction::DOWN: {
			player_direction_ = Direction::LEFT;
			break;
		}
		case Direction::LEFT: {
			player_direction_ = Direction::UP;
			break;
			}
	}//end switch
}//end TurnRight(.)


void MazeTask::TurnAround() {

	switch (player_direction_)
		{
		case Direction::UP: {
			player_direction_ = Direction::DOWN;
			break;
		}
		case Direction::RIGHT: {
			player_direction_ = Direction::LEFT;
			break;
		}
		case Direction::DOWN: {
			player_direction_ = Direction::UP;
			break;
		}
		case Direction::LEFT: {
			player_direction_ = Direction::RIGHT;
			break;
			}
	}//end switch
}//end TurnAround(.)

