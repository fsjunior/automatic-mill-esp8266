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
 
#ifndef _MILL_CONFIGURATION_HPP_
#define _MILL_CONFIGURATION_HPP_


class MillConfiguration {
  private:
    unsigned millTime;

    void saveConfiguration();
    void loadConfiguration();
    
    

  public:
    MillConfiguration();


    unsigned getMillTime();
    void setMillTime(unsigned millTime);
  
};


#endif /* _MILL_CONFIGURATION_HPP_ */
