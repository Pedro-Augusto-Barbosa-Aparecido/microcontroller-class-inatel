#define PUSH_BUTTON (1 << PB4);

const int tenPercentageOfOCRnAIn255 = (int) ((255 * 10) / 100);


int main() {
  DDRD |= (1 PD6);

  TCCR0A = (1 << COM0A1) + (1 << WGM01) + (1 << WGM00);  // pwm mode
  TCCR0B = (1 << CS02) + (1 << CS00);                    // configure prescaler 1024

  OCR0A = 0; // 250 counts of 4us -> 1ms delay
  
  PCICR = (1 << PCIE1);
  PCMSK1 |= PUSH_BUTTON;
  
  sei();

  for (;;) {

  }
}

ISR(PCIE1_vect) {
  if ((PINB & PUSH_BUTTON) == PUSH_BUTTON) {
    if (OCR0A >= 255) {
      OCR0A += tenPercentageOfOCRnAIn255;
    } else {
      OCR0A = 0;
    }
  }
}
