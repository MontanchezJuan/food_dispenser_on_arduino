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
<<<<<<< HEAD
=======
int modoTeclado = 0;  // 0: normal, 1: editar
>>>>>>> 367a7e46720bc1b85def1fbd63a55e9a85968e7e
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
  teclado_gestionar(&tiempoDosis, &gramosDosis, nombreMascotaActual);  // Gestión del teclado

  if (modoConfig) {
    if (id != -1 && id != mascotaActual) {
      mascotaActual = id;
      nombreMascotaActual = mascota_nombre(id);
<<<<<<< HEAD
      lcd_mostrar_nombre(nombreMascotaActual);
      delay(2000);
      dosificar(gramosDosis, mascotaActual);
      lcd_mostrar_tiempo_restante(tiempoDosis - gramosDosis, nombreMascotaActual);
      mascotaActual = -1;
      lcd.clear();
=======
>>>>>>> 367a7e46720bc1b85def1fbd63a55e9a85968e7e

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Configurando a:");
      lcd.setCursor(0, 1);
      lcd.print(nombreMascotaActual);
    } else if (id == -1 && mascotaActual == -1) {
      // Solo mostrar "Esperando gato" si aún no se ha pasado una mascota válida
      lcd.setCursor(0, 0);
      lcd.print("Esperando");
      lcd.setCursor(0, 1);
      lcd.print("Mascota...");
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

