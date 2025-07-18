#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdint.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

typedef unsigned char u8;
typedef char c8;
typedef int32_t i32;
typedef uint64_t u64;

int main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stdout, "[Format] %s <input.txt> <output>\n", argv[0]);
    return 1;
  }

  const char *input_file = argv[1];
  const char *output_file = argv[2];

  FILE *fp = fopen(input_file, "r");
  if (!fp) {
    fprintf(stderr, "[Error] Could not open (%s)\n", input_file);
    return 1;
  }

  int width = 0, height = 0, channels = 0;
  if (fscanf(fp, "Width: %d\nHeight: %d\nChannels: %d\n", &width, &height, &channels) != 3) {
    fprintf(stderr, "[Error] Invalid header in input file\n");
    fclose(fp);
    return 1;
  }

  if (channels != 4) {
    fprintf(stderr, "[Error] Only RGBA (4 channels) supported\n");
    fclose(fp);
    return 1;
  }

  u64 img_size = (u64)(width * height * channels);
  u8 *data = (u8 *)malloc(img_size);
  if (!data) {
    fprintf(stderr, "[Error] Buy more RAM...lol\n");
    fclose(fp);
    return 1;
  }

  for (int i = 0; i < width * height; i++) {
    int r, g, b, a;
    if (fscanf(fp, "%d %d %d %d", &r, &g, &b, &a) != 4) {
      fprintf(stderr, "[Error] Invalid pixel data at index %d\n", i);
      free(data);
      fclose(fp);
      return 1;
    }
    
    data[i * 4 + 0] = (u8)r;
    data[i * 4 + 1] = (u8)g;
    data[i * 4 + 2] = (u8)b;
    data[i * 4 + 3] = (u8)a;
  }
  fclose(fp);

  // Write PNG
  if (!stbi_write_png(output_file, width, height, channels, data, width * channels)) {
    fprintf(stderr, "[Error] Failed to write image (%s)\n", output_file);
    free(data);
    return 1;
  }

  free(data);
  printf("PNG image written to %s\n", output_file);
  return 0;
}
