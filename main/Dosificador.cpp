#include <Arduino.h>
#include <EEPROM.h>
#include "Dosificador.h"
#include "LcdDisplay.h"
#include "Mascotas.h"

const int LED_PIN = 8;
const int EEPROM_TIEMPO = 0;
const int EEPROM_GRAMOS = 2;

void dosificador_init() {
  pinMode(LED_PIN, OUTPUT);
}

void dosificar(int gramos, int id) {
  lcd_mostrar_dosificando(gramos);
  for (int i = gramos; i > 0; i--) {
    lcd_mostrar_gramos(i);
    dosificador_parpadear_led();
    mascotas_sumar_gramos(id, 1);
    delay(700);
  }
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

// Eprom para guardar tiempo de espera para cada dosis
void dosificador_guardar_tiempo_dosis(int tiempo) {
  EEPROM.write(EEPROM_TIEMPO, tiempo);
}

void dosificador_guardar_gramos(int gramos) {
  EEPROM.write(EEPROM_GRAMOS, gramos);
}
