#ifndef Actuadores_h
#define Actuadores_h

//Definimos los pines para el ventilador y la bomba de agua
const int ventiladorPin = 19;
const int bombaAguaPin = 18;

//Definimos variables para el control de los actuadores
const int valorTemp = 27;
const int valorHumMin = 65;
const int valorLuz = 100;

//Funciones de los actuadores
void FunBomba(void);
void FunVentilador(void);
void ServosAbrir(void);
void ServosCerrar(void);

#endif
