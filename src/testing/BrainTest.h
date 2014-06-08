#ifndef BRAINTEST_H_
#define BRAINTEST_H_

#include "../brain/Brain.h"  //TODO: I need to figure out how to get rid of the ".."


class BrainTest {
public:

	BrainTest() {};
	//Executes a bunch of unit tests (these are a bit messy at the moment)
	//although to have a permanent proper unit test, we'd need to rewrite the code to work on a pseudo-random generator.
	void Test1();

	//Apparently, it's bad to have an instance of a class call a static member function
	//(which Test1() does do, but since this is unit-testing, I'm not worrying about it)
	static void DisplaySynapses(const deque<Neuron> & neurons, int num_neuron_to_display);
};



#endif /* BRAINTEST_H_ */
