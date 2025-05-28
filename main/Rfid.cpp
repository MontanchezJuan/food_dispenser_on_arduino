#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include "Mascotas.h"

#define RST_PIN 9
#define SS_PIN 10

MFRC522 mfrc522(SS_PIN, RST_PIN);

unsigned long ultimo_rfid_detectado = 0;

void rfid_init() {
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.begin(9600);
}

unsigned long uid_to_long(byte *uid) {
  return ((unsigned long)uid[0] << 24) | ((unsigned long)uid[1] << 16) | ((unsigned long)uid[2] << 8) | ((unsigned long)uid[3]);
}


unsigned long rfid_getUltimo() {
  return ultimo_rfid_detectado;
}

int rfid_leer() {
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial())
    return -1;

  Serial.print("RFID Detectado: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) Serial.print("0");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  if (mfrc522.uid.size != 4) {
    ultimo_rfid_detectado = 0;
    return -1;
  }

  unsigned long rfid_id = uid_to_long(mfrc522.uid.uidByte);
  ultimo_rfid_detectado = rfid_id;

  for (int i = 0; i < 2; i++) {
    if (rfid_id == lista[i].rfid) {
      return i;
    }
  }
  return -1;
}
