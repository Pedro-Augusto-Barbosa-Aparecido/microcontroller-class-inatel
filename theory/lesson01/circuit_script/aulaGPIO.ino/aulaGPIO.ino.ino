#define SWITCH (1 << PD3)
#define TURN_ON_BUTTON (1 << PC0)
#define TURN_OFF_BUTTON (1 << PC1)
#define LOW_SENSOR (1 << PD4)
#define HIGH_SENSOR (1 << PD5)
#define BOMB (1 << PB0)

int main() {
  // define bomb as out
  DDRB = BOMB;

  // define pullup resistor to turn off button 
  PORTC = TURN_OFF_BUTTON;

  // optional - standard output's
  // turn off bomb
  PORTB &= ~(BOMB);
 
  // process
  for (;;) {
    // read automan key
    short int isSwitchActive = PIND & SWITCH;

    if (isSwitchActive == 0) {
        // automatic mode
        // read of sensors
        short int isSensorHighActive, isSensorLowActive;
        isSensorHighActive = PIND & HIGH_SENSOR;
        isSensorLowActive = PIND & BOMB;

        if (isSensorHighActive == HIGH_SENSOR) 
            PORTB &= ~(BOMB);
        else if (isSensorLowActive == 0) 
            PORTB |= BOMB;
    } else {
      // manual mode
      // read buttons
      short int isTurnOffButtonPressed, isTurnOnButtonPressed;
      isTurnOffButtonPressed = PINC & TURN_OFF_BUTTON;
      isTurnOnButtonPressed = PINC & TURN_ON_BUTTON;

      if (isTurnOffButtonPressed == 0) 
        PORTB &= ~(BOMB);
      else if (isTurnOnButtonPressed == TURN_ON_BUTTON) 
        PORTB |= BOMB;
    }
  }
}