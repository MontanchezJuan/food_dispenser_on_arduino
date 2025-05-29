#include <Wire.h>
#include <EEPROM.h>
#include "LcdDisplay.h"
#include "Dosificador.h"
#include "Mascotas.h"
#include "Teclado.h"
#include "Rfid.h"

// Variables globales
const char* nombreMascotaActual = "Desconocida";
int mascotaActual = -1;
int modoTeclado = 0; // 0: normal, 1: editar
int tiempoDosis, gramosDosis;
unsigned long lastDoseTime = 0;

void setup() {
  Serial.begin(9600);

  lcd_init();
  teclado_init();
  dosificador_init();
  mascotas_init();
  rfid_init();

  // Leer parámetros desde EEPROM
  tiempoDosis = dosificador_leer_tiempo();
  gramosDosis = dosificador_leer_gramos();

  lcd_mostrar_bienvenida();  
}

void loop() {
  // Detecta mascota válida
  int id = rfid_leer();

  // Serial.print(id);
  
  // Gestión del teclado (ajustes)
  teclado_gestionar(&tiempoDosis, &gramosDosis);

  if (id != -1) {
    // Nueva mascota detectada o misma mascota válida
    if (id != mascotaActual) {
      mascotaActual = id;
      nombreMascotaActual = mascota_nombre(id);
      lcd_mostrar_nombre(nombreMascotaActual);
      delay(2000);
      lcd_mostrar_tiempo_restante(tiempoDosis,nombreMascotaActual);
      dosificar(gramosDosis, mascotaActual);
      mascotaActual = -1;
      lcd.clear();

      return; // Termina aquí para esperar hasta detectar mascota válida
    }
  } else {
    // No detecta mascota válida, muestra mensaje y no temporiza
    lcd.setCursor(0, 0);
    lcd.print("Esperando");
    lcd.setCursor(0, 1);
    lcd.print("mascota...");
    mascotaActual = -1;
    
    return; // Termina aquí para esperar hasta detectar mascota válida
  }
}
