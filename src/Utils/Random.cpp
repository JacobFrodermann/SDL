#include <cstdint>
#include <random>
#include "./Random.hpp"


namespace AsteroidShooter {

Random Random::rand = Random();

Random::Random() {
    // Seed with true randomness so the sequence changes every run.
    std::random_device rd;
    state = rd();
    inc   = (rd() << 1u) | 1u; // must be odd
}

// PCG32
uint32_t Random::nextUInt() {
    uint64_t oldstate = state;
    state = oldstate * 6364136223846793005ULL + inc;
    
    uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
    uint32_t rot = oldstate >> 59u;
    
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

int Random::nextInt() {
    return nextUInt();
}
    
// float in [-0.25, 0.25]
float Random::nextFloat(float limit) {
    return (nextUInt() * (1.0f / 4294967296.0f) - limit) * limit;
}

}
