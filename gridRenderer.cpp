#include "gridRenderer.h"
#include <SDL2/SDL.h>

#define FACTOR 90
#define WIDTH (16 * FACTOR)
#define HEIGHT (9 * FACTOR)

#define GRIDCOLS 4
#define GRIDROWS 4

int main() {
  Canvas canvas(WIDTH, HEIGHT);
  Calam calam(canvas);
  GridRenderer grid(canvas, calam, GRIDCOLS, GRIDROWS);

  int world[GRIDROWS * GRIDCOLS] = {0};
  // for (int i = 3; i < 8; ++i) {
    // world[i] = 1;
  // }
  // int world[GRIDROWS * GRIDCOLS] = {
    // 0, 0, 0, 0, 0, 0,
    // 0, 0, 0, 1, 0, 0,
    // 0, 0, 0, 1, 1, 0,
    // 0, 0, 0, 0, 0, 0
  // };

  RGBA wallColor = {0, 0, 255, 255};
  RGBA floorColor = {255, 0, 0, 255};

  // Draw only if needed (could skip rendering if allZero, or draw floor anyway)
  grid.draw(world, wallColor, floorColor);

  canvas.clear();
  canvas.update();
  canvas.present();

  SDL_Delay(5000);
  return 0;
}
