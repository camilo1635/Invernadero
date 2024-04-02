#include "Sensores.h"
#include "DHT.h"

//Funcion para tomar el valor de la luz
void readPhoto() {
  int luz = analogRead(sensorPin);
  Serial.println("hello read Photo: ");
  Serial.println(luz);
}

//Funcion para tomar el valor de la temperatura y humedad
void readTempHum() {
  Serial.print(millis());
  h = dht.readHumidity();
  t = dht.readTemperature();
  
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println("°C");
  Serial.print("Humedad: ");
  Serial.print(h);
}
