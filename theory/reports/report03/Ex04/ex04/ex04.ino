#define PUSH_BUTTON_ON (1 << PB1);
#define PUSH_BUTTON_OFF (1 << PB2);

bool turnMotor = false;
bool counter = 0;
unsigned int power = (int)(255 * 0.125);
unsigned int motorPower = power;

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
  if ((PINB & PUSH_BUTTON_ON) == PUSH_BUTTON_ON) {
    if (motorPower <= 255) {
      motorPower += power;
    } else {
      motorPower = power;
    }
  }

  if ((PINB & PUSH_BUTTON_OFF) == 0) {
    motorPower = 0;
  }
}

ISR(TIMER0_COMPA_vect) {
  if (turnMotor && counter <= 8000) {
    OCR0A = motorPower;
  } else {
    counter = 0;
  }
}
