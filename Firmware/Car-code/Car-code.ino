#include <SPI.h>
#include <RF24.h>
#include <Servo.h>
#include <stdint.h>

// ==================================================
// NRF24L01
// CE = D9
// CSN = D10
// ==================================================

RF24 radio(9, 10);

const byte direccionRadio[6] = "F1CAR";

// ==================================================
// SERVO
// ==================================================

Servo servoDireccion;

const int SERVO_PIN = 8;

const int SERVO_CENTRO = 80;
const int SERVO_IZQUIERDA = 65;
const int SERVO_DERECHA = 95;

// ==================================================
// L298N
// ==================================================

const int ENA = 5;
const int IN1 = 2;
const int IN2 = 3;

const int ENB = 6;
const int IN3 = 4;
const int IN4 = 7;

// ==================================================
// DATOS
// ==================================================

struct DatosMando {
  int16_t acelerador;
  int16_t direccion;
};

DatosMando datos;

// ==================================================
// SEGURIDAD
// ==================================================

unsigned long ultimaRecepcion = 0;

const unsigned long TIMEOUT_RF = 500;

// ==================================================
// SETUP
// ==================================================

void setup() {

  Serial.begin(115200);

  // Motores
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Servo
  servoDireccion.attach(SERVO_PIN);
  servoDireccion.write(SERVO_CENTRO);

  pararMotores();

  // NRF24
  if (!radio.begin()) {

    Serial.println("ERROR NRF24");

    while (1) {
      pararMotores();
    }
  }

  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(108);

  radio.openReadingPipe(1, direccionRadio);

  radio.startListening();

  datos.acelerador = 0;
  datos.direccion = 0;

  ultimaRecepcion = millis();

  Serial.println("COCHE NRF24 OK");
}

// ==================================================
// LOOP
// ==================================================

void loop() {

  // ==================================================
  // RECIBIR
  // ==================================================

  if (radio.available()) {

    radio.read(
      &datos,
      sizeof(datos)
    );

    ultimaRecepcion = millis();

    // Limitar valores
    datos.acelerador =
      constrain(datos.acelerador, -100, 100);

    datos.direccion =
      constrain(datos.direccion, -100, 100);

    // ==================================================
    // DIRECCION
    // ==================================================

    int angulo = map(
      datos.direccion,
      -100,
      100,
      SERVO_IZQUIERDA,
      SERVO_DERECHA
    );

    angulo = constrain(
      angulo,
      SERVO_IZQUIERDA,
      SERVO_DERECHA
    );

    servoDireccion.write(angulo);

    // ==================================================
    // MOTORES
    // ==================================================

    if (datos.acelerador > 50) {

      adelante();

    } else if (datos.acelerador < -50) {

      atras();

    } else {

      pararMotores();
    }

    // ==================================================
    // SERIAL
    // ==================================================

    Serial.print("Acelerador: ");
    Serial.print(datos.acelerador);

    Serial.print(" | Direccion: ");
    Serial.print(datos.direccion);

    Serial.print(" | Servo: ");
    Serial.println(angulo);
  }

  // ==================================================
  // SEGURIDAD
  // ==================================================

  if (millis() - ultimaRecepcion > TIMEOUT_RF) {

    pararMotores();

    servoDireccion.write(SERVO_CENTRO);
  }
}

// ==================================================
// ADELANTE
// ==================================================

void adelante() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

// ==================================================
// ATRAS
// ==================================================

void atras() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

// ==================================================
// PARAR
// ==================================================

void pararMotores() {

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}