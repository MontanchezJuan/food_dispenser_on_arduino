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

  if (id != -1) {
    // Nueva mascota detectada o misma mascota válida
    if (id != mascotaActual) {
      mascotaActual = id;
      lcd_mostrar_nombre(mascota_nombre(id));
      compuerta_abrir();
      delay(2000);
      compuerta_cerrar();
      lcd_mostrar_tiempo_restante(tiempoDosis);

      // Reinicia el temporizador cuando detecta nueva mascota
      lastDoseTime = millis();
      enDosificacion = false;
    }
  } else {
    // No detecta mascota válida, muestra mensaje y no temporiza
    if (mascotaActual != -1) {
      mascotaActual = -1;
      lcd_mostrar_mensaje("Mascota no", 0);
      lcd_mostrar_mensaje("reconocida", 1);
    }
    return; // Termina aquí para esperar hasta detectar mascota válida
  }

  // Gestión del teclado (ajustes)
  teclado_gestionar(&tiempoDosis, &gramosDosis);

  // Si el tiempo pasó y hay mascota válida, dosifica
  if (!enDosificacion && millis() - lastDoseTime >= (unsigned long)tiempoDosis * 1000) {
    enDosificacion = true;
    dosificar(gramosDosis, mascotaActual);
    lastDoseTime = millis();
    enDosificacion = false;
    lcd_mostrar_tiempo_restante(tiempoDosis);
  }

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
  lcd_mostrar_mensaje("Dosis lista!", 1);
  delay(1200);
  lcd_mostrar_tiempo_restante(tiempoDosis);
}
