#include <Arduino.h>
#include "LcdDisplay.h"
#include "Mascotas.h"

Mascota lista[MAX_MASCOTAS] = { 
  {"Max", 0xE116C101, 0},
  {"Luna", 0x4922804A, 0}
};

void mascotas_init() {
  // Puedes inicializar si quieres
}

const char* mascota_nombre(int id) {
  if (id >= 0 && id < MAX_MASCOTAS)
    return lista[id].nombre;
  return "Desconocido";
}

void mascotas_sumar_gramos(int id, int gramos) {
  if (id >= 0 && id < MAX_MASCOTAS)
    lista[id].gramos_total += gramos;
}

void mascotas_reporte() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Reporte alimento");
  lcd.setCursor(0, 1);
  lcd.print("suministrado");
  delay(3000);
  for (int i = 0; i < MAX_MASCOTAS; i++) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(lista[i].nombre);
    lcd.setCursor(0, 1);
    lcd.print("Total: ");
    lcd.print(lista[i].gramos_total);
    lcd.print(" g");
    delay(3000);
  }
}
