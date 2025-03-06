/* ========================================================================
   Programa que realiza a tradução de uma mensagem digitada pelo usuário em
   código morse
   
   Autor: Pedro Couto
   Data: Março de 2025
   Atualizado em: --

========================================================================== */

/* ========================================================================== */
/* Constantes */

#define LED_PIN 13

char* letters[] =
{
  ".-",   // A
  "-...", // B
  "-.-.", // C
  "-..",  // D
  ".",    // E
  "..-.", // F
  "--.",  // G
  "....", // H
  "..",   // I
  ".---", // J
  "-.-",  // K
  ".-..", // L
  "--",   // M
  "-.",   // N
  "---",  // O
  ".--.", // P
  "--.-", // Q
  ".-.",  // R
  "...",  // S
  "-",    // T
  "..-",  // U
  "...-", // V
  ".--",  // W
  "-..-", // X
  "-.--", // Y
  "--.."  // Z
};

char* numbers[] = 
{
  "-----", // 0
  "·----", // 1
  "··---", // 2
  "···--", // 3
  "····-", // 4
  "·····", // 5
  "-····", // 6
  "--···", // 7
  "---··", // 8
  "----·", // 9
};

int dotDuration = 200;

/* ========================================================================== */
/* Protótipos */

void checkSerial();
void blinkSequence(char* seq);
void blinkSequence(char dotOrDash);

/* ========================================================================== */
/* Função Principal */

void setup() 
{
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Digite mensagem: \n");
} /* end setup */

void loop() 
{
  if(Serial.available())
  {
    checkSerial();
  }
} /* end loop */

/* ========================================================================== */
/* Funções secundárias */

void checkSerial()
{
  char ch;
  ch = Serial.read();

  if(ch >= 'a' && ch <= 'z')
  {
    blinkSequence(letters[ch - 'a']);
  }
  else if(ch >= 'A' && ch <= 'Z')
  {
    blinkSequence(letters[ch - 'A']);
  }
  else if(ch >= '0' && ch <= '9')
  {
    blinkSequence(numbers[ch - 'A']);
  }
  else if(ch == ' ')
  {
    delay(dotDuration * 4);
  }
}

void blinkSequence(char* seq)
{
  int i = 0;
  while(seq[i] != NULL)
  {
    blinkDotOrDash(seq[i]);
    i++;
  }

  delay(dotDuration * 3);
}

void blinkDotOrDash(char dotOrDash)
{
  digitalWrite(LED_PIN, 1);
  if(dotOrDash == '.')
  {
    delay(dotDuration);
  }
  else
  {
    delay(dotDuration * 3);
  }
  digitalWrite(LED_PIN, 0);
  delay(dotDuration);
}

/* ========================================================================== */
/* Final do Programa */
