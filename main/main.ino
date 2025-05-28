#include <Wire.h>
#include <EEPROM.h>
#include "LcdDisplay.h"
#include "Dosificador.h"
#include "Mascotas.h"
#include "Teclado.h"
#include "Rfid.h"
#include "Compuerta.h"

// Variables globales
unsigned long lastDoseTime = 0;
int tiempoDosis, gramosDosis;
bool enDosificacion = false;
int mascotaActual = -1;

void setup() {
  Serial.begin(9600);

  lcd_init();
  teclado_init();
  dosificador_init();
  mascotas_init();
  rfid_init();
  compuerta_init();

  // Leer parámetros desde EEPROM
  tiempoDosis = dosificador_leer_tiempo();
  gramosDosis = dosificador_leer_gramos();

  lcd_mostrar_mensaje("Bienvenido!", 0);
  delay(2000);
  lcd_mostrar_mensaje("Esperando RFID", 0);
  lcd_mostrar_mensaje("mascota...", 1);
}

void loop() {
  // Detecta mascota válida
  int id = rfid_leer();

  Serial.print(id);


  if (id != -1) {
    // Nueva mascota detectada o misma mascota válida
    if (id != mascotaActual) {
      mascotaActual = id;
      lcd_mostrar_nombre(mascota_nombre(id));
      compuerta_abrir();
      delay(2000);
      compuerta_cerrar();
      lcd_mostrar_tiempo_restante(tiempoDosis);

      enDosificacion = true;
      dosificar(gramosDosis, mascotaActual);
      enDosificacion = false;
      mascotaActual = -1;
      lcd.clear();

      return; // Termina aquí para esperar hasta detectar mascota válida
    }
  } else {
    // No detecta mascota válida, muestra mensaje y no temporiza
    mascotaActual = -1;
    lcd.setCursor(0, 0);
    lcd.print("Mascota no");
    lcd.setCursor(0, 1);
    lcd.print("reconocida");
    
    return; // Termina aquí para esperar hasta detectar mascota válida
  }

  Serial.print("llego"); //! no llega aquí

  // Gestión del teclado (ajustes)
  teclado_gestionar(&tiempoDosis, &gramosDosis);

  // Reporte por serial
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'R' || c == 'r') {
      mascotas_reporte();
    }
  }
}

// Función para dosificar alimento con LED y actualizar registros
void dosificar(int gramos, int id) {
  lcd_mostrar_dosificando(gramos);
  for (int i = gramos; i > 0; i--) {
    lcd_mostrar_gramos(i);
    dosificador_parpadear_led();
    mascotas_sumar_gramos(id, 1);
    delay(700);
  }
}
