#define inputPin 9

long segTrecho1 = 0, segTrecho2 = 0, segTrecho3 = 0;
long minTrecho1 = 0, minTrecho2 = 0, minTrecho3 = 0;
long tempo = 0, tempo1 = 0, tempo2 = 0, tempo3 = 0;
long millisTrecho1 = 0, millisTrecho2 = 0, millisTrecho3 = 0;
int volta = 0;
int control = 0, amostras = 1200, sinal;
float val = 0;
String separador = ";";

void exibirTempo() {
  Serial.print(minTrecho1);
  Serial.print(separador);
  Serial.print(segTrecho1);
  Serial.print(separador);
  Serial.print(millisTrecho1);
  Serial.print(separador);
  Serial.print(minTrecho2);
  Serial.print(separador);
  Serial.print(segTrecho2);
  Serial.print(separador);
  Serial.print(millisTrecho2);
  Serial.print(separador);
  Serial.print(minTrecho3);
  Serial.print(separador);
  Serial.print(segTrecho3);
  Serial.print(separador);
  Serial.print(millisTrecho3);
  Serial.print(separador);
  Serial.println(volta);
}

void setup()
{

  pinMode(inputPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  val = 0;
  for (int i = 0; i < amostras; i++) {
    sinal = digitalRead(inputPin);
    val = val + sinal;
    delayMicroseconds(1);
  }

  val /= amostras;

  if (val >= 1)
    val = 1;
  else
    val = 0;

  if (val == 1) {
    switch (control) {
      case 0:
        tempo = millis();
        segTrecho1 = 0;
        segTrecho2 = 0;
        segTrecho3 = 0;
        minTrecho1 = 0;
        minTrecho2 = 0;
        minTrecho3 = 0;
        millisTrecho1 = 0;
        millisTrecho2 = 0;
        millisTrecho3 = 0;
        control = 1;
        volta++;
        break;
      case 1:
        tempo1 = millis();
        millisTrecho1 = tempo1 - tempo;
        minTrecho1 = (millisTrecho1 / 60000) % 60;
        segTrecho1 = (millisTrecho1 / 1000) % 60;
        millisTrecho1 = millisTrecho1 - (((minTrecho1 * 60) + segTrecho1) * 1000);
        exibirTempo();
        control = 2;
        break;
      case 2:
        tempo2 = millis();
        millisTrecho2 = tempo2 - tempo1;
        minTrecho2 = (millisTrecho2 / 60000) % 60;
        segTrecho2 = (millisTrecho2 / 1000) % 60;
        millisTrecho2 = millisTrecho2 - ((minTrecho2 * 60 + segTrecho2) * 1000);
        exibirTempo();
        control = 3;
        break;
      case 3:
        tempo3 = millis();
        millisTrecho3 = tempo3 - tempo2;
        minTrecho3 = (millisTrecho3 / 60000) % 60;
        segTrecho3 = (millisTrecho3 / 1000) % 60;
        millisTrecho3 = millisTrecho3 - ((minTrecho3 * 60 + segTrecho3) * 1000);
        exibirTempo();
        control = 0;
        break;
    }
    delay(1000);
  }
}

