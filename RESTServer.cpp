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
 
#include "RESTServer.hpp"
#include <ArduinoJson.h>

#define DATA_ARRAY_SIZE 64


void RESTServer::replySuccess()
{
  StaticJsonBuffer<DATA_ARRAY_SIZE> actualBuffer;
  JsonObject& root = actualBuffer.createObject();
  root["Result"] = true;

  String output;
  root.printTo(output);
  server.send ( 200, "application/json", output);  
}


void RESTServer::replyFailure()
{
  StaticJsonBuffer<DATA_ARRAY_SIZE> actualBuffer;
  JsonObject& root = actualBuffer.createObject();
  root["Result"] = false;

  String output;
  root.printTo(output);
  server.send ( 500, "application/json", output);  
}



void RESTServer::handlePing()
{
  replySuccess();
}

void RESTServer::handleToogle()
{
  millManager.toogle();
  replySuccess();
}

void RESTServer::handleGetStatus()
{
   StaticJsonBuffer<DATA_ARRAY_SIZE> actualBuffer;
  JsonObject& root = actualBuffer.createObject();
  root["Status"] = millManager.isRunning();

  String output;
  root.printTo(output);
  server.send ( 200, "application/json", output);   
}

void RESTServer::handlePostMillTime()
{
  if(server.hasArg("plain")) {
    StaticJsonBuffer<DATA_ARRAY_SIZE> newBuffer;
    JsonObject& root = newBuffer.parseObject(server.arg("plain"));

    if (root.success()) {
      millConfiguration.setMillTime(root["Mill Time"]);

      handleGetMillTime();   
      
      return;
    }
  } 

  //otherwise
  replyFailure();
}

void RESTServer::handleGetMillTime()
{
  StaticJsonBuffer<DATA_ARRAY_SIZE> actualBuffer;
  JsonObject& root = actualBuffer.createObject();
  root["Mill Time"] = millConfiguration.getMillTime();

  String output;
  root.printTo(output);
  server.send ( 200, "application/json", output);  
}




RESTServer::RESTServer(MillConfiguration& millConfiguration, MillManager &millManager, int port):millConfiguration(millConfiguration), millManager(millManager), server(port)
{ 
  server.on("/ping", HTTP_GET, std::bind(&RESTServer::handlePing, this));
  
  server.on("/milltime", HTTP_POST, std::bind(&RESTServer::handlePostMillTime, this));
  server.on("/milltime", HTTP_GET, std::bind(&RESTServer::handleGetMillTime, this));
  
  server.on("/status", HTTP_GET, std::bind(&RESTServer::handleGetStatus, this));

  server.on("/toogle", HTTP_POST, std::bind(&RESTServer::handleToogle, this));
}

void RESTServer::begin()
{
  server.begin();   
}

void RESTServer::handleClient()
{
  server.handleClient();
}

