#define INTERRUPT_PB2 (1 << PB2)
#define INTERRUPT_PC4 (1 << PC4)
#define INTERRUPT_PD6 (1 << PD6)
#define INTERRUPT_PD2 (1 << PD2)
#define BUZZER (1 << PB4)

int main() {
  DDRB = 0;
  DDRC = 0;
  DDRD = 0;
  DDRB = BUZZER;

  // PORTB = INTERRUPT_PB2;
  // PORTC = INTERRUPT_PC4;
  // PORTD = INTERRUPT_PD2 + INTERRUPT_PD6;

  PORTB &= ~(BUZZER);

  PCICR = (1 << PCIE0) + (1 << PCIE1) + (1 << PCIE2);
  PCMSK0 = INTERRUPT_PB2;
  PCMSK1 = INTERRUPT_PC4;
  PCMSK2 = INTERRUPT_PD2 + INTERRUPT_PD6;

  sei();

  for (;;) {

  }
}

ISR(PCINT2_vect) {
  if ((PIND & INTERRUPT_PD2) || (PIND & INTERRUPT_PD6)) {
    PORTB |= BUZZER;
    _delay_ms(1000);
    PORTB &= ~(BUZZER);
  }
}

ISR(PCINT1_vect) {
  if (PINC & INTERRUPT_PC4) {
    PORTB |= BUZZER;
    _delay_ms(1000);
    PORTB &= ~(BUZZER);
  }
}

ISR(PCINT0_vect) {
  if (PINC & INTERRUPT_PB2) {
    PORTB |= BUZZER;
    _delay_ms(1000);
    PORTB &= ~(BUZZER);
  }
}

