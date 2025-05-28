#include <Arduino.h>
#include <Keypad.h>
#include "Dosificador.h"
#include "LcdDisplay.h"

const byte ROWS = 4, COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {7, 6, 5, 4}; // R1 a R4
byte colPins[COLS] = {3, 2, A1, A0}; // C1 a C4
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void teclado_init() {}

void teclado_gestionar(int* tiempoDosis, int* gramosDosis) {
  char key = keypad.getKey();
  static bool editTiempo = false, editGramos = false;
  static int buffer = 0;

  Serial.println(key);

  if (key) {
    if (key == 'A') { // Cambiar tiempo
      editTiempo = true;
      buffer = 0;
      lcd_mostrar_mensaje("Nuevo tiempo:", 0);
      delay(2000);
      lcd.clear();
    }
    else if (key == 'B') { // Cambiar gramos
      editGramos = true;
      buffer = 0;
      lcd_mostrar_mensaje("Nuevos gramos:", 0);
      delay(2000);
      lcd.clear();
    }
    else if (key == 'C') { // RESET
      *tiempoDosis = 15;
      *gramosDosis = 5;
      dosificador_guardar_tiempo(*tiempoDosis);
      dosificador_guardar_gramos(*gramosDosis);
      lcd_mostrar_mensaje("Valores RESET", 0);
      delay(2000);
      lcd.clear();
    }
    else if (isdigit(key)) {
      buffer = buffer * 10 + (key - '0');
      if (editTiempo && buffer >= 10 && buffer <= 30) {
        *tiempoDosis = buffer;
        dosificador_guardar_tiempo(buffer);
        lcd_mostrar_mensaje("Tiempo guardado!", 0);
        delay(800);
        lcd_mostrar_tiempo_restante(*tiempoDosis);
        editTiempo = false; buffer = 0;
      }
      else if (editGramos && buffer >= 1 && buffer <= 10) {
        *gramosDosis = buffer;
        dosificador_guardar_gramos(buffer);
        lcd_mostrar_mensaje("Gramos guardado!", 0);
        delay(800);
        lcd_mostrar_tiempo_restante(*tiempoDosis);
        editGramos = false; buffer = 0;
      }
    }
  }
}
