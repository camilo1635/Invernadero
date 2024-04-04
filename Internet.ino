#include <WiFi.h>  
#include "ThingSpeak.h"
#include "Sensores.h"
#include "Actuadores.h"
#include "DHT.h"

//Credenciales de red
const char* ssid = "Chupaloo";
const char* password = "1234567890.";

//ThingSpeak
#define SECRET_CH_ID 2461267    // replace 0000000 with your channel number
#define SECRET_WRITE_APIKEY "AIYY13ISLE6D8VQJ"

int keyIndex = 0;
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

// Initialize our values
int RSSI = 0;
int temperatura = random(0, 100);
int humedad = random(0, 100);
int light = random(0, 100);
int humedadSuelo = random(0, 100);
String myStatus = "";

void internet() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(ventiladorPin, OUTPUT);
  pinMode(bombaAguaPin, OUTPUT);

  // Set outputs to LOW
  digitalWrite(ventiladorPin, LOW);
  digitalWrite(bombaAguaPin, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //dht.begin();

  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }

  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);

}


void thingSpeak() {

  long rssi = WiFi.RSSI();
  /*
    float humedad = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float temperatura = dht.readTemperature();
    luz = analogRead(sensorLuz);
    float humedadSuelo = analogRead(sensorHumSuelo);
  */

  // set the fields with the values
  ThingSpeak.setField(1, rssi);
  ThingSpeak.setField(2, t);
  ThingSpeak.setField(3, h);
  ThingSpeak.setField(4, luz);
  ThingSpeak.setField(5, hs);

  // set the status
  ThingSpeak.setStatus(myStatus);

  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  delay(8000);
}
