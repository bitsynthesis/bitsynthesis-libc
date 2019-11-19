#include "oscillator.h"

Oscillator oscillator_new(uint8_t increment) {
  Oscillator osc = {
    .direction = OSCILLATOR_DOWN,
    .increment = increment,
    .value = 255
  };
  return osc;
}

void oscillator_step(Oscillator *osc) {
  int16_t value = osc->value;
  switch(osc->direction) {
    case OSCILLATOR_DOWN:
      value -= osc->increment;
      if(value <= 0) {
        osc->value = 0;
        osc->direction = OSCILLATOR_UP;
      } else {
        osc->value = (uint8_t) value;
      }
      break;
    case OSCILLATOR_UP:
      value += osc->increment;
      if(255 <= value) {
        osc->value = 255;
        osc->direction = OSCILLATOR_DOWN;
      } else {
        osc->value = (uint8_t) value;
      }
      break;
    default:
      break;
  }
}

void oscillator_reset(Oscillator *osc) {
  osc->value = 255;
  osc->direction = OSCILLATOR_DOWN;
}
