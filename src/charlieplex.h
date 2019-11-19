#ifndef _CHARLIEPLEX_H_
#define _CHARLIEPLEX_H_

#include <stdbool.h>
#include <stdint.h>

// Represents a single chain of charlieplexed LEDs.
// If RGB done in serial, use one. If in parallel, use three.
typedef volatile struct CharliePlex {
  bool led_active;
  uint8_t led_count;
  uint8_t led_index;
  uint8_t *led_values;
  uint8_t value_count;
  uint8_t value_index;
} CharliePlex;

CharliePlex charlieplex_new(
  uint8_t led_count,
  uint8_t value_count,
  uint8_t *led_values
);

void charlieplex_step(CharliePlex *cp);

#endif
