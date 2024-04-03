#ifndef Sensores_h
#define Sensores_h
  
#include "DHT.h"
#define DHTPIN 4 //Definimos el pin para el DHT
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

//Definimos el pin para la fotoresistencia
const int sensorLuz = 35;
const int sensorHumSuelo = 34;

//Variables a comparar
float h = 0;
float hs = 0;
float t = 0;
int luz = 0;

void readPhoto(void);
void readTempHum(void);

#endif
