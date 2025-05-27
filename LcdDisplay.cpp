#include "LcdDisplay.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

void lcd_init() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void lcd_mostrar_mensaje(const char* mensaje, int linea) {
  lcd.clear();
  lcd.setCursor(0, linea);
  lcd.print(mensaje);
}

void lcd_mostrar_tiempo_restante(int tiempo) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Siguiente dosis:");
  lcd.setCursor(0, 1);
  lcd.print("en ");
  lcd.print(tiempo);
  lcd.print(" seg");
}

void lcd_mostrar_nombre(const char* nombre) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mascota:");
  lcd.setCursor(0, 1);
  lcd.print(nombre);
}

void lcd_mostrar_dosificando(int gramos) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dosificando...");
  lcd.setCursor(0, 1);
  lcd.print(gramos);
  lcd.print("g");
}

void lcd_mostrar_gramos(int gramos) {
  lcd.setCursor(0, 1);
  lcd.print("Faltan: ");
  lcd.print(gramos);
  lcd.print("g ");
}
