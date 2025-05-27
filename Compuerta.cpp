#include <Servo.h>

Servo servo;
#define SERVO_PIN 13

void compuerta_cerrar() {
  servo.write(0);
}
void compuerta_init() {
  servo.attach(SERVO_PIN);
  compuerta_cerrar();
}
void compuerta_abrir() {
  servo.write(90);
}

