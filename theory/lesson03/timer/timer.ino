unsigned int counter = 0;
unsigned int seconds = 0;
unsigned int minutes = 0;
unsigned int hour = 0;

int main() {
  Serial.begin(115200);

  // configure timer 0 works as comparator
  TCCR0A = (1 << WGM01) + (0 << WGM00); // comparator mode
  TCCR0B = (1 << CS01) + (1 << CS00); 
  /*
    PreScaler: 64
    Frequency: 250KHz
    Period of each count: 4us
  */

  OCR0A = 249; // 250 counts of 4us -> 1ms delay
  TIMSK0 = (1 << OCIE0A); // enable interrupt on comparator A of timer 0

  sei();
  for (;;);
}

// interrupt happened each 1ms
ISR(TIMER0_COMPA_vect) {
  if (++counter == 1000) {
    counter = 0;

    if (++seconds == 60) {
      seconds = 0;

      if (++minutes == 60) {
        minutes = 0;

        if (++hour == 24) {
          hour = 0;
        }
      }
    }
  }

  Serial.print(hora);
  Serial.print(":");
  Serial.print(minutes);
  Serial.print(":");
  Serial.print(seconds);
  Serial.println("");
}
