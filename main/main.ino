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
int modoTeclado = 0;  // 0: normal, 1: editar
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
  int id = rfid_leer();  // Leer RFID
  teclado_gestionar(&tiempoDosis, &gramosDosis);  // Gestión del teclado

  if (modoConfig) {
    if (id != -1 && id != mascotaActual) {
      mascotaActual = id;
      nombreMascotaActual = mascota_nombre(id);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Configurando a:");
      lcd.setCursor(0, 1);
      lcd.print(nombreMascotaActual);
    } else if (id == -1 && mascotaActual == -1) {
      // Solo mostrar "Esperando gato" si aún no se ha pasado una mascota válida
      lcd.setCursor(0, 0);
      lcd.print("Modo Config");
      lcd.setCursor(0, 1);
      lcd.print("Esperando gato...");
    }
    return;  // Se mantiene en modo configuración
  }

  // --- MODO NORMAL ---
  if (id != -1 && id != mascotaActual) {
    mascotaActual = id;
    nombreMascotaActual = mascota_nombre(id);

    lcd_mostrar_nombre(nombreMascotaActual);
    delay(2000);
    lcd_mostrar_tiempo_restante(tiempoDosis, nombreMascotaActual);
    dosificar(gramosDosis, mascotaActual);
    mascotaActual = -1;
    lcd.clear();
    return;
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Esperando       ");
    lcd.setCursor(0, 1);
    lcd.print("mascota...      ");
    mascotaActual = -1;
    return;
  }
}

