//include file for all global variables (all of which are constants)
//The only non-constant thing defined here is the random generator.
#include <random>

#ifndef GLOBALS_H
#define GLOBALS_H

namespace globals {

extern float MIN_STRENGTH;
extern float MAX_STRENGTH;
extern float MIN_ACTIVATION;
extern float MAX_ACTIVATION;
extern float TIME_STEP;
extern float MIN_DECAY_RATE;
extern float MAX_DECAY_RATE;

//Define the random generator that will be used throughout the program
//we'll occasionally want pseudo-random numbers instead of using random_device
//for example, with testing, pseudo-random is better.
//To change types, you must also change it in Globals.cpp.
extern std::default_random_engine gen;   //one of these has to be commented out
//extern std::random_device gen;

}

#endif // GLOBALS_H
