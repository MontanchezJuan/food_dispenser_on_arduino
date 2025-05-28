#include <Arduino.h>
#include <Keypad.h>
#include "Dosificador.h"
#include "LcdDisplay.h"

const byte ROWS = 4, COLS = 4;
char keys_num[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

char keys_alpha[ROWS][COLS] = {
  {'A','B','C','D'},
  {'E','F','G','H'},
  {'I','J','K','L'},
  {'*','M','#','N'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 9, 10};

Keypad keypad_num = Keypad(makeKeymap(keys_num), rowPins, colPins, ROWS, COLS);
Keypad keypad_alpha = Keypad(makeKeymap(keys_alpha), rowPins, colPins, ROWS, COLS);

void teclado_init() {}

// Devuelve la tecla presionada según el modo
char teclado_getKey(bool modo_alfabetico) {
  if (modo_alfabetico)
    return keypad_alpha.getKey();
  else
    return keypad_num.getKey();
}

void teclado_gestionar(int* tiempoDosis, int* gramosDosis) {
  char key = keypad_num.getKey();
  static bool editTiempo = false, editGramos = false;
  static int buffer = 0;

  if (key) {
    if (key == 'A') { // Cambiar tiempo
      editTiempo = true;
      buffer = 0;
      lcd_mostrar_mensaje("Nuevo tiempo:", 0);
    }
    else if (key == 'B') { // Cambiar gramos
      editGramos = true;
      buffer = 0;
      lcd_mostrar_mensaje("Nuevos gramos:", 0);
    }
    else if (key == 'C') { // RESET
      *tiempoDosis = 15;
      *gramosDosis = 5;
      dosificador_guardar_tiempo(*tiempoDosis);
      dosificador_guardar_gramos(*gramosDosis);
      lcd_mostrar_mensaje("Valores RESET", 0);
      delay(1000);
      lcd_mostrar_tiempo_restante(*tiempoDosis);
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
