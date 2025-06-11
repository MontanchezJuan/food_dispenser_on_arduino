#include <Arduino.h>
#include <MFRC522.h>
#include <SPI.h>
#include "LcdDisplay.h"
#include "Mascotas.h"
#include "Teclado.h"

#define RST_PIN 9
#define SS_PIN 10

MFRC522 mfrc522(SS_PIN, RST_PIN);

void rfid_init() {
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.begin(9600);
}

unsigned long uid_to_long(byte *uid) {
  return ((unsigned long)uid[0] << 24) | ((unsigned long)uid[1] << 16) | ((unsigned long)uid[2] << 8) | ((unsigned long)uid[3]);
}

int rfid_leer() {
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial())
    return -1;

  // Serial.print("RFID Detectado: ");
  // for (byte i = 0; i < mfrc522.uid.size; i++) {
  //   if (mfrc522.uid.uidByte[i] < 0x10) Serial.print("0");
  //   Serial.print(mfrc522.uid.uidByte[i], HEX);
  //   Serial.print(" ");
  // }
  // Serial.println();

  if (mfrc522.uid.size != 4) {
    Serial.println("UID no tiene 4 bytes, ignorado");
    return -1;
  }

  unsigned long rfid_id = uid_to_long(mfrc522.uid.uidByte);

  for (int i = 0; i < MAX_MASCOTAS; i++) {
    if (rfid_id == lista[i].rfid) {
      Serial.print("Mascota reconocida: ");
      Serial.println(lista[i].nombre);
      return i;
    }
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mascota no");
  lcd.setCursor(0, 1);
  lcd.print("reconocida");
  delay(2000);
  lcd.clear();
  return -1;
}
