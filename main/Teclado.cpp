#include <Arduino.h>
#include <Keypad.h>
#include "Dosificador.h"
#include "LcdDisplay.h"
#include "Mascotas.h"

const byte ROWS = 4, COLS = 4;
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte rowPins[ROWS] = { 7, 6, 5, 4 };    // R1 a R4
byte colPins[COLS] = { 3, 2, A1, A0 };  // C1 a C4
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
bool modoConfig = false;

void teclado_init() {}

void teclado_gestionar(int* tiempoDosis, int* gramosDosis, const char* nombreMascotaActual) {
  char key = keypad.getKey();
  static bool editTiempo = false, editGramos = false;
  static int buffer = 0;

  if (!key) {
    return;  // No hay tecla presionada
  }

  Serial.println(key);

  if (key) {
    if (key == 'C') {  // REPORT MASCOTAS
      mascotas_reporte();
      lcd.clear();
    } else if (key == 'D' && modoConfig) {  // RESET
      *tiempoDosis = 15;
      *gramosDosis = 5;
      dosificador_guardar_tiempo(*tiempoDosis);
      dosificador_guardar_gramos(*gramosDosis);
      lcd_mostrar_mensaje("Valores RESET", 0);
      delay(3000);
      lcd_mostrar_config(nombreMascotaActual);
    } else if (key == 'A' && modoConfig){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Nuevo tiempo:"); 
      lcd.setCursor(0,1);
      lcd.print(buffer);
      lcd.print(" Segundos");
      delay(3000);
      buffer = 0; 
      lcd_mostrar_config(nombreMascotaActual);
    } else if (key == 'B' && modoConfig){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Nuevos gramos:"); 
      lcd.setCursor(0,1);
      lcd.print(buffer);
      lcd.print(" Gramos");
      delay(3000); 
      buffer = 0;
      lcd_mostrar_config(nombreMascotaActual);
    } else if (isdigit(key) && modoConfig) {
      buffer = buffer * 10 + (key - '0');
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(buffer);
    } else if (key == '*') {  //Entra a modo configuracion
      modoConfig = !modoConfig;
      if (modoConfig){
        lcd_mostrar_mensaje("Modo Config ON", 0);
        delay(3000);
      } else {
        lcd_mostrar_mensaje("Modo Config OFF", 0);
        delay(3000);
      }; 
      buffer = 0;
      lcd.clear();
    }
  }
}
