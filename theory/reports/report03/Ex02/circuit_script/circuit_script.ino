#define BI_MANUAL_1 (1 << PC0)
#define BI_MANUAL_2 (1 << PC1)

#define MOTOR (1 << PD6)

int calcDutCyclePercentage(int percentage) {
  return (int)((255 * percentage) / 100);
}

int counter = 0;
int currentCrib = 0;
bool isBiManualModeActive = false;
bool isDrillAlreadyInCrib = false;

const short int FOURTY_PERCENTAGE = calcDutCyclePercentage(40);
const short int EIGHTY_PERCENTAGE = calcDutCyclePercentage(80);
const short int THIRTY_FIVE_PERCENTAGE = calcDutCyclePercentage(35);
const short int TEN_PERCENTAGE = calcDutCyclePercentage(10);
const short int SEVENTY_FIVE_PERCENTAGE = calcDutCyclePercentage(75);

const int timeFromCribZeroToOne = 4000;    // 4 seconds
const int timeFromCribOneToTwo = 3000;     // 3 seconds
const int timeFromCribTwoToThree = 2000;   // 2 seconds
const int timeFromCribThreeToFour = 6000;  // 6 seconds
const int timeFromCribFourToFive = 5000;   // 5 seconds
const int timeOfDrillTurnOn = 4000;        // 4 segundos

int currentOCR0A = 0;

void turnOnDrill() {
  Serial.println("Entrou turnOn");
  if (!isDrillAlreadyInCrib && currentCrib >= 1) {
    counter = 0;
    isDrillAlreadyInCrib = true;

    Serial.print("Current crib entrou: ");
    Serial.println(currentCrib);
  }

  switch (currentCrib) {
    case 1:
      OCR0A = FOURTY_PERCENTAGE;
      break;
    case 2:
      OCR0A = EIGHTY_PERCENTAGE;
      break;
    case 3:
      OCR0A = THIRTY_FIVE_PERCENTAGE;
      break;
    case 4:
      OCR0A = TEN_PERCENTAGE;
      break;
    case 5:
      OCR0A = SEVENTY_FIVE_PERCENTAGE;
      break;
  }

  // PORTD |= MOTOR;
}

void turnOffDrill() {
  if (isDrillAlreadyInCrib && counter == timeOfDrillTurnOn) {
    OCR0A = 0;
    currentCrib++;
    isDrillAlreadyInCrib = false;

    Serial.print("Moving to crib: ");
    Serial.println(currentCrib);
  }
}


int main() {
  Serial.begin(115200);
  DDRD |= MOTOR;
  // PORTD &= ~MOTOR;

  // configure timer 0 works as comparator
  TCCR2A = (1 << COM2A1) + (1 << WGM21) + (1 << WGM20);  // pwm mode
  TCCR2B = (1 << CS22) + (1 << CS20);                    // configure prescaler 1024
  // OCR0A = 0; // 250 counts of 4us -> 1ms delay
  TIMSK2 = (1 << OCIE2A);  // enable interrupt on comparator A of timer 0

  // configure timer 2 works as comparator
  TCCR0A = (1 << WGM01) + (0 << WGM00);  // comparator mode
  TCCR0B = (1 << CS01) + (1 << CS00);    // configure prescaler timer 2
  /*
    PreScaler: 64
    Frequency: 250KHz
    Period of each count: 4us
  */

  OCR0A = 249;             // 250 counts of 4us -> 1ms delay
  TIMSK0 = (1 << OCIE0A);  // enable interrupt on comparator A of timer 0

  PCICR = (1 << PCIE1);
  PCMSK1 |= BI_MANUAL_1 + BI_MANUAL_2;

  sei();
  for (;;) {
    // OCR0A = currentOCR0A;

    // if ((counter % 500) == 0) {

    // Serial.print("Current OCR0A: ");
    // Serial.println(OCR0A);
    // }
  }
}

ISR(PCINT1_vect) {
  bool isBiManual1Pressed = (PINC & BI_MANUAL_1) == BI_MANUAL_1;
  bool isBiManual2Pressed = (PINC & BI_MANUAL_2) == BI_MANUAL_2;
  isBiManualModeActive = isBiManual1Pressed & isBiManual2Pressed;

  if (isBiManualModeActive) {
    if (currentCrib == 0) {
      currentCrib = 1;
      counter = 0;
      Serial.println("Entrou no inicio");
    }

    Serial.print("Current crib: ");
    Serial.println(currentCrib);
    Serial.print("Counter: ");
    Serial.println(counter);
  } else {
    // OCR0A = 0;
    currentCrib = 0;
  }
}

// interrupt happened each 1ms
ISR(TIMER0_COMPA_vect) {
  counter += 1;
  bool isCribOne = currentCrib == 1 && (counter == timeFromCribZeroToOne);
  bool isCribTwo = currentCrib == 2 && (counter == timeFromCribOneToTwo || isDrillAlreadyInCrib);
  bool isCribThree = currentCrib == 3 && (counter == timeFromCribTwoToThree || isDrillAlreadyInCrib);
  bool isCribFour = currentCrib == 4 && (counter == timeFromCribThreeToFour || isDrillAlreadyInCrib);
  bool isCribFive = currentCrib == 5 && (counter == timeFromCribFourToFive || isDrillAlreadyInCrib);

  // Serial.print("Current crib: ");
  // Serial.println(currentCrib);
  // Serial.print("Counter: ");
  // Serial.println(counter);

  // currentOCR0A = TEN_PERCENTAGE;
  // Serial.println(counter);
  if ((counter % 4000) == 0) {
    Serial.print("Counter ,: ");
    Serial.println(counter);
    // PORTD |= MOTOR;
  }

  if (isCribOne) {
    Serial.println("Entrou aqui");
    currentOCR0A = FOURTY_PERCENTAGE;
    turnOnDrill();
  }
  /* else if (isCribTwo) {
    turnOnDrill();
    turnOffDrill();
  } else if (isCribThree) {
    turnOnDrill();
    turnOffDrill();
  } else if (isCribFour) {
    turnOnDrill();
    turnOffDrill();
  } else if (isCribFive) {
    turnOnDrill();
    turnOffDrill();
  } else if (currentCrib > 5) {
    Serial.println("Process finished");
    currentCrib = 0;
  }*/
}
