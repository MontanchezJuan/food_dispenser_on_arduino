#ifndef DOSIFICADOR_H
#define DOSIFICADOR_H

void dosificar(int gramos, int id);
void dosificador_init();
void dosificador_parpadear_led();
int dosificador_leer_tiempo();
int dosificador_leer_gramos();
void dosificador_guardar_tiempo(int tiempo);
void dosificador_guardar_gramos(int gramos);

#endif
