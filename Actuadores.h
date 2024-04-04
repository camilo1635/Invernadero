#ifndef Actuadores_h
#define Actuadores_h

//Definimos los pines para el ventilador, la bomba de agua y ledAmarillo
const int ventiladorPin = 19;
const int bombaAguaPin = 18;
const int ledAmarilloPin = 17;

//Definimos variables para el control de los actuadores
const int valorTempMax = 25;
const int valorHumSueloMin = 170;
const int valorHumSueloMax = 190;
const int valorLuzMax = 30;

//Funciones de los actuadores
void FunBomba(void);
void FunVentilador(void);
void FunLedAmarillo(void);
void ServosAbrir(void);
void ServosCerrar(void);
void actuadorSetup(void);

#endif
