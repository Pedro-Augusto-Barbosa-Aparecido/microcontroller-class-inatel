#define LED (1 << PD7)
#define LED_V (1 << PD6)

unsigned int cont = 0;
unsigned short int cont1 = 0;

int main() {
  // Configurando o LED como saída
  DDRD = LED + LED_V;
  // Configurando temporizador - Modo Comparador
  TCCR0A = (1 << WGM01);  //Configuração do modo de funcionamento para comparador
  // Configurando o Pre-scaler
  TCCR0B = (1 << CS02);  //Pre-scaler de 8 (frequencia de 2MHz - periodo de 500ns em cada contagem)
  // Configurando o TOP
  OCR0A = 249;  //200 contagens de 500ns, o que gera interrupt a cada 100μs[micro]
  // Configurando opção de estouro
  TIMSK0 = (1 << OCIE0A);  //Gerar interrupt no estouro do comparador OCR0A
  // Habilitando as interrupções
  sei();
  // Super Loop vazio
  while (1) {}

  return 0;
}
// o q acontece a cada 100μs ???
ISR(TIMER0_COMPA_vect) {
  cont++;

  if (cont1 >= 60) {
    PORTD |= LED_V;
  }

  if (cont > 275) {
    cont1++;
    cont = 0;
    PORTD &= 0;

    if (cont1 > 60) {
      cont1 = 0;
    }
  }

  // Quando passar 1000ms
  if (cont >= 250 && cont < 275) {
    PORTD |= LED;
  }
}