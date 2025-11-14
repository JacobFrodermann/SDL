#pragma once
#include "SDL_rect.h"
#include <vector>

namespace AsteroidShooter {

class Asteroid {

public:
  Asteroid(int);
  SDL_Rect getSrcRect();
  SDL_Rect getDstRect();
  static void tick();
  float X, Y, VelX, VelY, rot, h, w, rs;
  static std::vector<Asteroid> asteroids;
  static void spawn(int score), filter();
  bool intersects(SDL_Rect), intersects(SDL_Point);
  bool checkBounds();
  void damage();
  int skin, radius, health;
};

} // namespace AsteroidShooter