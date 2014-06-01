#ifndef BRAINTEST_H_
#define BRAINTEST_H_

#include "../brain/Brain.h"  //TODO: I need to figure out how to get rid of the ".."


class BrainTest {
public:

	BrainTest() {};
	//Executes a bunch of unit tests
	void Test1();

	void DisplaySynapses(const deque<Neuron> & neurons, int num_neuron_to_display);
};



#endif /* BRAINTEST_H_ */
