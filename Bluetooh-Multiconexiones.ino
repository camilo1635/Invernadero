#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

//Bluetooh
BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic1 = NULL;
BLECharacteristic* pCharacteristic2 = NULL; // Declaración de pCharacteristic1

bool deviceConnected = false;
bool oldDeviceConnected = false;
uint32_t value = 0;

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID "f3d3857d-c19e-40f9-a5af-7335d7dac9df"
#define CHARACTERISTIC_UUID1 "d63ce40b-2683-4670-9a76-b462488f9139"
#define CHARACTERISTIC_UUID2 "6d391c5f-ab7a-4ba4-bfca-b7a384cd1471"

const int ventiladorPin = 19;
const int bombaAguaPin = 18;
  
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      BLEDevice::startAdvertising();
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};


void setup(){
  // Create the BLE Device
  BLEDevice::init("Invernadero");

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
  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();
  pinMode(ventiladorPin, OUTPUT);
  pinMode(bombaAguaPin, OUTPUT);

  digitalWrite(ventiladorPin, LOW);
  digitalWrite(bombaAguaPin, LOW);
}

void loop(){
  
  std::string controlValue1 = pCharacteristic1->getValue();
  std::string controlValue2 = pCharacteristic2->getValue();

  if (!controlValue1.empty()) {
    char ventiladorValor = controlValue1[0];
    if (ventiladorValor == '1') {
      digitalWrite(ventiladorPin, HIGH); // LED Off
    } else if (ventiladorValor == '0') {
      digitalWrite(ventiladorPin, LOW); // LED On
    }
  }

  if (!controlValue2.empty()) {
    char bombaAguaValor = controlValue2[0];
    if (bombaAguaValor == '1') {
      digitalWrite(bombaAguaPin, HIGH); // LED Off
    } else if (bombaAguaValor == '0') {
      digitalWrite(bombaAguaPin, LOW); // LED On
    }
  }
  
}
