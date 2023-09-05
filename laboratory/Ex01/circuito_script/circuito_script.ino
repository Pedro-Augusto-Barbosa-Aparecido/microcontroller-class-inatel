#define TURN_ON_BUTTON (1 << PD3)
#define TURN_OFF_BUTTON (1 << PD4)
#define SENSOR (1 << PD2)
#define MOTOR (1 << PC1)
#define ALARM (1 << PC0)

int main() {
  DDRC = (MOTOR + ALARM);
  PORTC &= ~(MOTOR + ALARM);

  for (;;) {
    short int sensor = PIND & SENSOR;
    short int isTurnOffButtonPressed = PIND & TURN_OFF_BUTTON;
    short int isTurnOnButtonPressed = PIND & TURN_ON_BUTTON;

    if (sensor == SENSOR) {
      PORTC |= ALARM;
      PORTC &= ~(MOTOR);
    } else if (isTurnOffButtonPressed == NF) {
      PORTC &= ~(MOTOR);
    } else if (isTurnOnButtonPressed == NA) {
      PORTC |= MOTOR;
      PORTC &= ~(ALARM);
    }
  }

  return 0;
}