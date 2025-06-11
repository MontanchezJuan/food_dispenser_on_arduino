#ifndef LCDDISPLAY_H
#define LCDDISPLAY_H

#include <LiquidCrystal_I2C.h>
extern LiquidCrystal_I2C lcd;

void lcd_init();
void lcd_mostrar_bienvenida();
void lcd_mostrar_comiendo_mascota(const char* nombre);
void lcd_mostrar_config(const char* nombreMascota);
void lcd_mostrar_mensaje(const char* mensaje, int linea);

#endif
