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
 
#include "MillManager.hpp"
#include "Arduino.h"

MillManager::MillManager(MillConfiguration& millConfiguration, int pin): millConfiguration(millConfiguration), pin(pin)
{
  pinMode(pin, OUTPUT);
  digitalWrite(D0, HIGH);
}


void deactivateMill(MillManager *millManager)
{
  digitalWrite(millManager->pin, HIGH); //HIGH is deactivated  
}

void MillManager::activate()
{
  digitalWrite(pin, LOW); //low is activated

  if(millConfiguration.getMillTime() != 0) {
    stopTicker.once(millConfiguration.getMillTime(), deactivateMill, this);  
  }
}


void MillManager::deactivate()
{
  stopTicker.detach();
  deactivateMill(this);
}

void MillManager::toogle()
{
  if(!isRunning()) {
    activate();    
  } else {
    deactivate();
  }
}


bool MillManager::isRunning()
{
  return digitalRead(pin) == LOW;
}

