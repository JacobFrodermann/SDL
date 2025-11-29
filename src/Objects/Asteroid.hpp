#pragma once
#include <SDL3/SDL_rect.h>
#include <vector>
#include "../Utils/Random.hpp"
#include <SDL3/SDL_pixels.h>

namespace AsteroidShooter {

class Asteroid {

public:
  Asteroid(int);
  const SDL_FRect getDstRect(),
                  getSrcRect();

  static std::vector<Asteroid> asteroids;
  static void spawn(int score), filter();
  static void tick();
  
  bool  intersects(const SDL_FRect*), 
        intersects(SDL_FPoint);
  bool checkBounds();
  bool isGolden();
  void damage();
  
  float X, Y, VelX, VelY, rot, h, w, rs;
  int skin, radius, health;
  bool removeMe = false;
  SDL_Color color;
};

} // namespace AsteroidShooter