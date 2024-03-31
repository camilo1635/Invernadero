#include "AsyncTaskLib.h"
#include "Actuadores.h"
#include "Sensores.h"
#include "Internet.h"

//Tareas
void readTempHum(void);
AsyncTask Task1(2300, true, readTempHum);
void readPhoto(void);
AsyncTask Task2(1000, true, readPhoto);
void FunBomba(void);
AsyncTask Task3(2000, true, FunBomba);
void FunVentilador(void);
AsyncTask Task4(3000, true, FunVentilador);

void setup()
{
  internet();
  Task1.Start();
  Task2.Start();
  Task3.Start();
  Task4.Start();

}

void loop()
{
  
  Task1.Update();
  Task2.Update();
  Task3.Update();
  Task4.Update();
  loopServerWeb();
  thingSpeak();

}
