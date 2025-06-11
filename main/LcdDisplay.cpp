#include <Arduino.h>
#include "LcdDisplay.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

void lcd_init() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void lcd_mostrar_bienvenida() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Bienvenido!");
  delay(1000);
  lcd.clear();
}

void lcd_mostrar_mensaje(const char* mensaje, int linea) {
  lcd.clear();
  lcd.setCursor(0, linea);
  lcd.print(mensaje);
}

void lcd_mostrar_comiendo_mascota(const char* nombre) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(nombre);
  lcd.setCursor(0, 1);
  lcd.print("comiendo...");
}

void lcd_mostrar_config(const char* nombreMascota) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Configurando a:");
  lcd.setCursor(0, 1);
  lcd.print(nombreMascota);
}