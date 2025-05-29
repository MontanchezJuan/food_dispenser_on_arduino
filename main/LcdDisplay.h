#ifndef LCDDISPLAY_H
#define LCDDISPLAY_H

#include <LiquidCrystal_I2C.h>
extern LiquidCrystal_I2C lcd;

void lcd_init();
void lcd_mostrar_bienvenida();
void lcd_mostrar_dosificando(int gramos);
void lcd_mostrar_gramos(int gramos);
void lcd_mostrar_mensaje(const char* mensaje, int linea);
void lcd_mostrar_nombre(const char* nombre);
void lcd_mostrar_tiempo_restante(int tiempo, char* nombre);

#endif
