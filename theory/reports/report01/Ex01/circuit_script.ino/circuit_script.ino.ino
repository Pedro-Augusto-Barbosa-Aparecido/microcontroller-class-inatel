#define TURN_ON_BUTTON (1 << PC0)
#define TURN_OFF_BUTTON (1 << PC1)
#define SWITCH_AUTOMATIC_MODE (1 << PD3)
#define HIGH_SENSOR (1 << PD4)
#define LOW_SENSOR (1 << PD5)
#define BOMB (1 << PB0)

void turnOffBomb() {
  PORTB &= ~BOMB;
}

void turnOnBomb() {
  PORTB |= BOMB;
}

int main() {
  // define pin of bomb as output
  DDRB = BOMB;

  // pull up on buttons on and off
  PORTC = TURN_OFF_BUTTON;

  turnOffBomb();

  for (;;) {
    // reading switch
    short int isSwitchActivated = PIND & SWITCH_AUTOMATIC_MODE;

    // automatic mode
    if (isSwitchActivated == 0) {
      short int isSensorHighActivated, isSensorLowActivated;
      isSensorHighActivated = PIND & HIGH_SENSOR;
      isSensorLowActivated = PIND & LOW_SENSOR;

      if (isSensorHighActivated == HIGH_SENSOR) {
        turnOffBomb();
      } else if (isSensorLowActivated == LOW_SENSOR) {
        turnOnBomb();
      }
    } else {
      short int isTurnOnButtonPressed, isTurnOffButtonPressed;
      isTurnOffButtonPressed = PINC & TURN_OFF_BUTTON;
      isTurnOnButtonPressed = PINC & TURN_ON_BUTTON;

      if (isTurnOffButtonPressed == 0) {
        turnOffBomb();
      } else if (isTurnOnButtonPressed == TURN_ON_BUTTON) {
        turnOnBomb();
      }
    }
  }
}
