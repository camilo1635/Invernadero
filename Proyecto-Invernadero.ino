#include "AsyncTaskLib.h"
#include "Actuadores.h"
#include "Sensores.h"
#include "Internet.h"

//Tareas asincronas
void readTempHum(void);
AsyncTask Task1(2300, true, readTempHum);
void readPhoto(void);
AsyncTask Task2(1000, true, readPhoto);
void FunBomba(void);
AsyncTask Task3(3500, true, FunBomba);
void FunVentilador(void);
AsyncTask Task4(2000, true, FunVentilador);
void readHumedadSuelo(void);
AsyncTask Task5(3000, true, readHumedadSuelo);
void FunLedAmarillo(void);
AsyncTask Task6(1500, true, FunLedAmarillo);

void setup()
{
  internet();
  actuadorSetup();
  //setupBluetooth();
  Task1.Start();
  Task2.Start();
  Task3.Start();
  Task4.Start();
  Task5.Start();
  Task6.Start();
}

void loop()
{

  Task1.Update();
  Task2.Update();
  Task3.Update();
  Task4.Update();
  Task5.Update();
  Task6.Update();
  thingSpeak();
  //loopBluetooth();

}
