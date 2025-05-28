#include <Arduino.h>
#include <EEPROM.h>
#include "Dosificador.h"

const int LED_PIN = 8;
const int EEPROM_TIEMPO = 0;
const int EEPROM_GRAMOS = 2;

void dosificador_init() {
  pinMode(LED_PIN, OUTPUT);
}

void dosificador_parpadear_led() {
  digitalWrite(LED_PIN, HIGH);
  delay(250);
  digitalWrite(LED_PIN, LOW);
  delay(250);
}

int dosificador_leer_tiempo() {
  int tiempo = EEPROM.read(EEPROM_TIEMPO);
  if (tiempo < 10 || tiempo > 30) tiempo = 3;
  return tiempo;
}

void dosificador_guardar_tiempo(int tiempo) {
  EEPROM.write(EEPROM_TIEMPO, tiempo);
}

int dosificador_leer_gramos() {
  int gramos = EEPROM.read(EEPROM_GRAMOS);
  if (gramos < 1 || gramos > 10) gramos = 5;
  return gramos;
}

void dosificador_guardar_gramos(int gramos) {
  EEPROM.write(EEPROM_GRAMOS, gramos);
}
