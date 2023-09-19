#define LED_PIN_D5 (1 << PD5)
#define LED_PIN_D6 (1 << PD6)
#define LED_PIN_D7 (1 << PD7)
#define LED_PIN_B1 (1 << PB1)

#define BUTTON_PCINT0 (1 << PCINT0)
#define BUTTON_PCINT2 (1 << PCINT2)
#define BUTTON_PCINT20 (1 << PCINT20)

// Na interrupção PCINT0
ISR(PCINT2_vect) {
  // if (PCINT2_vect == BUTTON_PCINT20) {
      PORTB |= LED_PIN_B1;
      _delay_ms(500);  
      PORTB &= ~(LED_PIN_B1);
  // }
}
// Na interrupção PCINT1
ISR(PCINT1_vect) {
  /* CÓDIGO QUE VAI RODAR
 NA INTERRUPÇÃO DO PCINT1 */
}
// Na interrupção PCINT2
ISR(PCINT0_vect) {
  if (!(PINB & BUTTON_PCINT2)) {
      PORTD ^= LED_PIN_D6;
      _delay_ms(500);  
      PORTD ^= LED_PIN_D6;
  } else if (!(PINB & BUTTON_PCINT0)) {
      PORTD ^= LED_PIN_D7;
      _delay_ms(1000);  
      PORTD ^= LED_PIN_D7;
  }
}
int main(void) {
  PORTB = (1 << PB0) + (1 << PB2);
  PORTD = (1 << PD4);

  DDRD = LED_PIN_D5 + LED_PIN_D6 + LED_PIN_D7;
  DDRB = LED_PIN_B1;

  PCICR |= (1 << PCIE2) + (1 << PCIE0);
  PCMSK2 |= BUTTON_PCINT20;
  PCMSK0 |= BUTTON_PCINT0 + BUTTON_PCINT2;
  sei();

  for (;;) {
    PORTD ^= LED_PIN_D5;
    _delay_ms(250);   
  }
}