  #define BUTTON (1 << PD2)
  #define LED (1 << PD6)

  int brightness = 0;

  int main() {
    Serial.begin(9200);

    DDRD = LED;

    EICRA = 0b00000011;
    EIMSK = 0b00000001;

    // configure timer 0 works as comparator
    TCCR0A |= (1 << WGM01) | (1 << WGM00) | (1 << COM0A1);  // pwm mode
    TCCR0B = (0 << CS01) + (1 << CS00) + (0 << CS02);       // configure timer 0
    /*
      PreScaler: 64
      Frequency: 250KHz
      Period of each count: 4us
    */

    OCR0A = 0;               // 250 counts of 4us -> 1ms delay
    TIMSK0 = (1 << OCIE0A);  // enable interrupt on comparator A of timer 0

    PORTD &= ~LED;

    sei();
    for (;;) {
      if(brightness > 100)
        brightness = 0;
      OCR0A = (int)((255 * brightness) / 100);
    }
  }

  ISR(INT0_vect) {
    brightness += 10;
    Serial.println(brightness);
  }