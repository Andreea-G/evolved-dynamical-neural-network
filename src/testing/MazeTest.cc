/*
 *	MazeTest.cc
 *	This is a test suite to make sure the MazeTask is working properly.
 *	Created on: May 11, 2014
 *	Author: Garrett
 */

#include <iostream>
#include <string>

#include "MazeTest.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;


void MazeTest::test() {

	string test_maze="maze_files/test_maze";

		deque<bool> left_turn={false,false};

	//Test that random initialization works properly (try it 200 times)
		for (int i = 0; i < 200; i++) {
			MazeTask maze1(test_maze, true);
			int start_tile = int(maze1.map_[maze1.row_][maze1.col_]);
			if (start_tile != 1 && start_tile != 2)
				cerr << "Unexpected start tile: " << start_tile << endl;
	}

	//Test that starting position is set well.
	MazeTask maze2(test_maze);
	if (maze2.row_ != 1 || maze2.col_ != 2)
		cerr << "Unexpecting start row and col";

	//Test that advance position works
	//Test stopping at first decision
	maze2.AdvancePosition();
	if (maze2.row_ != 1 || maze2.col_ != 10)
		cerr << "Didn't advance properly. We're at: " << maze2.row_ << ", " << maze2.col_;

	//Test turning around
	maze2.AdvancePosition();
	if (maze2.row_ != 1 || maze2.col_ != 10 || maze2.player_direction_ != Direction::LEFT)
		cerr << "Didn't advance properly. We're at: " << maze2.row_ << ", " << maze2.col_;

	//test brain input
		deque<bool> brain_input = maze2.GetBrainInput();
		if (brain_input[0] == false || brain_input[1] == false || brain_input[2] == true)
		cerr << "wrong brain input at (1,10)";

	//Turn left
	maze2.ActOnDecision(left_turn);
		if (maze2.player_direction_ != Direction::DOWN)
		cerr << "Not facing the right way!";

	//Advance again
	maze2.AdvancePosition();
		if (maze2.row_ != 3 || maze2.col_ != 10)
		cerr << "After left turn, advanced incorrectly. We're at: " << maze2.row_ << ", " << maze2.col_;

	//test brain input
	brain_input = maze2.GetBrainInput();
		if (brain_input[0] == false || brain_input[1] == false || brain_input[2] == false)
		cerr << "wrong brain input at (3,10)";
}
	//make sure we're not finished
		if (maze2.IsFinished() == true)
		cerr << "We're not finished yet!!!";

	//go to end and test if we're finished
	maze2.ActOnDecision(left_turn);
	maze2.AdvancePosition();
	maze2.AdvancePosition();
	maze2.ActOnDecision(left_turn);
	maze2.AdvancePosition(); //should be done after this.
	if (maze2.IsF}inished() == false)
		cerr << "But, we ARE finished!!!";


	cout << "\nTesting is finished" << endl;
	return;

}


