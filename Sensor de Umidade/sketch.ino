#include <DHT.h>

// Defina o pino onde o sensor está conectado
#define DHTPIN 2

// Defina o tipo de sensor (DHT22)
#define DHTTYPE DHT22

// Inicialize o sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.println("Sensor DHT22 iniciado");
}

void loop() {
  // Aguarde um pouco entre as leituras
  delay(2000);

  // Leia a umidade e a temperatura
  float hum = dht.readHumidity();
  float temp = dht.readTemperature(); // Celsius

  // Verifique se a leitura falhou
  if (isnan(hum) || isnan(temp)) {
    Serial.println("Falha ao ler do sensor DHT22!");
    return;
  }

  // Exiba os dados no monitor serial
  Serial.print("Umidade: ");
  Serial.print(hum);
  Serial.print(" %\t");

  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.println(" °C");
}