#define MOTOR (1 << PD2)
#define SENSOR (1 << PB3)
#define TURN_ON_BUTTON (1 << PB0)
#define TURN_OFF_BUTTON (1 << PB1)
#define ALARM (1 << PD6)

void turnOffMotor() {
  PORTD &= ~MOTOR;
}

void turnOnMotor() {
  PORTD |= MOTOR;
}

void turnOffAlarm() {
  PORTD &= ~ALARM;
}

void turnOnAlarm() {
  PORTD |= ALARM;
}

int main() {
  // define as output
  DDRD = MOTOR + ALARM;

  // define as pull
  // PORTB = TURN_OFF_BUTTON;

  turnOffAlarm();
  turnOffMotor();

  for (;;) {
    short int isSensorActivated = PINB & SENSOR;
    short int isTurnOffButtonIsPressed = PINB & TURN_OFF_BUTTON;
    short int isTurnOnButtonIsPressed = PINB & TURN_ON_BUTTON;

    if (isSensorActivated == SENSOR) {
      turnOffMotor();
      turnOnAlarm();
    } else if (isSensorActivated == 0) {
      turnOffAlarm();
    } 
    
    if (isTurnOffButtonIsPressed == TURN_OFF_BUTTON) {
      turnOffMotor();
    } else if (isTurnOnButtonIsPressed == TURN_ON_BUTTON) {
      turnOnMotor();
    } 
  }

}
