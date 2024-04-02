#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "Actuadores.h"

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
BLECharacteristic* pCharacteristic1 = NULL; // Declaración de pCharacteristic1
BLECharacteristic* pCharacteristic2 = NULL; // Declaración de pCharacteristic2
BLECharacteristic* pCharacteristic3 = NULL; // Declaración de pCharacteristic3

bool deviceConnected = false;
bool oldDeviceConnected = false;
uint32_t value = 0;

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID "f3d3857d-c19e-40f9-a5af-7335d7dac9df"
#define CHARACTERISTIC_UUID1 "d63ce40b-2683-4670-9a76-b462488f9139"
#define CHARACTERISTIC_UUID2 "6d391c5f-ab7a-4ba4-bfca-b7a384cd1471"
#define CHARACTERISTIC_UUID3 "697a7857-5624-46fc-bbee-7703cbf9f026"

#define LED1_PIN 2
#define LED2_PIN 4
#define LED3_PIN 16

char ledStatus = 48;
char ledStatus2 = 48;
char ledStatus3 = 48;

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      BLEDevice::startAdvertising();
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};



void setupBluetooth() {
  Serial.begin(115200);

  // Create the BLE Device
  BLEDevice::init("09876");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pCharacteristic1 = pService->createCharacteristic(
                       CHARACTERISTIC_UUID1,
                       BLECharacteristic::PROPERTY_READ   |
                       BLECharacteristic::PROPERTY_WRITE
                     );

  pCharacteristic2 = pService->createCharacteristic(
                       CHARACTERISTIC_UUID2,
                       BLECharacteristic::PROPERTY_READ   |
                       BLECharacteristic::PROPERTY_WRITE
                     );

  pCharacteristic3 = pService->createCharacteristic(
                       CHARACTERISTIC_UUID3,
                       BLECharacteristic::PROPERTY_READ   |
                       BLECharacteristic::PROPERTY_WRITE
                     );
  // https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
  // Create a BLE Descriptor
  //pCharacteristic->addDescriptor(new BLE2902());

  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();
  pinMode (LED1_PIN, OUTPUT); // Set the LED pin as OUTPUT
  pinMode (LED2_PIN, OUTPUT);
  pinMode (LED3_PIN, OUTPUT);

  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED3_PIN, LOW);
}

void loopBluetooth() {
  
  std::string controlValue = pCharacteristic1->getValue();
  std::string controlValue2 = pCharacteristic2->getValue();
  std::string controlValue3 = pCharacteristic3->getValue();

  if (controlValue[0] != ledStatus) {
    Serial.print("Value changed... new value: ");
    Serial.println(controlValue[0]);
    ledStatus = controlValue[0];
    if (ledStatus == 48) {
      digitalWrite(LED1_PIN, LOW); // LED Off
    }
    else if (ledStatus == 49) {
      digitalWrite(LED1_PIN, HIGH); // LED On
    }
  }
  
  if (!controlValue2.empty()) {
    char ledValue2 = controlValue2[0];
    if (ledValue2 == '1') {
      digitalWrite(LED2_PIN, HIGH); // LED Off
    } else if (ledValue2 == '0') {
      digitalWrite(LED2_PIN, LOW); // LED On
    }
  }

  if (!controlValue3.empty()) {
    char ledValue3 = controlValue3[0];
    if (ledValue3 == '1') {
      digitalWrite(LED3_PIN, HIGH); // LED Off
    } else if (ledValue3 == '0') {
      digitalWrite(LED3_PIN, LOW); // LED On
    }
  }

  
}
