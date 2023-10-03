#define BotaoA (1 << PB5)
#define BotaoB (1 << PB4)
#define BotaoC (1 << PB3)
#define M1 (1 << PD5)
#define M2 (1 << PD6)
#define M3 (1 << PD7)

unsigned short int sum = 0;

void turnOn(short int motor) {
  if (sum == 150) {
    PORTD &= ~(M1 + M2);
    sum = 70;
    PORTD |= M3;
  } else if (sum == 100) {
    sum = 70;
    PORTD &= ~(M1 + M2);
    PORTD |= M3;
  } else if (sum == 120) {
    sum = 70;
    PORTD &= ~(M1 + M2);
    PORTD |= M3;
  } else
    PORTD |= motor;
}

ISR(PCINT0_vect) {
  short int botaoA = (PINB & BotaoA);
  short int botaoB = (PINB & BotaoB);
  short int botaoC = (PINB & BotaoC);

  if (botaoA == 0) {
    sum += 30;
    turnOn(M1);
  } 
  
  if (botaoA == BotaoA) {
    sum -= 30;
    PORTD &= ~(BotaoA);
  }

  if (botaoB == 0) {
    sum += 50;
    turnOn(M2);
  } 
  
  if (botaoB == BotaoB) {
    sum -= 50;
    PORTD &= ~(BotaoB);
  }

  if (botaoC == 0) {
    sum += 70;
    turnOn(M3);
  } 
  
  if (botaoC == BotaoC) {
    sum -= 70;
    PORTD &= ~(BotaoC);
  }

  if (sum == 0) {
    PORTD &= 0;
  }
}

int main() {
  PORTB = BotaoA + BotaoB + BotaoC;
  DDRD = M1 + M2 + M3;

  PCICR = (1 << PCIE0);
  PCMSK0 = (1 << PCINT4) + (1 << PCINT3) + (1 << PCINT5);

  sei();

  for(;;) {

  }

  return 0;
}