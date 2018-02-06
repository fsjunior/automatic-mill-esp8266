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
 
#include <Bounce2.h>
#include "MillManager.hpp"
#include "MillConfiguration.hpp"


#define MOTOR_PIN D0
#define BUTTON_PIN D1

static bool millRunning = false;

int milltime = 0;



Bounce buttonDebouncer = Bounce();

MillConfiguration millConfiguration;
MillManager millManager(millConfiguration, MOTOR_PIN);

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON_PIN, INPUT);

  buttonDebouncer.attach(BUTTON_PIN);
  buttonDebouncer.interval(5);
}



void loop() {
  buttonDebouncer.update();
  
  if(buttonDebouncer.rose()) {
    millManager.toogle();
  }
  
  delay(30);

}
