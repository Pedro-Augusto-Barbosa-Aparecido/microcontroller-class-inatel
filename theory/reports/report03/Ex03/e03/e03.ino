#define PUSH_BUTTON_ON (1 << PB1);
#define PUSH_BUTTON_OFF (1 << PB2);

unsigned int timer = 0;

int main() {
  DDRD |= (1 PD1);

  TCCR0A = (1 << COM0A1) + (1 << WGM01) + (1 << WGM00);  // pwm mode
  TCCR0B = (1 << CS02) + (1 << CS00);                    // configure prescaler 1024

  OCR0A = 0; // 250 counts of 4us -> 1ms delay
  
  PCICR = (1 << PCIE0);
  PCMSK0 |= PUSH_BUTTON_ON + PUSH_BUTTON_OFF;
  
  sei();

  for (;;) {

  }
}

ISR(PCINT0_vect) {
    if ((PINB & PUSH_BUTTON_OFF) == 0) {
      timer = 0;
    } else if ((PINB & PUSH_BUTTON_ON) == PUSH_BUTTON_ON) {
      timer = 1;
    }
}

ISR(TIMER0_COMPA_vect) {
  if ((PIND & PUSH_BUTTON_ON) == PUSH_BUTTON_ON) {
      if (timer++ > 10001) {
        PORTD |= (1 << PD1);
      } else {
        PORTD &= ~(1 << PD1);
      }
  } else {
      PORTD &= ~(1 << PD1);
  }
}
