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

void teclado_gestionar(long id, const char* nombreMascotaActual) {
  char key = keypad.getKey();
  static bool editTiempo = false, editGramos = false;
  static int buffer = 0;

  if (!key) {
    return;  // No hay tecla presionada
  }

  Serial.println(key); //! Comentar en producción

  if (key) {
    if (key == 'C') {  // REPORT MASCOTAS
      mascotas_reporte();
      lcd.clear();
      lcd_mostrar_config(nombreMascotaActual);
    } else if (key == 'D' && modoConfig) {  // RESET
      int tiempo = dosificador_leer_tiempo();
      int gramos = dosificador_leer_gramos();
      set_gramos_por_nombre(nombreMascotaActual, gramos);
      set_tiempo_por_nombre(nombreMascotaActual, tiempo);

      // dosificador_guardar_tiempo(15);
      // dosificador_guardar_gramos(5);
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("Valores RESET"); 
      delay(1000);

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Valores RESET"); 
      lcd.setCursor(0,1);
      lcd.print("Tiempo:");
      lcd.print(tiempo);
      delay(1000);

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Tiempo:");
      lcd.print(tiempo);
      lcd.setCursor(0,1);
      lcd.print("Gramos:");
      lcd.print(gramos);
      delay(1000);

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Gramos:");
      lcd.print(gramos);
      delay(1000);

      lcd_mostrar_config(nombreMascotaActual);
    } else if (key == 'A' && modoConfig){
      if (buffer < 10 || buffer > 30) {
        lcd_mostrar_mensaje("Tiempo invalido", 0);
      } else {
        set_tiempo_por_nombre(nombreMascotaActual, buffer);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Nuevo tiempo:"); 
        lcd.setCursor(0,1);
        lcd.print(buffer);
        lcd.print(" Segundos");
      }
      delay(3000);
      buffer = 0; 
      lcd_mostrar_config(nombreMascotaActual);
    } else if (key == 'B' && modoConfig){
      if (buffer < 1 || buffer > 10) {
        lcd_mostrar_mensaje("Gramos invalido", 0);
      } else {
        set_gramos_por_nombre(nombreMascotaActual, buffer);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Nuevos gramos:"); 
        lcd.setCursor(0,1);
        lcd.print(buffer);
        lcd.print(" Gramos");
      }
      delay(3000); 
      buffer = 0;
      lcd_mostrar_config(nombreMascotaActual);
    } else if (isdigit(key) && modoConfig) {
      buffer = buffer * 10 + (key - '0');
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(buffer);
    } else if (key == '#') {  // Mascota comelona gorda obesa
      int id = mascota_con_mas_gramos_total();
      Mascota* m = get_mascota(id);
      if (m != NULL) {
        const char* nombreMascota = m->nombre;
        int gramos_total = m->gramos_total;
        lcd.clear();
        lcd.setCursor(0,1);
        lcd.print("Mascota mas"); 
        delay(1000);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Mascota mas"); 
        lcd.setCursor(0,1);
        lcd.print("gorda del mes:");
        delay(1000);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("gorda del mes:");
        lcd.setCursor(0,1);
        lcd.print(nombreMascota);
        delay(1000);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(nombreMascota);
        lcd.setCursor(0,1);
        lcd.print("gramos totales:");
        delay(1000);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("gramos totales:");
        lcd.setCursor(0,1);
        lcd.print(gramos_total);
        delay(1000);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(gramos_total);
        delay(1000);
        lcd_mostrar_config(nombreMascotaActual);
      }
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
