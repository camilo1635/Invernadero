#include "Actuadores.h"
#include "Sensores.h"
#include <ESP32Servo.h>


Servo servo;
int pinServo = 34;

int pos = 0;
int pos2 = 0;

void actuadorSetup() {
  Serial.begin(115200);

  //dispositivos actuadore
  pinMode(ventiladorPin, OUTPUT);
  pinMode(bombaAguaPin, OUTPUT);


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
