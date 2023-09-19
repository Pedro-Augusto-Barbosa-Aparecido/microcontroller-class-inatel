#define TURN_ON_BUTTON (1 << PD3)
#define TURN_OFF_BUTTON (1 << PD2)

#define MOTOR (1 << PB1)

int main() {
  DDRB = MOTOR;

  PORTD |= TURN_OFF_BUTTON;
  PORTB &= ~MOTOR;

  // interrupt coinfiguration INT0 (PD2) and INT1 (PD3)
  EICRA = (1 << ISC01) + (0 << ISC00) + (1 << ISC11) + (1 << ISC10);
  EIMSK = (1 << INT1) + (1 << INT0);
  
  sei();

  for (;;) {

  }
}

ISR(INT0_vect) {
  PORTB &= ~MOTOR;
}

ISR(INT1_vect) {
  PORTB |= MOTOR;
}
