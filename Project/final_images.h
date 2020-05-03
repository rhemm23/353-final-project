#ifndef __FINAL_IMAGES_H__
#define __FINAL_IMAGES_H__

#include <stdint.h>

/* Bitmap info for asteroid */
extern const uint8_t asteroidBitmaps[];
extern const uint8_t asteroidWidthPages;
extern const uint8_t asteroidWidthPixels;
extern const uint8_t asteroidHeightPixels;

/* Bitmap info for ship */
extern const uint8_t shipBitmaps[];
extern const uint8_t shipWidthPages;
extern const uint8_t shipWidthPixels;
extern const uint8_t shipHeightPixels;

// Alphabet
extern const uint8_t letters[];
typedef struct {
  uint16_t width;
  uint16_t offset;
} FONT_CHAR_INFO;
extern const FONT_CHAR_INFO letters_indexs[];

#endif