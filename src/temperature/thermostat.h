// =======================================================================
//****Переключення реле
void relayOn() {
    if (!relayBoilerOn) {
        digitalWrite(5, 0);
    } else {
        digitalWrite(5, 1);
    }
    if (relaySmallroomOn) {
        digitalWrite(4, 0);
    } else {
        digitalWrite(4, 1);
    }
    if (relayBedroomOn) {
        digitalWrite(0, 0);
    } else {
        digitalWrite(0, 1);
    }
}

// =======================================================================
//****Режим управління реле
boolean force(byte mode, boolean *relayOn) {
    if (mode == 1) {
        *relayOn = false;
        return true;
    }
    if (mode == 2) {
        *relayOn = true;
        return true;
    }
    return false;
}

// =======================================================================
//****Термостат
boolean thermostat(float temperature, float gisterezis, float realTemperature, int startTime, 
int stopTime, boolean mode, boolean relayOn) { //mode - true нагрів, false охолодження
    int realTime = DateTime.hour*60+DateTime.minute;
    if (realTime >= startTime && realTime <= stopTime) {
        if (mode == true) {
            if (realTemperature > (gisterezis +  temperature)) {
                if (relayOn) {
                    return false;
                }
            }
            if(realTemperature <  temperature) {
               if (!relayOn) {
                    return true;
                } 
            }
             if (relayOn) {
                return true;
            } else {
                 return false;
            }
            
        } else {
        if (realTemperature>temperature) {
                if (!relayOn) {
                    return true;
                }
            } 
            if (realTemperature <(temperature -gisterezis)) {
               if (relayOn) {
                    return false;
                }
            }
            if (relayOn) {
                return true;
            } else {
                 return false;
            }
            
        }
    } else return false;
    
}

// =======================================================================
//****Вихідний день режим
boolean sunday(String address) {
return thermostat(config.sundayTemperature, config.sundayGiterezis, 
                        getTemperatureFromFilter(smallRoom),
                        config.timeSundayStart, config.timeSundayStop, true, relayBoilerOn);
}

// =======================================================================
//****Нічний режим
boolean night(String address) {
return   thermostat(config.nightTemperature, config.nightGiterezis, 
                        getTemperatureFromFilter(address),
                        0, 299, true, relayBoilerOn);
}

// =======================================================================
//****Ранковий режим
boolean morning(String address) {
return thermostat(config.morningTemperature, config.morningGiterezis, 
                        getTemperatureFromFilter(address),
                        config.timeMorningStart, config.timeMorningStop, true, relayBoilerOn);
}

// =======================================================================
//****Денний режим
boolean day(String address) {
return thermostat(config.dayTemperature, config.dayGiterezis, 
                        getTemperatureFromFilter(address),
                        config.timeDayStart, config.timeDayStop, true, relayBoilerOn);
}

// =======================================================================
//****Вечірній режим
boolean evening(String address) {
return thermostat(config.eveningTemperature, config.eveningGiterezis, 
                        getTemperatureFromFilter(address),
                        config.timeEveningStart, config.timeEveningStop, true, relayBoilerOn);
}

// =======================================================================
//****Вентилятор
boolean fan(String address, boolean relay) {
return thermostat(config.fanTemperature, config.fanGiterezis, 
                        getTemperatureFromFilter(address),
                        config.timeFanStart, config.timeFanStop, false, relaySmallroomOn);
}

// =======================================================================
//****Управління реле
void thermostatControl() {
    getTime();
   if (force(config.relayBoiler, &relayBoilerOn)==false) {
       boolean tempSmallRoom;
       boolean tempBedRoom;
       if (wd == "Субота" || wd == "Неділя") {
           if(night(smallRoom)) {tempSmallRoom = true;}
                else if(sunday(smallRoom)){tempSmallRoom = true;}
                    else {tempSmallRoom = false; }
            if(night(bedRoom)) {tempBedRoom  = true;}
                else if(sunday(bedRoom)){tempBedRoom  = true;}
                    else {tempBedRoom  = false;}
                
        } else {
            if(night(smallRoom)) {tempSmallRoom = true;}
                else if (morning(smallRoom)) {tempSmallRoom = true;}
                    else if (day(smallRoom)) {tempSmallRoom = true;}
                        else if (evening(smallRoom)) {tempSmallRoom = true;}
                            else {tempSmallRoom = false;}  
            if(night(bedRoom)) {tempBedRoom  = true;}
                else if (morning(bedRoom)) {tempBedRoom= true;}
                    else if (day(bedRoom)) {tempBedRoom = true;}
                        else if (evening(bedRoom)) {tempBedRoom = true;}
                            else {tempBedRoom = false;}  
        }
        if (tempSmallRoom || tempBedRoom) {
                relayBoilerOn = true;
                } else {
                    relayBoilerOn = false;
                }
        
   }
   if (force(config.relaySmallroom, &relaySmallroomOn)==false) {
       relaySmallroomOn = fan(radiatorSmallRoom, relaySmallroomOn);
    }
   if (force(config.relayBedroom, &relayBedroomOn)==false) {
       relayBedroomOn = fan(radiatorBedRoom, relayBedroomOn);
   }
  relayOn();
}