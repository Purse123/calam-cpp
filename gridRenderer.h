#pragma once
#include "calam.h"
#include "Canvas.h"

class GridRenderer {
 public:
  GridRenderer(Canvas &canvas, Calam &calam, int gridCols, int gridRows):
    canvas(canvas), calam(calam), cols(gridCols), rows(gridRows) {
    tileWidth = canvas.getWidth() / cols;
    tileHeight = canvas.getHeight() / rows;
  }
  /*  
  void draw(int* world, RGBA wallColor, RGBA floorColor) {
    for (int y = 0; y < rows; ++y) {
      for (int x = 0; x < cols; ++x) {
	int value = world[y * cols + x];
	RGBA color = (value == 1) ? wallColor : floorColor;

	int w = (x == cols - 1) ? canvas.getWidth() - tileWidth * x: tileWidth;
	int h = (y == rows - 1) ? canvas.getHeight() - tileHeight * y: tileHeight;

	// calam.putFillRect({tileWidth * x, tileHeight * y}, {w, h}, color);
	calam.putRect({tileWidth * x, tileHeight * y}, {w, h}, color);
      }
    }
  }
  */
  void draw(int* world, RGBA wallColor, RGBA floorColor) {
    for (int row = 0; row <= rows; ++row) {
      for (int col = 0; col <= cols; ++col) {
	int value = world[row * cols + col];
	RGBA color = (value == 1) ? wallColor : floorColor;

	int x = col * tileWidth;
	int y = row * tileHeight;

	int w = (col == cols - 1) ? canvas.getWidth() - x : tileWidth;
	int h = (row == rows - 1) ? canvas.getHeight() - y : tileHeight;

	calam.putRect({x, y}, {w, h}, color);
      }
    }
  }
  
private:
  Canvas &canvas;
  Calam &calam;
  int cols, rows;
  int tileWidth, tileHeight;
};
