#include <Arduino.h>
#include "Mascotas.h"

Mascota lista[MAX_MASCOTAS] = {
  {"Max", 0xE116C101, 0},
  {"Luna", 0x0B8FFC03, 0}
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
  Serial.println("Reporte alimento suministrado:");
  for (int i = 0; i < MAX_MASCOTAS; i++) {
    Serial.print(lista[i].nombre);
    Serial.print(": ");
    Serial.print(lista[i].gramos_total);
    Serial.println(" gramos");
  }
}
