#include <EEPROM.h>
#include <Arduino.h>
#include "Mascotas.h"
#include "Teclado.h"
#include "LcdDisplay.h"

#define EEPROM_START 0  // Dirección inicial para mascotas

Mascota lista[MAX_MASCOTAS];

void mascotas_init() {
  for (int i = 0; i < MAX_MASCOTAS; i++) {
    int addr = EEPROM_START + i * sizeof(Mascota);

    // Leer nombre
    for (int j = 0; j < sizeof(lista[i].nombre); j++) {
      lista[i].nombre[j] = EEPROM.read(addr + j);
    }

    // Leer UID (4 bytes)
    unsigned long uid = 0;
    for (int b = 0; b < 4; b++) {
      uid |= ((unsigned long)EEPROM.read(addr + sizeof(lista[i].nombre) + b)) << (8 * b);
    }
    lista[i].rfid = uid;

    // Leer gramos_total (4 bytes)
    int gramos = 0;
    for (int b = 0; b < 4; b++) {
      gramos |= EEPROM.read(addr + sizeof(lista[i].nombre) + 4 + b) << (8 * b);
    }
    lista[i].gramos_total = gramos;

    // Validar nombre, si está vacío, inicializa por defecto
    if (lista[i].nombre[0] == 0xFF || lista[i].nombre[0] == 0) {
      // Nombre vacío, cargar valores por defecto o dejar vacío
      strncpy(lista[i].nombre, "Vacío", sizeof(lista[i].nombre));
      lista[i].rfid = 0;
      lista[i].gramos_total = 0;
    }
  }

  Mascota lista[MAX_MASCOTAS] = {
    {"Max", 0xE116C101, 0},
    {"Luna", 0x0B8FFC03, 0}
  };
}

void mascotas_guardar(int i) {
  if (i < 0 || i >= MAX_MASCOTAS) return;

  int addr = EEPROM_START + i * sizeof(Mascota);

  // Guardar nombre
  for (int j = 0; j < sizeof(lista[i].nombre); j++) {
    EEPROM.update(addr + j, lista[i].nombre[j]);
  }

  // Guardar UID (4 bytes)
  for (int b = 0; b < 4; b++) {
    EEPROM.update(addr + sizeof(lista[i].nombre) + b, (lista[i].rfid >> (8 * b)) & 0xFF);
  }

  // Guardar gramos_total (4 bytes)
  for (int b = 0; b < 4; b++) {
    EEPROM.update(addr + sizeof(lista[i].nombre) + 4 + b, (lista[i].gramos_total >> (8 * b)) & 0xFF);
  }
}

// Guardar mascota con nombre ingresado dinámicamente
void mascotas_guardar_con_nombre(unsigned long rfid) {
  char nombre[12] = {0};
  int idx = 0;
  bool nombre_aceptado = false;

  lcd_mostrar_mensaje("Ingrese nombre:", 0);
  lcd_mostrar_mensaje("", 1);

  // Cambiar entre teclado numérico (false) y alfabético (true)
  bool modo_alfabetico = true;

  while (!nombre_aceptado) {
    char key = teclado_getKey(modo_alfabetico); // Función que lee tecla según modo

    if (key) {
      if (key == '#') { // Tecla aceptar nombre
        nombre_aceptado = true;
      }
      else if (key == '*') { // Borrar último carácter
        if (idx > 0) {
          idx--;
          nombre[idx] = '\0';
        }
      }
      else if (key == 'D') { // Cambiar modo teclado
        modo_alfabetico = !modo_alfabetico;
      }
      else {
        if (idx < sizeof(nombre) - 1) {
          nombre[idx++] = key;
          nombre[idx] = '\0';
        }
      }

      // Mostrar nombre actualizado en LCD
      lcd_mostrar_mensaje(nombre, 1);
    }
  }

  // Buscar posición para guardar la mascota (primer lugar vacío o con mismo rfid)
  int i = -1;
  for (int j = 0; j < MAX_MASCOTAS; j++) {
    if (lista[j].rfid == rfid || lista[j].rfid == 0) {
      i = j;
      break;
    }
  }

  if (i == -1) {
    lcd_mostrar_mensaje("No hay espacio", 0);
    delay(2000);
    return;
  }

  // Guardar nombre, rfid y reset gramos_total
  strncpy(lista[i].nombre, nombre, sizeof(lista[i].nombre));
  lista[i].rfid = rfid;
  lista[i].gramos_total = 0;

  // Guardar en EEPROM
  mascotas_guardar(i);

  lcd_mostrar_mensaje("Mascota guardada", 0);
  delay(2000);
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
