#include <iostream>
#include <SDL2/SDL.h>
#include <cstdint>
#include <cstring>
#include "calam.h"

int main() {
  if (SDL_Init(SDL_INIT_VIDEO)) {
    std::cerr << "[ERROR] SDL_Init Error: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Window* win = SDL_CreateWindow(
    "Raycasting in nutshell",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    WIDTH, HEIGHT,
    SDL_WINDOW_SHOWN
  );
  
  if (!win) {
    std::cerr << "[ERROR] STD_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE);				/* Sets hardware-accelerated 2d renderer context */

  if (!renderer) {
    std::cerr << "[ERROR] STD_CreateRenderer Error: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 1;
  }

  SDL_Texture* texture = SDL_CreateTexture(
    renderer, SDL_PIXELFORMAT_ABGR8888,
    // SDL_TEXTUREACCESS:
    // 1. STATIC: change rarely, not locable
    // 2. STREAMING: change frequently, locable
    // 3. Texture used as render target
    SDL_TEXTUREACCESS_STREAMING,
    WIDTH, HEIGHT
  );

  u32* frameBuffer = new u32[WIDTH * HEIGHT];
  memset(frameBuffer, 0, WIDTH * HEIGHT * sizeof(u32));
  
  vec2D p = {100, 200};
  RGBA cyan = {0, 255, 255, 255};
  putPixel (frameBuffer, p, cyan);

  // rect = NULL, represent area to update, NULL for entire texture
  // const void *pixels = frameBuffer, ray pixel data in texture format
  // int pitch = no of byte in row including padding
  SDL_UpdateTexture(texture, NULL, frameBuffer, WIDTH * sizeof(uint32_t));
  SDL_RenderClear(renderer);	// clear rendering target with drawing color
  
  // copy portion of current rendering target
  // SDL_Rect* srcrect: source, dstrect: destination (NULL strech to fill given rect)
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);			  /* Present rendered image to screen */
  
  vec2D p1 = {200, 400};
  vec2D p2 = {400, 200};
  putLine (frameBuffer, p1, p2, cyan);
  SDL_UpdateTexture(texture, NULL, frameBuffer, WIDTH * sizeof(uint32_t));
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);

  vec2D circle_center = {100, 100};
  int radius = 50;
  putCircle (frameBuffer, circle_center, radius, cyan);
  SDL_UpdateTexture(texture, NULL, frameBuffer, WIDTH * sizeof(uint32_t));
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);

  SDL_Delay(2000);

  delete[] frameBuffer;
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);
  SDL_Quit();
  
  return 0;
}
