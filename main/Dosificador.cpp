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

void dosificar_initial() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dosificacion");
  lcd.setCursor(0, 1);
  lcd.print("inicial");
  delay(2000);

  for (int i = 0; i < MAX_MASCOTAS; i++) {
    if (lista[i].nombre[0] == '\0') continue;

    int gramos = lista[i].gramos_dosis;

    for (int g = 1; g <= gramos; g++) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Dosis: ");
      lcd.print(lista[i].nombre);
      lcd.setCursor(0, 1);
      lcd.print("Gramo ");
      lcd.print(g);
      delay(150);
      dosificador_parpadear_led();
    }
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Fin de");
  lcd.setCursor(0, 1);
  lcd.print("dosificacion");
  delay(2000);
  lcd.clear();
}

void dosificar() {
  for (int i = 0; i < MAX_MASCOTAS; i++) {
    if (lista[i].nombre[0] == '\0') continue;
    if (lista[i].hay_comida == true) continue;
    if (lista[i].siguiente_dosis_en != 0)
    {
      lista[i].siguiente_dosis_en = lista[i].siguiente_dosis_en - 1;
    } else if (lista[i].siguiente_dosis_en == 0 && lista[i].gramos_faltantes != 0)
    {
      lista[i].gramos_faltantes = lista[i].gramos_faltantes - 1;
      dosificador_parpadear_led();
    } else if (lista[i].siguiente_dosis_en == 0 && lista[i].gramos_faltantes == 0)
    {
      lista[i].hay_comida = true;
    }
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
  return tiempo;
}

// void dosificador_guardar_tiempo(int tiempo) {
//   EEPROM.write(EEPROM_TIEMPO, tiempo);
// }

int dosificador_leer_gramos() {
  int gramos = EEPROM.read(EEPROM_GRAMOS);
  return gramos;
}

// void dosificador_guardar_gramos(int gramos) {
//   EEPROM.write(EEPROM_GRAMOS, gramos);
// }
