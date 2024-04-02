#include <WiFi.h>
#include "WebServer.h"
#include "ThingSpeak.h"
#include "Sensores.h"
#include "DHT.h"

const char* ssid = "TP-LINK_DDAE";
const char* password = "24890717";

//ThingSpeak
#define SECRET_CH_ID 2461267    // replace 0000000 with your channel number
#define SECRET_WRITE_APIKEY "AIYY13ISLE6D8VQJ"

int keyIndex = 0; 
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

// Initialize our values
int RSSI = 0;
int temperatura = random(0,100);
int humedad = random(0,100);
int light = random(0,100);
String myStatus = "";


// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output12State = "off";
String output14State = "off";

// Assign output variables to GPIO pins
const int output12 = 12;
const int output14 = 14;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void internet() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(ventiladorPin, OUTPUT);
  pinMode(bombaAguaPin, OUTPUT);
  
  // Set outputs to LOW
  digitalWrite(ventiladorPin, LOW);
  digitalWrite(bombaAguaPin, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  
  dht.begin();

  Serial.begin(115200);  //Initialize serial
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);
  
}


void thingSpeak(){
  
  long rssi = WiFi.RSSI();
  
  float humedad = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float temperatura = dht.readTemperature();
  float light = analogRead(sensorPin);
  
  // set the fields with the values
  ThingSpeak.setField(1, rssi);
  ThingSpeak.setField(2, temperatura);
  ThingSpeak.setField(3, humedad);
  ThingSpeak.setField(4, light);
  
  // set the status
  ThingSpeak.setStatus(myStatus);
  
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);


  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  
  delay(20000);
}
void loopServerWeb() {
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");

            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");

            client.println("<h2>Humedad: " + String(h) + "</h2>");;
            client.println("<h2>Temperatura: " + String(t) + "</h2>");;
            client.println("<h2>Luz: " + String(luz) + "</h2>");;

            // Display current state, and ON/OFF buttons for GPIO 26
            client.println("<p>GPIO 12 - State " + output12State + "</p>");
            // If the output26State is off, it displays the ON button
            if (output12State == "off") {
              client.println("<p><a href=\"/12/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/12/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for GPIO 27
            client.println("<p>GPIO 14 - State " + output14State + "</p>");
            // If the output27State is off, it displays the ON button
            if (output14State == "off") {
              client.println("<p><a href=\"/14/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/14/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
