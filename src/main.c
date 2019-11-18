#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define F_CPU 1000000UL
#include <util/delay.h>

volatile uint8_t pattern = 0;
volatile uint8_t state = 0; // the active rgb led
volatile uint8_t color_state = 0; // the active color within rgb led
volatile uint8_t value_state = 0; // the value step
volatile uint16_t delay_state = 0;

int main() {
  DDRA = (1 << DDA0) | (1 << DDA1) | (1 << DDA2) | (1 << DDA3);
  DDRB = (1 << DDB0) | (1 << DDB1) | (1 << DDB2);

  PORTA = (1 << PORTA0) | (1 << PORTA1) | (1 << PORTA3) | (1 << PORTA7);
  PORTB = 0xFF;

  TCCR0B = (1 << CS00) | (1 << CS02);

  GIMSK = (1 << PCIE0);
  PCMSK0 = (1 << PCINT7);
  TIMSK0 = (1 << TOIE0);

  // grb
  uint8_t led_state[2][15][3] = {
    {
      {0, 0, 1},
      {1, 0, 0},
      {0, 0, 4},
      {4, 0, 0},
      {0, 0, 7},
      {7, 0, 0},
      {0, 0, 10},
      {10, 0, 0},
      {0, 0, 13},
      {13, 0, 0},
      {0, 0, 16},
      {16, 0, 0},
      {16, 0, 16},
      {16, 0, 8},
      {8, 0, 16}
    },
    {
      {16, 0, 0},
      {0, 0, 16},
      {16, 0, 0},
      {0, 0, 16},
      {16, 0, 0},
      {0, 0, 16},
      {16, 0, 0},
      {0, 0, 16},
      {16, 0, 0},
      {0, 0, 16},
      {16, 0, 0},
      {0, 0, 16},
      {16, 0, 16},
      {0, 0, 0},
      {0, 0, 0}
    }
  };

  sei();

  while(1) {
    if(15 < value_state) {
      value_state = 0;
      color_state++;
    }

    if(2 < color_state) {
      color_state = 0;
      if(state < 15) {
        state++;
      } else {
        state = 0;
      }
    }

    uint8_t color_value = led_state[pattern][state][color_state];
    uint8_t color_on_off = 0;

    if(value_state < color_value) {
      color_on_off = 1;
    }

    PORTA = 15;
    PORTB = ~(color_on_off << color_state);
    PORTA = state;

    value_state++;
  }

  return 0;
}

/* // if button pressed, swap pattern */
/* ISR(PCINT0_vect) { */
/*   #<{(| if((PORTA & (1 << PORTA7)) == 0) { |)}># */
/*     if(pattern == 0) { */
/*       pattern = 1; */
/*     } else { */
/*       pattern = 0; */
/*     } */
/*   #<{(| } |)}># */
/* } */

ISR(TIM0_OVF_vect) {
  if(50 < delay_state) {
    delay_state = 0;
    if(pattern == 0) {
      pattern = 1;
    } else {
      pattern = 0;
    }
  } else {
    delay_state++;
  }
}
