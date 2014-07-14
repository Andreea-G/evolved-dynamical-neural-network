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
#include <tclap/CmdLine.h>

#include <src/brain/Brain.h>
#include <src/brain/Neuron.h>
#include <src/evolution/Evolution.h>
#include <src/gamemaster/GameMaster.h>
#include <src/tasks/MazeTask.h>

#include <src/testing/BrainTest.h>
#include <src/testing/EvolutionTest.h>
#include <src/testing/MazeTest.h>
#include <src/gamemaster/GameMaster.h>

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

	try {

		//create commandline parser object and give description of program for when user gives the flag "--help"
		TCLAP::CmdLine cmd("Evolved Dynamical Neural Network", ' ', "0.1");

		// Define a value argument and add it to the command line.
		// A value arg defines a flag and a type of value that it expects,
		// such as "-n Bishop".
		TCLAP::ValueArg<std::string> nameArg("n","name","Name to print",true,"homer","string");

		// Add the argument nameArg to the CmdLine object. The CmdLine object
		// uses this Arg to parse the command line.
		cmd.add( nameArg );

		//flag
		TCLAP::SwitchArg reverseSwitch("r","reverse","Print name backwards", cmd, false);

		// Parse the argv array.
		cmd.parse( argc, argv );

		// Get the value parsed by each arg.
		std::string name = nameArg.getValue();
		bool reverseName = reverseSwitch.getValue();


	} catch (TCLAP::ArgException &e) {
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
	}



	return 0;
}



