#include "gridRenderer.h"
#include <SDL2/SDL.h>

#define FACTOR 90
#define WIDTH (16 * FACTOR)
#define HEIGHT (9 * FACTOR)

#define GRIDCOLS 10
#define GRIDROWS 10

int main() {
  Canvas canvas(WIDTH, HEIGHT);
  Calam calam(canvas);
  GridRenderer grid(canvas, calam, GRIDCOLS, GRIDROWS);

  int world_map[GRIDCOLS][GRIDROWS] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,1,0,1,0,0,1},
    {1,0,1,0,1,0,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,1,0,1,0,0,1},
    {1,0,1,0,1,0,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}
  };

  RGBA wallColor = {0, 0, 255, 255};
  RGBA floorColor = {255, 0, 0, 255};

  // Draw only if needed (could skip rendering if allZero, or draw floor anyway)
  grid.draw_minimap(world_map, wallColor, floorColor);

  canvas.clear();
  canvas.update();
  canvas.present();

  SDL_Delay(5000);
  return 0;
}
