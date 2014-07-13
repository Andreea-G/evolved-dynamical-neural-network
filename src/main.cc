//============================================================================
// Name			: MazeTester.cpp
// Author		:
// Version		:
// Copyright	:
// Description	:
//============================================================================

//TODO: clean up these headers and namespace declarations at some point.
#include <iostream>
#include <string>

//#include "tasks/MazeTask.h"
#include "testing/MazeTest.h"
#include "testing/BrainTest.h"
#include "testing/GameMasterTest.h"
#include "testing/EvolutionTest.h"
#include "brain/Brain.h"
#include "brain/Neuron.h"
#include "evolution/Evolution.h"
#include "tasks/MazeTask.h"
#include "gamemaster/GameMaster.h"

using std::cout;
using std::endl;
using std::string;
using std::cin;

int main() {

	GameMasterTest gamemaster_test;
	gamemaster_test.Test1();
	
//	MazeTest maze_test;
//	maze_test.test();

	return 0;
}



