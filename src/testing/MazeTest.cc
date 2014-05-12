/*
 * MazeTest.cc
 *
 *  Created on: May 11, 2014
 *      Author: garrett
 */

#include <iostream>

#include "MazeTest.h"

using std::cout;
using std::endl;


void MazeTest::test() {

  cout << "\nAbout to instantiate MazeTask object";
  cout << "\nOh dang!";
  cout << "\nReally? no luck?";
  cout << endl;

  MazeTask maze1;

  maze1.LoadMap("maze_files/simple_maze");

  cout << "\nAlright, here's the results." << endl;



  return;

}


