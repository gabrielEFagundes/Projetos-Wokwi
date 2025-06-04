#include <Servo.h> // Inclui a biblioteca Servo para controlar servos
 
Servo meuServo; // Cria um objeto Servo para controlar o servo motor
int pos; // Declara uma variável para controlar a posição do servo motor 
 
void setup() {
    meuServo.attach(6); // Associa o servo motor ao pino digital 6 do Arduino
    meuServo.write(0); // Define a posição inicial do servo motor para 0 graus
}
 
void loop() {
    // Movimento do servo de 0 a 90 graus
    for (pos = 0; pos < 180; pos++) {
        meuServo.write(pos); // Define a posição atual do servo
        delay(15); // Aguarda 15 milissegundos antes de mover para a próxima posição
    }
    delay(1000); // Aguarda 1 segundo antes de iniciar o próximo movimento
 
    // Movimento do servo de 90 a 0 graus
    for (pos = 180; pos >= 0; pos--) {
        meuServo.write(pos); // Define a posição atual do servo
        delay(15); // Aguarda 15 milissegundos antes de mover para a próxima posição
    }
    delay(1000); // Aguarda 1 segundo antes de iniciar o próximo ciclo
}