#pragma once
#include <cstdint>

namespace AsteroidShooter {
    class Random {
        public:
        Random();

        static Random rand;
        
        // PCG32
        uint32_t nextUInt();
        int nextInt();
        
        // float in [-0.25, 0.25]
        float nextFloat(float limit);
        
        private:
        uint64_t state;
        uint64_t inc;
    };
}
