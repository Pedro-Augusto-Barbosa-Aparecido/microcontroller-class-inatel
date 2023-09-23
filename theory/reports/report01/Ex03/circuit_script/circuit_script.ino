#include <stdarg.h>

#define MOTOR_TRANSPORTER_TO_ELEVATOR (1 << PD0) // M1
#define MOTOR_TRANSPORTER_TO_VERIFICATION (1 << PD1) // M2
#define MOTOR_ELEVATOR (1 << PD2)
#define SENSOR_ONE (1 << PB0)
#define SENSOR_TWO (1 << PB1)
#define SENSOR_THREE (1 << PB2)
#define SENSOR_FOUR (1 << PB3)
#define TURN_ON_BUTTON (1 << PC0)
#define TURN_OFF_BUTTON (1 << PC1)
#define LAMP (1 << PD3)

bool isSystemRunning = false;

void turnOn(int qtdPins, ...) {
  int pinsToTurnOn = 0b00000000;

  va_list pins;
  va_start(pins, qtdPins);

  for (short int i = 0; i < qtdPins; i++) {
    pinsToTurnOn += va_arg(pins, int);
  }

  va_end(pins);

  PORTD |= pinsToTurnOn;
}

void turnOff(int qtdPins, ...) {
  int pinsToTurnOff = 0b00000000;

  va_list pins;
  va_start(pins, qtdPins);

  for (short int i = 0; i < qtdPins; i++) {
    pinsToTurnOff += va_arg(pins, int);
  }

  va_end(pins);

  PORTD &= ~pinsToTurnOff;
}

void blinkLamp() {
  turnOn(1, LAMP);

  _delay_ms(500);

  turnOff(1, LAMP);
}

ISR(PCINT1_vect) {
  if (!(PINC & TURN_OFF_BUTTON)) {
    turnOff(
      4,
      MOTOR_ELEVATOR, 
      MOTOR_TRANSPORTER_TO_ELEVATOR, 
      MOTOR_TRANSPORTER_TO_VERIFICATION,
      LAMP
    );

    isSystemRunning = false;
  }
}

int main() {
  // define outputs
  DDRD = MOTOR_ELEVATOR + MOTOR_TRANSPORTER_TO_ELEVATOR + MOTOR_TRANSPORTER_TO_VERIFICATION + LAMP;

  // pull up on turn off button
  PORTC = TURN_OFF_BUTTON;

  // config interrupt in PORTC
  PCICR |= (1 << PCIE1);

  PCMSK1 |= (1 << PCINT9);

  // set outputs as turned off by default
  turnOff(
    4,
    MOTOR_ELEVATOR, 
    MOTOR_TRANSPORTER_TO_ELEVATOR, 
    MOTOR_TRANSPORTER_TO_VERIFICATION,
    LAMP
  );

  sei();

  for (;;) {
    short int isTurnOnButtonPressed = PINC & TURN_ON_BUTTON;
    short int isTurnOffButtonPressed = PINC & TURN_OFF_BUTTON;
    short int isSensorOneActivated = PINB & SENSOR_ONE;
    short int isSensorTwoActivated = PINB & SENSOR_TWO;
    short int isSensorThreeActivated = PINB & SENSOR_THREE;
    short int isSensorFourActivated = PINB & SENSOR_FOUR;

    if (isTurnOnButtonPressed == TURN_ON_BUTTON) {
      turnOn(
        1,
        MOTOR_TRANSPORTER_TO_ELEVATOR
      );

      isSystemRunning = true;
    } else if (isTurnOffButtonPressed == 0) {
      turnOff(
        4,
        MOTOR_ELEVATOR, 
        MOTOR_TRANSPORTER_TO_ELEVATOR, 
        MOTOR_TRANSPORTER_TO_VERIFICATION,
        LAMP
      );

      isSystemRunning = false;
    } else if (isSensorOneActivated == SENSOR_ONE && isSystemRunning) {
      turnOff(
        1,
        MOTOR_TRANSPORTER_TO_ELEVATOR
      );

      _delay_ms(3000);

      turnOn(
        1,
        MOTOR_ELEVATOR
      );
    } else if (isSensorTwoActivated == SENSOR_TWO && isSystemRunning) {
      turnOff(
        1,
        MOTOR_ELEVATOR
      );

      turnOn(
        1,
        MOTOR_TRANSPORTER_TO_VERIFICATION
      );
    } else if (isSensorThreeActivated == SENSOR_THREE && isSystemRunning) {
      turnOff(
        1,
        MOTOR_TRANSPORTER_TO_VERIFICATION
      );

      _delay_ms(3000);

      turnOn(
        1,
        MOTOR_TRANSPORTER_TO_VERIFICATION
      );

      while ((PINB & SENSOR_THREE) == SENSOR_THREE && isSystemRunning) 
        blinkLamp();
    } else if (isSensorFourActivated == SENSOR_FOUR && isSystemRunning) {
      turnOff(
        4,
        MOTOR_ELEVATOR, 
        MOTOR_TRANSPORTER_TO_ELEVATOR, 
        MOTOR_TRANSPORTER_TO_VERIFICATION,
        LAMP
      );
    }
  }
}
