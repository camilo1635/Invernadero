#include "Sensores.h"
#include "DHT.h"

//Funcion para tomar el valor de la luz
void readPhoto() {
  luz = int(map(int(analogRead(sensorLuz)), 0, 4095, 0, 100));
}

void readHumedadSuelo(){
  hs = 100 - int(map(int(analogRead(sensorHumSuelo)), 1840, 4095, 0, 100));
}

//Funcion para tomar el valor de la temperatura y humedad
void readTempHum() {
  h = dht.readHumidity();
  t = dht.readTemperature();
}
