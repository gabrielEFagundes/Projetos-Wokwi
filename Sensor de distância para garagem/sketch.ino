// Pinos do arduino utilizados
int pinTrigger = 5;     // pino usado para disparar os pulsos do sensor
int pinEcho = 6;        // pino usado para ler a saida do sensor
int PinLEDvermelho = 2; // pino usado pelo LED vermelho
int PinLEDamarelo = 3;  // pino usado pelo LED amarelo
int PinLEDverde = 4;    // pino usado pelo LED verde
int PinBuzzer = A0;     // pino usado pelo buzzer

// Variaveis e constantes para controle de distancia
const int atraso = 200;       // tempo de espera do loop 
const int MaxContador = 5000/atraso;   // número de iterações para considerar parado (5s)
const float tolerancia = 1.0;   // tolerancia para detecção de movimento    
const float velocidadeSom_mps = 340;        // em metros por segundo
const float velocidadeSom_mpus = 0.000340;  // em metros por microsegundo
float Distancia = 0;          // Distancia medida
float DistanciaAnterior = 0;  // Distancia anterior medida (detecção de movimento)
int contador = 0;             // contador de tempo para detecçaõ de movimento

// Valores limites das faixas de sinalização
const int LimiteVerde = 29;
const int LimiteAmarelo = 17;
const int LimiteVermelho = 10;
const int LimiteBuzzer = 8;

// Comandos de sinalização
const int Verde = 1;
const int Amarelo = 2;
const int Vermelho = 3;
const int Buzzer = 4;

// Inicialização
void setup() {
  pinMode(pinTrigger, OUTPUT);      // configura pino Trigger como saída
  digitalWrite(pinTrigger, LOW);    // pino trigger - nível baixo
  pinMode(pinEcho, INPUT);          // configura pino ECHO como entrada
  pinMode(PinLEDvermelho, OUTPUT);  // configura pino LED vermelho como saída
  pinMode(PinLEDamarelo, OUTPUT);   // configura pino LED amarelo como saída
  pinMode(PinLEDverde, OUTPUT);     // configura pino LED verde como saída
  pinMode(PinBuzzer, OUTPUT);       // configura pino Buzzer como saída
  Serial.begin(9600);               // inicializa monitor serial 9600 Bps (debug)
  delay(100);                       // atraso de 100 milisegundos
  Distancia = medeDistancia();
  DistanciaAnterior = Distancia;
  desligaSinais();
}
// Loop principal
void loop() {
  Distancia = medeDistancia();
  if (estaParado()) { desligaSinais(); }
  else if (Distancia <= LimiteBuzzer) { Sinaliza(Buzzer);  } 
  else if (Distancia <= LimiteVermelho) { Sinaliza(Vermelho); } 
  else if (Distancia <= LimiteAmarelo) { Sinaliza(Amarelo); } 
  else if (Distancia <= LimiteVerde) {Sinaliza(Verde); } 
  else { desligaSinais();}
  
  Serial.print("Distancia em centimentros: ");  // mostra no monitor serial
  Serial.print(Distancia);                      // mostra o calculo de distancia em metros
  Serial.println();
  delay(atraso);                                // tempo de atraso 
}

float medeDistancia(){
  float tempoEcho = 0;
  disparaPulsoUltrassonico();
  tempoEcho = pulseIn(pinEcho, HIGH);
  return calculaDistancia(tempoEcho) * 100;
}

void disparaPulsoUltrassonico(){
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);
}

float calculaDistancia(float tempo_us){
  return ((tempo_us * velocidadeSom_mpus) / 2);
}

// Sinaliza a faixa apropriada
void Sinaliza(int faixa) {
  desligaSinais();
  if (faixa == Verde) {
    digitalWrite(PinLEDverde, HIGH);
  } else if (faixa == Amarelo) {
    digitalWrite(PinLEDamarelo, HIGH);
  } else if (faixa == Vermelho) {
    digitalWrite(PinLEDvermelho, HIGH);
  } else if (faixa == Buzzer) {
    digitalWrite(PinLEDvermelho, HIGH);
    tone(PinBuzzer, 500);
  }
}
// Desliga a sinalização
void desligaSinais() {
  digitalWrite(PinLEDverde, LOW);
  digitalWrite(PinLEDamarelo, LOW);
  digitalWrite(PinLEDvermelho, LOW);
  noTone(PinBuzzer);
}
// verifica se está parado
byte estaParado() {
  byte parado;
  if (sq(Distancia - DistanciaAnterior) <= tolerancia) {
    if (contador >= MaxContador) {
      Serial.println("Sem movimento. Desligando sinais...");
      parado = 1;
    } else {
      contador++;
      parado = 0;
    }
  } else {
    contador = 0;
    parado = 0;
  }
  DistanciaAnterior = Distancia;
  return parado;
}