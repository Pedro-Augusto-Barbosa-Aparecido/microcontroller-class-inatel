ISR(INT0_vect) {
  PORTD |= 0b00010000;
  _delay_ms(1000);
  PORTD &= ~(0b00010000); 
}

int main() {
  DDRD = 0b00110000;
  PORTD = 1 << PD2;

  EICRA = 0b00001000;
  EIMSK = 0b00000001;

  sei();

  for (;;) {
    PORTD ^= 0b00100000;
    _delay_ms(500);
  }

  return 0;
}