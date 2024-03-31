#include "Actuadores.h"
#include "Sensores.h"
#include <ESP32Servo.h>


Servo servo;
int pinServo = 34;
int pinServo = 35;

int pos1 = 0;
int pos2 = 0;

void actuadorSetup() {
  Serial.begin(115200);

  //dispositivos actuadore
  pinMode(bombaPin, OUTPUT);
  pinMode(tiraLedPin, OUTPUT);
  pinMode(ventiladorPin, OUTPUT);

  //alarmas visuales y sonicas
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);

  //Inicializamos la posicion del servo
  servo.attach(pinServo, 500, 2500);
}

//Funcion de operacion de la bomba de agua
void FunBomba() {
  if (h < 30) {
    digitalWrite(bombaAguaPin, HIGH);
  } else {
    digitalWrite(bombaAguaPin, LOW);
  }
}

//Funcion de operacion del ventilador
void FunVentilador() {
  if (t > 30) {
    digitalWrite(ventiladorPin, HIGH);
  } else {
    digitalWrite(ventiladorPin, LOW);
  }
}
