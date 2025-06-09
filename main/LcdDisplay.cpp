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
  delay(2000);
  lcd.clear();
}

void lcd_mostrar_dosificando(int gramos) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dosificando");
  lcd.setCursor(0, 1);
  lcd.print(gramos);
  lcd.print("g");
}

void lcd_mostrar_gramos(int gramos) {
  lcd.setCursor(0, 1);
  lcd.print("faltan: ");
  lcd.print(gramos);
  lcd.print("g");
}

void lcd_mostrar_mensaje(const char* mensaje, int linea) {
  lcd.clear();
  lcd.setCursor(0, linea);
  lcd.print(mensaje);
}

void lcd_mostrar_nombre(const char* nombre) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mascota:");
  lcd.setCursor(0, 1);
  lcd.print(nombre);
}

void lcd_mostrar_tiempo_restante(int tiempo, char* nombre) {
  for (int t = tiempo; t > 0; t--) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dosis: ");
    lcd.print(nombre);
    lcd.setCursor(0, 1);
    lcd.print("en ");
    lcd.print(t);
    lcd.print(" seg");
    delay(1000);
  }
  lcd.clear();
}

void lcd_mostrar_config(const char* nombreMascota) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Configurando a:");
  lcd.setCursor(0, 1);
  lcd.print(nombreMascota);
}