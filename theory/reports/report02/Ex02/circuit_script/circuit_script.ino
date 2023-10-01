#define TURN_ON_BUTTON (1 << PC0)
#define TURN_OFF_BUTTON (1 << PC1)
#define SENSOR_ONE (1 << PB0)
#define SENSOR_TWO (1 << PB1)
#define ADVANCE (1 << PD1)
#define RECOIL (1 << PD2)
#define M1 (1 << PD3)

int main() {
  DDRD = M1 + ADVANCE + RECOIL;
  PORTC = TURN_OFF_BUTTON;

  DDRD &= ~(M1 + ADVANCE + RECOIL);

  PCICR = (1 << PCIE1);
  PCMSK1 = SENSOR_ONE + SENSOR_TWO;

  sei();

  for (;;) {
    short int isTurnOnButtonPressed = PINC & TURN_ON_BUTTON;
    short int isTurnOffButtonPressed = PINC & TURN_OFF_BUTTON;

    if (isTurnOnButtonPressed == TURN_ON_BUTTON) {
      DDRD |= (M1 + ADVANCE);
    } else if (!isTurnOffButtonPressed) {
      DDRD &= ~(M1 + ADVANCE);
      DDRD |= RECOIL;
      _delay_ms(800);
      DDRD &= ~(RECOIL);
    }
  }
}

ISR(PCIE1_vect) {
  if (PINB & SENSOR_ONE) {
    DDRD |= ADVANCE;
  } else if (!(PINB & SENSOR_ONE)) {
    DDRD &= ~(RECOIL + ADVANCE);
  } else if ((PINB & SENSOR_TWO) || !(PINB & SENSOR_ONE)) {
    DDRD &= ~(M1 + ADVANCE);
    DDRD |= RECOIL;
  } 
}