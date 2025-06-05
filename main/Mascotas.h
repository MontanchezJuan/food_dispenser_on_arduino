#ifndef MASCOTAS_H
#define MASCOTAS_H

#define MAX_MASCOTAS 4

typedef struct {
  char nombre[12];
  unsigned long rfid;
  int gramos_total;
  int tiempo_espera;
  int gramos_dosis;
} Mascota;

extern Mascota lista[MAX_MASCOTAS];

void mascotas_init();
const char* mascota_nombre(int id);
void mascotas_sumar_gramos(int id, int gramos);
void mascotas_reporte();
void set_gramos_por_nombre(const char* nombre, int gramos);
void set_tiempo_por_nombre(const char* nombre, int tiempo);
int get_tiempo(int id);
int get_gramos(int id);

#endif
