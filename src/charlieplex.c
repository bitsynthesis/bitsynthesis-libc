#include "charlieplex.h"

void charlieplex_update_active(CharliePlex *cp) {
  uint8_t led_value = *(cp->led_values + cp->led_index);

  if(cp->value_index < led_value) {
    cp->led_active = true;
  } else {
    cp->led_active = false;
  }
}

CharliePlex charlieplex_new(
  uint8_t led_count,
  uint8_t value_count,
  uint8_t *led_values
) {
  CharliePlex cp = {
    .led_count = led_count,
    .led_index = 0,
    .led_values = led_values,
    .value_count = value_count,
    .value_index = 0
  };

  charlieplex_update_active(&cp);

  return cp;
}

void charlieplex_step(CharliePlex *cp) {
  // advance indexes
  if(cp->value_index < (cp->value_count - 1)) {
    cp->value_index++;
  } else {
    cp->value_index = 0;

    if(cp->led_index < (cp->led_count - 1)) {
      cp->led_index++;
    } else {
      cp->led_index = 0;
    }
  }

  // update state
  charlieplex_update_active(cp);
}
