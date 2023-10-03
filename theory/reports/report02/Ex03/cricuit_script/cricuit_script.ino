#define TURN_ON_BUTTON (1 << PB0)
#define TURN_OFF_BUTTON (1 << PD3)
#define SENSOR_ONE (1 << PB1)
#define SENSOR_TWO (1 << PB2)
#define SENSOR_THREE (1 << PD2)
#define M1 (1 << PD1)
#define ALARM (1 << PD4)
#define BUZZER (1 << PD5)

ISR(INT1_vect) {
  if ((PIND & TURN_OFF_BUTTON) == TURN_OFF_BUTTON) {
    PORTD &= ~(M1 + ALARM + BUZZER);
  }
}

int main() {
  PORTB = TURN_ON_BUTTON;
  DDRD = (ALARM + BUZZER + M1);

  EICRA = (1 << ISC11) + (1 << ISC10);
  EIMSK = (1 << INT1);

  sei();

  for (;;) {
    short int isTurnOnButtonPressed = PINB & TURN_ON_BUTTON;
    short int isBigBoxIdentified = PINB & SENSOR_ONE;

    if (isTurnOnButtonPressed == 0) {
      PORTD |= M1;
    } else if (isBigBoxIdentified == SENSOR_ONE) {
      PORTD &= ~(M1);

      while (true) {
        PORTD |= (ALARM + BUZZER);
        _delay_ms(200);
        PORTD &= ~(ALARM);
      }
    }
  }
  
  return 0;
}