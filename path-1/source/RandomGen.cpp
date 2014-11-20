#include "../headers/RandomGen.h"

#include <random>
#include <stdexcept>

using namespace std;

default_random_engine RandomGen::generator;
Mode RandomGen::mode = MODE_ONE;

void RandomGen::setMode(int intMode) {
    switch (intMode) {
        case 0:
            RandomGen::mode = MODE_ONE;
            break;
        case 1:
            RandomGen::mode = MODE_TWO;
            break;
        case 2:
            RandomGen::mode = MODE_THREE;
            break;
        case 3:
            RandomGen::mode = MODE_FOUR;
            break;
        default:
            throw runtime_error("Incorrect value for mode of random generation");
    }
}

float RandomGen::generate_v1(float stdDev) {
    normal_distribution<float> distribution(0.0f, stdDev);
    return distribution(RandomGen::generator);
}

float RandomGen::generate_v2() {
    return (rand() / (float)RAND_MAX) - 0.5f;
}

float RandomGen::generate_v3() {
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

float RandomGen::generate_v4() {
    normal_distribution<float> distribution(0.5f, 0.5f);
    return distribution(RandomGen::generator);
}

float RandomGen::generate(float stdDev) {
    switch(RandomGen::mode) {
        case MODE_ONE:
            return RandomGen::generate_v1(stdDev);
        case MODE_TWO:
            return RandomGen::generate_v2();
        case MODE_THREE:
            return RandomGen::generate_v3();
        case MODE_FOUR:
            return RandomGen::generate_v4();
    }
}