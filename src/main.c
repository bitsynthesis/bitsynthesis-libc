#include <avr/io.h>
#include <stdint.h>

#define F_CPU 1000000UL
#include <util/delay.h>

uint8_t state = 0;
uint8_t color_state = 0;

int main() {
  DDRA = (1 << DDA0) | (1 << DDA1) | (1 << DDA2) | (1 << DDA3);
  DDRB = (1 << DDB0) | (1 << DDB1) | (1 << DDB2);

  PORTA = (1 << PORTA0) | (1 << PORTA1) | (1 << PORTA3);
  PORTB = 0xFF;

  // grb
  uint8_t led_state[16][3] = {
    {0, 0, 1},
    {1, 0, 0},
    {0, 0, 1},
    {1, 0, 0},
    {0, 0, 1},
    {1, 0, 0},
    {0, 0, 1},
    {1, 0, 0},
    {0, 0, 1},
    {1, 0, 0},
    {0, 0, 1},
    {1, 0, 0},
    {0, 0, 1},
    {1, 0, 1},
    {1, 0, 1},
    {1, 0, 1}
  };

  while(1) {
    if(2 < color_state) {
      color_state = 0;
      if(state < 15) {
        state++;
      } else {
        state = 0;
      }
    }

    PORTA = 15;
    PORTB = ~(led_state[state][color_state] << color_state);
    PORTA = state;

    color_state++;

    /* _delay_ms(100); */
  }

  return 0;
}
