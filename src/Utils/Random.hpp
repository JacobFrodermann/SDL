#pragma once
#include <cstdint>

namespace AsteroidShooter {
    class Random {
        public:
        Random();
        
        // PCG32
        uint32_t nextUInt();
        
        // float in [-0.25, 0.25]
        float nextFloat(float limit);
        
        private:
        uint64_t state;
        uint64_t inc;
    };
}
