#include <random>

namespace globals {
//Note: only constant variables are allowed in here!

extern constexpr float MIN_STRENGTH = 0.0;
extern constexpr float MAX_STRENGTH = 1.0;
extern constexpr float MIN_ACTIVATION = 0.0;
extern constexpr float MAX_ACTIVATION = 1.0;
//For now, I'm setting TIME_STEP to 1, which has the advantage of cycling the brain much faster
//(basically, we're moving from continues to discrete)
extern constexpr float TIME_STEP = 1;
//since TIME_STEP is set to 1, I'm setting a max decay rate of 1.0, anything higher is overkill
extern constexpr float MIN_DECAY_RATE = 0.01;
extern constexpr float MAX_DECAY_RATE = 1.0;
extern constexpr float MIN_FITNESS_SCORE = 0.0;
extern constexpr float MAX_FITNESS_SCORE = 1.0;

std::default_random_engine gen;
//std::random_device gen;

}
