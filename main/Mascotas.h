#ifndef MASCOTAS_H
#define MASCOTAS_H

#define MAX_MASCOTAS 4

typedef struct {
  char nombre[12];
  unsigned long rfid;
  int gramos_total;
} Mascota;

extern Mascota lista[MAX_MASCOTAS];

void mascotas_init();
const char* mascota_nombre(int id);
void mascotas_sumar_gramos(int id, int gramos);
void mascotas_reporte();

// Nueva función para guardar en EEPROM desde índice
void mascotas_guardar(int i);

// Nueva función para guardar una mascota con nombre ingresado dinámicamente
void mascotas_guardar_con_nombre(unsigned long rfid);

#endif
