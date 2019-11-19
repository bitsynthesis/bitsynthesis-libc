#ifndef _OSCILLATOR_H_
#define _OSCILLATOR_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef enum {
  OSCILLATOR_DOWN,
  OSCILLATOR_UP
} OscillatorDirection;

typedef struct Oscillator {
  OscillatorDirection direction;
  uint8_t increment;
  uint8_t value;
} Oscillator;

Oscillator oscillator_new(uint8_t increment);
void oscillator_step(Oscillator *osc);
void oscillator_reset(Oscillator *osc);

#endif
