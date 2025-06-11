#ifndef MASCOTAS_H
#define MASCOTAS_H

#define MAX_MASCOTAS 4

typedef struct {
  char nombre[12];
  unsigned long rfid;
  int gramos_total;
  int tiempo_espera;
  int gramos_dosis;
  bool hay_comida;
  int siguiente_dosis_en;
  int gramos_faltantes;
} Mascota;

extern Mascota lista[MAX_MASCOTAS];

void mascotas_init();
const char* mascota_nombre(int id);
void mascotas_sumar_gramos(int id);
void set_tiempo_por_nombre(const char* nombre, int tiempo);
void set_gramos_por_nombre(const char* nombre, int gramos);
void mascotas_reporte();
void set_hay_comida(int id, bool estado);
Mascota* get_mascota(int id);
int mascota_con_mas_gramos_total();
void set_siguiente_dosis_en(int id, int valor);
void set_gramos_faltantes(int id, int gramos);

#endif
