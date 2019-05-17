#include <avr/io.h>
#include <util/delay.h>

#define DELAY 1000

int main() {
  DDRB = 0b000100000;

  while (true) {
    PORTB = 0b000100000;
    _delay_ms(DELAY);

    PORTB = 0b000000000;
    _delay_ms(DELAY);
  }
}
