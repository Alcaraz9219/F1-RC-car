#include <SPI.h>
#include <RF24.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <stdint.h>

// ==================================================
// NRF24L01
// CE = D9
// CSN = D10
// ==================================================

RF24 radio(9, 10);

const byte direccionRadio[6] = "F1CAR";

// ==================================================
// LCD
// ==================================================

LiquidCrystal_I2C lcd(0x27, 16, 2);

// ==================================================
// CONTROLES
// ==================================================

const int JOYSTICK_X = A0;

const int BOTON_ACELERADOR = 2;
const int BOTON_FRENO = 3;

// ==================================================
// DATOS
// ==================================================

struct DatosMando {
  int16_t acelerador;
  int16_t direccion;
};

DatosMando datos;

// ==================================================
// JOYSTICK
// ==================================================

const int CENTRO_X = 512;
const int ZONA_MUERTA = 80;

// ==================================================
// SETUP
// ==================================================

void setup() {

  Serial.begin(115200);

  pinMode(JOYSTICK_X, INPUT);

  pinMode(BOTON_ACELERADOR, INPUT_PULLUP);
  pinMode(BOTON_FRENO, INPUT_PULLUP);

  // LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("F1 RC CAR");

  lcd.setCursor(0, 1);
  lcd.print("INICIANDO...");

  delay(1000);

  // NRF24
  if (!radio.begin()) {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ERROR NRF24");

    Serial.println("ERROR NRF24");

    while (1);
  }

  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(108);

  radio.openWritingPipe(direccionRadio);

  radio.stopListening();

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("NRF24 OK");

  lcd.setCursor(0, 1);
  lcd.print("MANDO LISTO");

  delay(1500);
}

// ==================================================
// LOOP
// ==================================================

void loop() {

  // ==================================================
  // DIRECCION
  // ==================================================

  int x = analogRead(JOYSTICK_X);

  int diferenciaX = x - CENTRO_X;

  if (abs(diferenciaX) < ZONA_MUERTA) {

    datos.direccion = 0;

  } else {

    datos.direccion = map(
      diferenciaX,
      -512,
      511,
      -100,
      100
    );

    datos.direccion = constrain(
      datos.direccion,
      -100,
      100
    );
  }

  // ==================================================
  // ACELERADOR / FRENO
  // ==================================================

  bool aceleradorPulsado =
    digitalRead(BOTON_ACELERADOR) == LOW;

  bool frenoPulsado =
    digitalRead(BOTON_FRENO) == LOW;

  if (aceleradorPulsado && !frenoPulsado) {

    datos.acelerador = 100;

  } else if (frenoPulsado && !aceleradorPulsado) {

    datos.acelerador = -100;

  } else {

    datos.acelerador = 0;
  }

  // ==================================================
  // TRANSMITIR
  // ==================================================

  radio.write(
    &datos,
    sizeof(datos)
  );

  // ==================================================
  // LCD
  // ==================================================

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("DIR:");

  if (datos.direccion < -10) {

    lcd.print("IZQ");

  } else if (datos.direccion > 10) {

    lcd.print("DER");

  } else {

    lcd.print("RECT");
  }

  lcd.setCursor(0, 1);

  if (datos.acelerador == 100) {

    lcd.print("ADELANTE");

  } else if (datos.acelerador == -100) {

    lcd.print("ATRAS");

  } else {

    lcd.print("PARADO");
  }

  // ==================================================
  // SERIAL
  // ==================================================

  Serial.print("Direccion: ");
  Serial.print(datos.direccion);

  Serial.print(" | Acelerador: ");
  Serial.println(datos.acelerador);

  delay(50);
}