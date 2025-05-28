#ifndef TECLADO_H
#define TECLADO_H

void teclado_init();
void teclado_gestionar(int* tiempoDosis, int* gramosDosis);
char teclado_getKey(bool modo_alfabetico);

#endif
