#ifndef CALAM_H_
#define CALAM_H_

#include <cstdint>
#include <SDL2/SDL.h>

#define FACTOR 90
#define WIDTH (16 * FACTOR)
#define HEIGHT (9 * FACTOR)

using u32 = std::uint32_t;
struct vec2D {
  int x, y;
};

struct RGBA {
  u32 r, g, b, a;
};

void display(void);
void putPixel(u32* frameBuffer, int width, int height, vec2D p, RGBA color);
void putLine(u32* frameBuffer, int width, int height, vec2D p1, vec2D p2, RGBA c);

#endif
