#ifndef Internet_h
#define Internet_h

#include <WiFi.h>
#include "WebServer.h"
#include "DHT.h"

void internet();
void loopServerWeb();
void thingSpeak();

#endif
