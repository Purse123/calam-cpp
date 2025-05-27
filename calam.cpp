#include <iostream>
#include "calam.h"

void display(void) {
  std::cout << "Hello world" << std::endl;
}

void putPixel(u32* frameBuffer, vec2D p, RGBA color) {
  int x = p.x;
  int y = p.y;
  
  if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT) return;
  frameBuffer[y * WIDTH + x] =
    (color .a << 24) | (color .b << 16) | (color .g << 8) | color.r;
}

void putLine(u32* frameBuffer, vec2D p1, vec2D p2, RGBA c) {
  int dx = abs(p2.x - p1.x);
  int dy = abs(p2.y - p1.y);

  int incrementer_x = (p2.x > p1.x) ? 1 : -1;
  int incrementer_y = (p2.y > p1.y) ? 1 : -1;

  if (dy <= dx) {
    int desPar = 2 * dy - dx;
    for (int i = 0; i <= dx; ++i) {
      putPixel(frameBuffer, p1, c);
      p1.x += incrementer_x;
      if (desPar < 0) {
        desPar += 2 * dy;
      } else {
        desPar += 2 * dy - 2 * dx;
        p1.y += incrementer_y;
      }
    }
  } else {
    int desPar = 2 * dx - dy;
    for (int i = 0; i <= dy; ++i) {
      putPixel(frameBuffer, p1, c);
      p1.y += incrementer_y;
      if (desPar < 0) {
        desPar += 2 * dx;
      } else {
        desPar += 2 * dx - 2 * dy;
        p1.x += incrementer_x;
      }
    }
  }
}

void putTriangle (u32* frameBuffer, vec2D p1, vec2D p2, vec2D p3, RGBA c) {
  putLine(frameBuffer, p1, p2, c);
  putLine(frameBuffer, p3, p2, c);
  putLine(frameBuffer, p1, p3, c);
}

void EightSegSymmetry(u32* frameBuffer, vec2D center, int x, int y, RGBA c) {
  putPixel (frameBuffer, {center.x + x, center.y + y}, c);
  putPixel (frameBuffer, {center.x - x, center.y + y}, c);
  putPixel (frameBuffer, {center.x + x, center.y - y}, c);
  putPixel (frameBuffer, {center.x - x, center.y - y}, c);

  putPixel (frameBuffer, {center.x + y, center.y + x}, c);
  putPixel (frameBuffer, {center.x - y, center.y + x}, c);
  putPixel (frameBuffer, {center.x + y, center.y - x}, c);
  putPixel (frameBuffer, {center.x - y, center.y - x}, c);
}

void putCircle (u32* frameBuffer, vec2D center, int radius, RGBA c) {
  int x = 0;
  int y = radius;
  int p0 = 1 - radius;

  while (x <= y) {
    EightSegSymmetry(frameBuffer, center, x, y, c);
    if (p0 < 0)
      p0 += 2 * x + 1;
    else {
      p0 += 2 * x + 1 - 2 * y;
      y--;
    }
    x++;
  }
}

void plot_ellipse_points (u32* frameBuffer, vec2D center, int x, int y, RGBA c) {
  putPixel (frameBuffer, {center.x + x, center.y + y}, c);
  putPixel (frameBuffer, {center.x - x, center.y + y}, c);
  putPixel (frameBuffer, {center.x + x, center.y - y}, c);
  putPixel (frameBuffer, {center.x - x, center.y - y}, c);
}

void putEllipse (u32* frameBuffer, vec2D center, vec2D radius, RGBA c) {
  int x = 0, y = radius.y;

  // initial paramter for region 1
  // slope < 1, x increments & y-plot
  int p10 = pow(radius.y, 2)
          - pow(radius.x, 2) * radius.y
          + pow(radius.x, 2) / 4;
  int dx = 2 * pow(radius.y, 2) * x;
  int dy = 2 * pow(radius.x, 2) * y;

  while (dx < dy) {
    plot_ellipse_points(frameBuffer, center, x, y, c);

    x++;
    if (p10 < 0) {
      dx += 2 * pow(radius.y, 2);
      p10 += dx + pow(radius.y, 2);
    } else {
      y--;
      dx += 2 * pow(radius.y, 2);
      dy -= 2 * pow(radius.x, 2);
      p10 += dx - dy + pow(radius.y, 2);
    }
  }

  // initial paramter for region 2
  // slope > 1, y increments & x-plot
  int p20 = pow(radius.y, 2) * pow(x + 0.5, 2)
          + pow(radius.x, 2) * pow(y - 1, 2)
          - pow(radius.x, 2) * pow(radius.y, 2);
  while (y >= 0) {
    plot_ellipse_points(frameBuffer, center, x, y, c);

    y--;
    if (p20 > 0) {
      dy -= 2 * pow(radius.x, 2);
      p20 += pow(radius.x, 2) - dy;
    } else {
      x++;
      dx += 2 * pow(radius.y, 2);
      dy -= 2 * pow(radius.x, 2);
      p20 += dx - dy + pow(radius.x, 2);
    }
  }
}
