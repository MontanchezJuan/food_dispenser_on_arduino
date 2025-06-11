#include <Wire.h>
#include <EEPROM.h>
#include "LcdDisplay.h"
#include "Dosificador.h"
#include "Mascotas.h"
#include "Teclado.h"
#include "Rfid.h"

// Variables globales
const char* nombreMascotaActual = "Desconocida";
int tiempoDosis, gramosDosis;
int mascotaActual = -1;

void setup() {
  Serial.begin(9600);

  lcd_init();
  teclado_init();
  dosificador_init();
  mascotas_init();
  rfid_init();

  lcd_mostrar_bienvenida();
  dosificar_initial();
}

void loop() {
  long id = rfid_leer();
  teclado_gestionar(id, nombreMascotaActual);  // Gestión del teclado
  dosificar();

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
      // Solo mostrar "Esperando Mascota" si aún no se ha pasado una mascota válida
      lcd.setCursor(0, 0);
      lcd.print("Esperando      *"); // *: para diferenciar el modo esperando config del normal
      lcd.setCursor(0, 1);
      lcd.print("mascota...      ");
    }
    return;  // Se mantiene en modo configuración
  }

  // --- MODO NORMAL ---
  if (id != -1 && id != mascotaActual) {
    mascotaActual = id;
    Mascota* m = get_mascota(id);
    if (m != NULL) {
      nombreMascotaActual = m->nombre;
      gramosDosis = m->gramos_dosis;
      tiempoDosis = m->tiempo_espera;
      bool hay_comida = m->hay_comida;
      if (hay_comida == true) {
        long loopID = id;
        while (loopID == id)
        {
          lcd_mostrar_comiendo_mascota(nombreMascotaActual);
          delay(2000);
          loopID = rfid_leer();
        }
        
        set_hay_comida(id, false);
        set_siguiente_dosis_en(id, tiempoDosis);
        set_gramos_faltantes(id, gramosDosis);
        mascotas_sumar_gramos(id);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Bye");
        lcd.setCursor(0, 1);
        lcd.print(nombreMascotaActual);
        delay(1000);
      } else {
        int siguiente_dosis_en = lista[id].siguiente_dosis_en;
        if (siguiente_dosis_en != 0)
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(nombreMascotaActual);
          lcd.setCursor(0, 1);
          lcd.print("aun faltan: ");
          lcd.print(siguiente_dosis_en);
          delay(1000);
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(nombreMascotaActual);
        lcd.setCursor(0, 1);
        lcd.print("espera un poco");
        delay(1000);
      }
    }
    mascotaActual = -1;
    return;
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Esperando       ");
    lcd.setCursor(0, 1);
    lcd.print("mascota...      ");
    delay(1000);
    mascotaActual = -1;
    return;
  }
}

