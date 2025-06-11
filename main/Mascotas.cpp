#include <Arduino.h>
#include "LcdDisplay.h"
#include "Mascotas.h"

Mascota lista[MAX_MASCOTAS] = { 
  {"Luna", 0x4922804A, 0, 15, 3, true, 0, 0},
  {"Max", 0xE116C101, 0, 10, 5, true, 0, 0}
};

void mascotas_init() {
  // Puedes inicializar si quieres
}

const char* mascota_nombre(int id) {
  if (id >= 0 && id < MAX_MASCOTAS)
    return lista[id].nombre;
  return "Desconocido";
}

void mascotas_sumar_gramos(int id) {
  if (id >= 0 && id < MAX_MASCOTAS)
    lista[id].gramos_total += lista[id].gramos_dosis;
}

void mascotas_reporte() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Reporte alimento");
  lcd.setCursor(0, 1);
  lcd.print("suministrado");
  delay(3000);

  for (int i = 0; i < MAX_MASCOTAS; i++) {
    // Si la mascota no tiene nombre, salimos del bucle
    if (lista[i].nombre[0] == '\0') break;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(lista[i].nombre);
    lcd.setCursor(0, 1);
    lcd.print("Total: ");
    lcd.print(lista[i].gramos_total);
    lcd.print(" g");
    delay(3000);
  }

  lcd.clear();
  lcd.print("Fin reporte");
  delay(2000);
  lcd.clear();
}

void set_tiempo_por_nombre(const char* nombre, int tiempo) {
  for (int i = 0; i < MAX_MASCOTAS; i++) {
    if (strcmp(lista[i].nombre, nombre) == 0) {
      lista[i].tiempo_espera = tiempo;
      return;
    }
  }
}

void set_gramos_por_nombre(const char* nombre, int gramos) {
  for (int i = 0; i < MAX_MASCOTAS; i++) {
    if (strcmp(lista[i].nombre, nombre) == 0) {
      lista[i].gramos_dosis = gramos;
      return;
    }
  }
}

void set_hay_comida(int id, bool estado) {
  if (id >= 0 && id < MAX_MASCOTAS) {
    lista[id].hay_comida = estado;
  }
}

Mascota* get_mascota(int id) {
  if (id >= 0 && id < MAX_MASCOTAS)
    return &lista[id];
  return NULL;
}

int mascota_con_mas_gramos_total() {
  int max_gramos = -1;
  int indice_max = -1;

  for (int i = 0; i < MAX_MASCOTAS; i++) {
    if (lista[i].gramos_total > max_gramos) {
      max_gramos = lista[i].gramos_total;
      indice_max = i;
    }
  }

  return indice_max;
}

void set_siguiente_dosis_en(int id, int valor) {
  if (id >= 0 && id < MAX_MASCOTAS) {
    lista[id].siguiente_dosis_en = valor;
  }
}

void set_gramos_faltantes(int id, int gramos) {
  if (id >= 0 && id < MAX_MASCOTAS) {
    lista[id].gramos_faltantes = gramos;
  }
}
