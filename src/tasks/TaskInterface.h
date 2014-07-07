/*
 * TaskInterface.h
 *
 * This is the interface (abstract base class) for all tasks that the brain will be expected to learn.
 * Examples of tasks could be a maze, an addition problem, the 2048 game, etc.,
 * but they should all have these function implemented.
 *
 *  Created on: May 4, 2014
 *      Author: Garrett
 */

#ifndef TASKS__TASKINTERFACE_H_
#define TASKS__TASKINTERFACE_H_

#include <deque>

using std::deque;

class TaskInterface {

public:

	virtual ~TaskInterface() { }

	//ActOnDecision tells the task object that the brain has made a decision and the task
	//object updates the current state of the game.  All decisions must be in binary form,
	//i.e. a list of Booleans.
	//return false if nothing was done because the decision was invalid.
    virtual bool ActOnDecision(const deque<bool> decision) = 0 ;

	//This function gets input that is later given to the brain.  Since the brain expects
    //a deque of Booleans, that's what the task object must return
    virtual deque<bool> GetBrainInput() const = 0 ;

	//Optional function to say if the task is completed.  For example, in a maze task, this
	//would say if the player was at the finish of the maze. Returns 1 for finished, 0 for
	//not finished and -1 to signify that this hasn't been implemented by the particular task
	//or there was an error.
	virtual int IsFinished() const { return -1; }

};


#endif /* TASKS_TASKINTERFACE_H_ */
