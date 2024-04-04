#include "Actuadores.h"
#include "Sensores.h"
#include <ESP32Servo.h>

Servo servo;
int pinServo = 16;

int pos = 0;

void actuadorSetup() {
  Serial.begin(115200);

  //dispositivos actuadores
  pinMode(ventiladorPin, OUTPUT);
  pinMode(bombaAguaPin, OUTPUT);
  pinMode(ledAmarilloPin, OUTPUT);

  //digitalWrite(ledAmarilloPin, LOW);
  
  //Inicializamos la posicion del servo
  servo.attach(pinServo, 500, 2500);
}

//Funcion de operacion de la bomba de agua
void FunBomba() {
  if (hs < valorHumSueloMin) {
    digitalWrite(bombaAguaPin, HIGH);
    delay(2000);
    digitalWrite(bombaAguaPin, LOW);
  } else {
    digitalWrite(bombaAguaPin, LOW);
  }
}

//Funcion de operacion del ventilador
void FunVentilador() {
  if (t > valorTempMax || hs > valorHumSueloMax) {
    digitalWrite(ventiladorPin, HIGH);
    ServosCerrar();
  } else {
    digitalWrite(ventiladorPin, LOW);
    ServosAbrir();
  }
}

void FunLedAmarillo() {
  if (luz > valorLuzMax) {
    digitalWrite(ledAmarilloPin, HIGH);
  } else {
    digitalWrite(ledAmarilloPin, LOW);
  }
}

//Funcion de los servos
void ServosAbrir() {
  for (pos = 0; pos <= 90; pos += 1) {
    servo.write(pos);
    delay(15);
  }
  
}

// esta funcion cierra las ventanas
void ServosCerrar() {
  for (pos = 90; pos >= 0; pos -= 1) {
    servo.write(pos);
    delay(15);
  }
}
