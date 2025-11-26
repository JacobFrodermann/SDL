#include "Game.hpp"
#include "Objects/Asteroid.hpp"
#include "Objects/Beam.hpp"
#include "Objects/Ship.hpp"
#include "Objects/Particle.hpp"
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "Settings.hpp"
#include "Utils/Util.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <algorithm>
#include <math.h>
#include <cstddef>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>

namespace AsteroidShooter {

const SDL_FRect Game::BgRect = SDL_FRect{690, 0, 540, 2160},
                Game::ForceFieldSrcRect = {0, 0, 50, 70};

int Game::init(SDL_Renderer *renderer, bool debug) {
  this->debug = debug;
  this->BgTexture = Util::loadTexuture("assets/GameBG.png", renderer);
  this->ShipsTexture = Util::loadTexuture("assets/Ships.png", renderer);
  this->BeamTexture = Util::loadTexuture("assets/beam.png", renderer);
  this->AsteroidsTexture = Util::loadTexuture("assets/asteriodAtlas.png", renderer);
  this->ForceFieldTexture = Util::loadTexuture("assets/forcefield.png", renderer);


  BackgroundOffset = 0;
  animationState = 0;
  dead = false;
  pressed = {};
  return 0;
}

int Game::draw(SDL_Renderer *render) {
  this->renderer = render;
  tick++;
  tick %= 20;
  int ret = 0;
  SDL_Event e;
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_EVENT_QUIT) {
      ret = SDL_EVENT_QUIT;
    } else if (e.type == SDL_EVENT_KEY_DOWN) {
      pressed.push_back(e.key.key);
    } else if (e.type == SDL_EVENT_KEY_UP) {
      pressed.erase(
          std::remove(pressed.begin(), pressed.end(), e.key.key),
          pressed.end());
    }
  }

  handleKeyPresses();

  if (!Ship::player.dead) {
    Ship::player.tick();
    Asteroid::spawn(score);
    doCollisions();

    if (tick == 1) {
      Beam::filter();
      Asteroid::filter();
      score++;
    }

    Asteroid::tick();
  }

  BackgroundOffset -= .1f;
  animationState += .05f;

  if ((int)animationState == 4)
    animationState = 0; // reset animation before 5

  renderParticles();

  Particle::tick();

  renderAsteroids();

  renderBeams();

  renderLives();

  
  SDL_RenderTextureRotated(
      renderer, ShipsTexture, Ship::player.getSrcRect(animationState),
      Ship::player.getDstRect(), (Ship::player.rotation - M_PI) * -180 / M_PI,
      NULL, SDL_FLIP_NONE);

  if (Ship::player.isInvis()) {
    SDL_RenderTextureRotated(renderer, ForceFieldTexture, &ForceFieldSrcRect,
                     Ship::player.getDstRect(),
                     (Ship::player.rotation - M_PI) * -180 / M_PI, NULL,
                     SDL_FLIP_NONE);
  }

  return ret;
}

Game::~Game() {
  SDL_DestroyTexture(this->BgTexture);
  SDL_DestroyTexture(this->ShipsTexture);
  SDL_DestroyTexture(this->BeamTexture);
  SDL_DestroyTexture(this->AsteroidsTexture);
}

void Game::doCollisions() {
  for (Beam &b : Beam::beams) {
    for (Asteroid &a : Asteroid::asteroids) {
      bool hit = a.intersects(b.head);
      hit = hit || a.intersects(b.tail);
      if (hit) {
        b.removeMe = true;
        b.X = 1000000; // move out of bounds deleted by beam::filter
        a.damage();
      }
    }
  }
  bool hit = false;
  for (Asteroid &a : Asteroid::asteroids) {
    if (a.intersects(Ship::player.getColRect())) {
      hit = true;
      break;
    }
  }
  if (hit) {
    Ship::player.damage(1);
  }
}

void Game::renderBeams() {
  for (Beam &b : Beam::beams) {
    const SDL_FRect dst = b.getDstRect();
    SDL_RenderTextureRotated(renderer, BeamTexture, NULL, &dst,
                     (b.rot - M_PI) * -180 / M_PI, NULL, SDL_FLIP_NONE);
    b.tick();
  }
}

void Game::renderAsteroids() {
  for (Asteroid &a : Asteroid::asteroids) {
    const SDL_FRect src = a.getSrcRect(), dst = a.getDstRect();
    if (debug) {
      SDL_RenderRect(renderer, &dst);
    }
    SDL_RenderTextureRotated(renderer, AsteroidsTexture, &src, &dst, a.rot, NULL,
                     SDL_FLIP_NONE);
  }
}

void Game::renderParticles() {
  for (Particle &p : Particle::particles) {
    SDL_Color c = p.getDrawColor();
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.g, c.a);
    SDL_FRect r = p.getRect();
    SDL_RenderFillRect(renderer, &r);
  }
}

void Game::handleKeyPresses() {
  if (Util::isPressed(pressed, {SDLK_UP, SDLK_W})) {
    Ship::player.accel(ACCEL_MOD);
  }
  if (Util::isPressed(pressed, {SDLK_LEFT, SDLK_A}))
    Ship::player.rot(STEERING_MOD);
  if (Util::isPressed(pressed, {SDLK_RIGHT, SDLK_D}))
    Ship::player.rot(-STEERING_MOD);
  if (Util::isPressed(pressed, SDLK_SPACE))
    Ship::player.shoot();
}

void Game::renderLives() {
  for (int i = 0; i < Ship::player.getHealth(); i++) {
    const SDL_FRect dst = SDL_FRect{static_cast<float>(890 + 50 * i), 20, 40, 60};
    SDL_RenderTexture(renderer, ShipsTexture,
                   Ship::player.getSrcRect(animationState), &dst);
  }
}
} // namespace AsteroidShooter