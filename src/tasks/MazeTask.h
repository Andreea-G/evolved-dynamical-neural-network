/*
 * MazeTask.h
 *
 * An example maze textfile could look like:
 *
 *  0 0 0 0 0 0 0 0
 *  0 2 1 1 1 1 1 0
 *  0 0 0 1 0 0 0 0
 *  0 0 1 1 1 1 3 0
 *  0 0 0 0 0 0 0 0
 *
 *  Note that it should be padded with zeros.
 *
 *  Created on: May 4, 2014
 *      Author: Garrett
 */

#ifndef TASKS_MAZETASK_H_
#define TASKS_MAZETASK_H_

#include <string>
#include <vector>

#include "TaskInterface.h"

using std::vector;

//directions player may face in
enum class Direction {LEFT, UP, DOWN, RIGHT};
//the different kinds of tile that make up map
enum class MazeTile {WALL, NORMAL, START, FINISH};


class MazeTask : public TaskInterface {

public:

  friend class MazeTest; //TODO remove this.
  //Temp constructor for unit testing
  MazeTask() {row_ = 0; col_ = 0; width_ = 0; height_ = 0; player_direction_ = Direction::LEFT; }

  //the map file (see docs at top of file) and whether you want
  //a random starting position.  If random_start is false, then
  //player is started at place in map where value is 2.
  //To set the starting direction, it will loop through the 4 directions
  //stopping when it finds a valid one.
  MazeTask(std::string map_file, bool random_start = false);


  void ActOnDecision(vector<bool> decision);

  //
  vector<bool> GetBrainInput() const;

  //
  int IsFinished() const;

private: //set back to private

  bool LoadMap(std::string map_file);

  //A matrix representing the map, where 0s are walls, 1s are valid paths,
  //2 is the suggested starting point, and 3 is the finish.
  vector<vector<MazeTile> > map_;

  //Current location of the player given by row and height
  int row_;
  int col_;

  //The width and height of the map (including the padding zeros)
  size_t width_;
  size_t height_;

  //Stored the direction which the player is pointing in our (2D) maze.
  Direction player_direction_;

  void AdvancePosition();
};


#endif /* TASKS_MAZETASK_H_ */
