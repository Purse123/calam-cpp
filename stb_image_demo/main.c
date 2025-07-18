#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

typedef unsigned char u8;
typedef char c8;
typedef int32_t i32;

i32 main(i32 argc, c8 **argv) {
  if (argc != 3) {
    fprintf(stdout, "[Format] %s <input> <output.txt>\n", argv[0]);
    return 1;
  }

  const c8 *input_file = argv[1];
  const c8 *output_file = argv[2];

  i32 width, height;
  i32 channel_in_file;			/* 8-bit components per pixel */
  i32 desired_channel = 4;
  
  // 4 channel RGBA
  // 141 line stb_image.h
  u8 *data = stbi_load(input_file, &width, &height, &channel_in_file, desired_channel);
  if (!data) {
    fprintf(stderr, "[Error] Couldnot load image (%s)\n", input_file);
    return 1;
  }

  FILE *fp = fopen(output_file, "w");
  if (!fp) {
    fprintf(stderr, "[Error] Couldnot load (%s)\n", output_file);
    stbi_image_free(data);
    return 1;
  }

  fprintf(fp, "Width: %d\nHeight: %d\nChannels: 4\n", width, height);
  if (ferror(fp)) {
    fprintf(stderr, "[Error] writing on (%s)\n", output_file);
    stbi_image_free(data);
    fclose(fp);
    return 1;
  }

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      int index = (y * width + x) * 4; // 4 for channels RGBA
      
      u8 r = data[index + 0];
      u8 g = data[index + 1];
      u8 b = data[index + 2];
      u8 a = data[index + 3];

      fprintf(fp, "%d %d %d %d ", r, g, b, a);
    }
    fprintf(fp, "\n");
  }

  fclose(fp);
  stbi_image_free(data);
  return 0;
}
