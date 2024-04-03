#include "Sensores.h"
#include "DHT.h"

//Funcion para tomar el valor de la luz
void readPhoto() {
  int luz = analogRead(sensorLuz);
}

void readHumedadSuelo(){
  int hs = analogRead(sensorHumSuelo);
  Serial.println(hs);
}

//Funcion para tomar el valor de la temperatura y humedad
void readTempHum() {
  h = dht.readHumidity();
  t = dht.readTemperature();
}
