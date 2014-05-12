/*
 * MazeTask.cc
 *
 *  Created on: May 4, 2014
 *      Author: garrett
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <random>

#include "MazeTask.h"

using std::vector;


MazeTask::MazeTask(std::string map_file, bool random_start) {
  //Load map file into map_ member variable
  if (LoadMap(map_file)==false) {
    std::cerr << std::endl << "Error loading map!";
  }

  height_ = map_.size();
  width_ = map_[0].size();

  //temporarily initialize these
  row_ = 0;
  width_ = 0;


  std::cout << "Inside MazeTask" <<std::endl;

  if (random_start) {
    //generate two random coordinates and check if it's a valid start point,
    //if not, try again.

    std::random_device generator;
    std::uniform_int_distribution<int> row_distro(0,height_-1);
    std::uniform_int_distribution<int> col_distro(0,width_-1);

    int rand_row=0;
    int rand_col=0;
    while(true) {
      rand_row = row_distro(generator);
      rand_col = col_distro(generator);
      //Check if this position is valid, and if so, set it as player's position
      if (map_[rand_row][rand_col] == MazeTile::NORMAL || map_[rand_row][rand_col] == MazeTile::START ) {
        row_ = rand_row;
        col_ = rand_col;
        break;
      }
    }//end while

  }
  else { //if start is not random, then search for the start position

    for (size_t row_i=0; row_i < height_; row_i++) {
      for (size_t col_j=0; col_j < width_; col_j++) {
        std::cout << "Height is" << height_ << std::endl;
        std::cout << "Width is" << width_ << std::endl;
        if (map_[row_i][col_j] == MazeTile::START) {
          row_ = row_i;
          col_ = col_j;
          break;
        }
      }
    }

    if (map_[row_][col_]!=MazeTile::START) {
      std::cerr << "\nWe were not able to find a start position in map! (a position with value 2)";
    }

  }//else


  //go through the 4 directions and stop when we find a valid one.
  MazeTile tile_above = map_[row_-1][col_];
  MazeTile tile_right = map_[row_][col_+1];
  MazeTile tile_below = map_[row_+1][col_];
  MazeTile tile_left  = map_[row_][col_-1];

  if (tile_above==MazeTile::NORMAL || tile_above==MazeTile::START)
    player_direction_ = Direction::UP;

  else if (tile_right==MazeTile::NORMAL || tile_right==MazeTile::START)
    player_direction_ = Direction::RIGHT;

  else if (tile_below==MazeTile::NORMAL || tile_below==MazeTile::START)
    player_direction_ = Direction::DOWN;

  else if (tile_left==MazeTile::NORMAL || tile_left==MazeTile::START)
    player_direction_ = Direction::LEFT;

  else
    std::cerr << "\nNo valid starting direction was found!";

}



bool MazeTask::LoadMap(std::string map_file) {

  std::ifstream in_file(map_file.c_str());

  //Make sure it opened successfully
  if (!in_file.is_open()) {
    std::cerr << "ERROR: The file " << map_file << " was not found.";
    return false;
  }


  //variable to hold each line of the map textfile
  std::string line;

  while (getline(in_file, line)) {


    //temporary var to hold the individual numbers from the map file
    int num;

    std::istringstream line_stream(line);

    //save current row into temporary vector
    vector<MazeTile> temp_row_vec;
    while (line_stream >> num) {  //TODO How come if it's just one number on the line this returns false and we never get into loop?
      MazeTile temp_tile = static_cast<MazeTile>(num);
      //Make sure temp_tile is a valid tile
      if (temp_tile!=MazeTile::WALL && temp_tile!=MazeTile::NORMAL &&
          temp_tile!=MazeTile::START && temp_tile!=MazeTile::FINISH) {
        std::cerr << "The current tile is not valid since it has a value of " << int(temp_tile) << std::endl;
      }
      temp_row_vec.push_back(temp_tile);
    }
    //Add this row to our map
    map_.push_back(temp_row_vec);
  }


  return true;

}


void MazeTask::ActOnDecision(vector<bool> decision) {
  //TODO
}

vector<bool> MazeTask::GetBrainInput() const {
  //TODO
  vector <bool> bool_vec;
  return bool_vec;
}

int MazeTask::IsFinished() const {
  return 1; //TODO finish this
}

void MazeTask::AdvancePosition() {

}











