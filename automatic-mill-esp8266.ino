/*
 *  This file is part of Automatic Mill Project
 *  Copyright (c) 2018 Francisco de Souza Junior (chico.net.br).
 *  
 *
 *  automatic-mill-esp8266 is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  automatic-mill-esp8266 is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with automatic-mill-esp8266.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * 
 */

/*Wifi*/
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
/*create a password.h file and put a #define inside it with your password. for example:
 * #define PASSWORD "fuba"
 */
#include "password.h"


/*Button*/
#include <Bounce2.h>

/*Mill*/
#include "MillManager.hpp"
#include "MillConfiguration.hpp"
#include "RESTServer.hpp"


/*Button*/
#define MOTOR_PIN D0
#define BUTTON_PIN D1

Bounce buttonDebouncer;

/*Mill*/
MillConfiguration millConfiguration;
MillManager millManager(millConfiguration, MOTOR_PIN);

/* REST Server */
RESTServer restServer(millConfiguration, millManager, 80);

void setup() {  
  //Setup button
  pinMode(BUTTON_PIN, INPUT);

  //Configure button debouncer
  buttonDebouncer.attach(BUTTON_PIN);
  buttonDebouncer.interval(5);

  // setup wifi
  WiFi.softAP("Automatic Mill", PASSWORD);
  MDNS.begin("mill");


  //setup rest server

  restServer.begin();
}



void loop() {
  restServer.handleClient();
  
  buttonDebouncer.update();
    
  if(buttonDebouncer.rose()) {
    millManager.toogle();
  } //easy peasy
  
  delay(30);

}
