#define SWITCH (1 << PD3)
#define TURN_ON_BUTTON (1 << PC0)
#define TURN_OFF_BUTTON (1 << PC1)
#define LOW_SENSOR (1 << PD4)
#define HIGH_SENSOR (1 << PD5)
#define BOMB (1 << PB0)

int main() {
  DDRB = BOMB;
  DDRC = 0;
  DDRD = 0;
  
  for (;;) {

  }
}

// port C
ISR(PCINT1_vect) {

} 

// port D
ISR(PCINT2_vect) {
  
} 