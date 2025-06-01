#ifndef CALAM_H_
#define CALAM_H_

#include <cstdint>
#include <SDL2/SDL.h>
#include "Canvas.h"
#include <iostream>

struct vec2D { int x, y; };
struct RGBA { u32 r, g, b, a; };

class Calam {
 public:
  Calam(Canvas &canvas);
  
  void putPixel (vec2D p, RGBA color);
  void putLine (vec2D p1, vec2D p2, RGBA c);
  void putFillRect(vec2D p1, vec2D p2, RGBA c);
  void putRect (vec2D p1, vec2D p2, RGBA c);
  void putTriangle (vec2D p1, vec2D p2, vec2D p3, RGBA c);
  void putFillTriangle (vec2D p1, vec2D p2, vec2D p3, RGBA c);
  void putCircle (vec2D center, int radius, RGBA c);
  void putEllipse (vec2D center, vec2D radius, RGBA c);

 private:
  Canvas &canvas;
};
  
#endif
