#include <TimerOne.h>

void t() {
  analogWrite(6, 21929);
}

void setup() {
  // put your setup code here, to run once:
  DDRD = (1 << PD6);

  Timer1.initialize(4000000);
  Timer1.attachInterrupt(t);
  Timer1.pwm(6, 1024);
}

void loop() {
  // put your main code here, to run repeatedly:
}
