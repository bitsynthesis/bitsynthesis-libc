#include "color.h"

void color_hue_to_rgb(Color *color) {
  uint16_t hue = color->hue;
  uint16_t saturation = 255;
  uint16_t value = 255;

  uint8_t region = color->hue / 43;

  uint8_t p = 0;
  uint8_t t = (hue - (region * 43)) * 6;
  uint8_t q = (value * (255 - ((saturation * t) >> 8))) >> 8;

  switch(region) {
    case 0:
      color->red = value;
      color->green = t;
      color->blue = p;
      break;
    case 1:
      color->red = q;
      color->green = value;
      color->blue = p;
      break;
    case 2:
      color->red = p;
      color->green = value;
      color->blue = t;
      break;
    case 3:
      color->red = p;
      color->green = q;
      color->blue = value;
      break;
    case 4:
      color->red = t;
      color->green = p;
      color->blue = value;
      break;
    default:
      color->red = value;
      color->green = p;
      color->blue = q;
  }
}
