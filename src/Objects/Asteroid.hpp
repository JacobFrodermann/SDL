#pragma once
#include <SDL3/SDL_rect.h>
#include <vector>

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
  void damage();
  
  float X, Y, VelX, VelY, rot, h, w, rs;
  int skin, radius, health;
};

} // namespace AsteroidShooter