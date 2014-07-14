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

#include <src/brain/Brain.hpp>
#include <src/brain/Neuron.hpp>
#include <src/evolution/Evolution.hpp>
#include <src/gamemaster/GameMaster.hpp>
#include <src/tasks/MazeTask.hpp>
#include <src/testing/BrainTest.hpp>
#include <src/testing/EvolutionTest.hpp>
#include <src/testing/MazeTest.hpp>
#include <src/testing/GameMasterTest.hpp>

#include <tclap/CmdLine.h> //Note: .h, not .hpp since this is a third-party file we're using that was named as such.

using std::cout;
using std::endl;
using std::string;
using std::cin;

int main(int argc, char* argv[]) {
	//Parse the arguments from the commandline, then execute the GameMaster which is where the meat and potatoes are

//	BrainTest test;
//	brain.test1();
	
//	BrainTest brain_test1;
//	brain_test1.Test1();

//	MazeTest maze_test;
//	maze_test.test();

	GameMasterTest gmtest;
	gmtest.Test2();

	return 0;
	try {

		//create commandline parser object and give description of program for when user gives the flag "--help"
		TCLAP::CmdLine cmd("Evolved Dynamical Neural Network", ' ', "0.1");


	} catch (TCLAP::ArgException &e) {
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
	}


	return 0;
}



