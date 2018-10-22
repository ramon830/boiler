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
//****Управління реле
void thermostatControl() {
    getTime();
   if (force(config.relayBoiler, &relayBoilerOn)==false) {
       boolean tempSmallRoom;
       boolean tempBedRoom;
       if (wd == "Субота" || wd == "Неділя") {
                tempSmallRoom = thermostat(config.sundayTemperature, config.sundayGiterezis, 
        getTemperatureFromFilter(smallRoom),
        config.timeSundayStart, config.timeSundayStop, true, relayBoilerOn);
                tempBedRoom = thermostat(config.sundayTemperature, config.sundayGiterezis, 
        getTemperatureFromFilter(bedRoom),
        config.timeSundayStart, config.timeSundayStop, true, relayBoilerOn);
         
        } else {
           
                if(thermostat(config.nightTemperature, config.nightGiterezis, 
                    getTemperatureFromFilter(smallRoom),
                    config.timeNightStart, config.timeNightStop, true, relayBoilerOn)) {
                      tempSmallRoom = true; 
                } else {
                if (thermostat(config.morningTemperature, config.morningGiterezis, 
                    getTemperatureFromFilter(smallRoom),
                    config.timeMorningStart, config.timeMorningStop, true, relayBoilerOn)) {
                        tempSmallRoom = true;
                    } else {
                        if (thermostat(config.dayTemperature, config.dayGiterezis, 
                        getTemperatureFromFilter(smallRoom),
                        config.timeDayStart, config.timeDayStop, true, relayBoilerOn)) {
                            tempSmallRoom = true;
                        } else {
                                if (thermostat(config.eveningTemperature, config.eveningGiterezis, 
                            getTemperatureFromFilter(smallRoom),
                            config.timeEveningStart, config.timeEveningStop, true, relayBoilerOn)) {
                                tempSmallRoom = true;
                            } else {
                               tempSmallRoom = false; 
                            }  
                        }   
                    } 
                      
                }

                 if(thermostat(config.nightTemperature, config.nightGiterezis, 
                    getTemperatureFromFilter(bedRoom),
                    config.timeNightStart, config.timeNightStop, true, relayBoilerOn)) {
                     tempBedRoom  = true; 
                } else {
                if (thermostat(config.morningTemperature, config.morningGiterezis, 
                    getTemperatureFromFilter(bedRoom),
                    config.timeMorningStart, config.timeMorningStop, true,relayBoilerOn)) {
                        tempBedRoom= true;
                    } else {
                        if (thermostat(config.dayTemperature, config.dayGiterezis, 
                        getTemperatureFromFilter(bedRoom),
                        config.timeDayStart, config.timeDayStop, true, relayBoilerOn)) {
                            tempBedRoom = true;
                        } else {
                                if (thermostat(config.eveningTemperature, config.eveningGiterezis, 
                            getTemperatureFromFilter(bedRoom),
                            config.timeEveningStart, config.timeEveningStop, true, relayBoilerOn)) {
                                tempBedRoom = true;
                            } else {
                               tempBedRoom = false; 
                            }  
                        }   
                    } 
                      
                }



        
        }
        if (tempSmallRoom || tempBedRoom) {
                relayBoilerOn = true;
            } else {
                relayBoilerOn = false;
            }
   }
   if (force(config.relaySmallroom, &relaySmallroomOn)==false) {
       relaySmallroomOn = thermostat(config.fanTemperature, config.fanGiterezis, 
       getTemperatureFromFilter(radiatorSmallRoom),
       config.timeFanStart, config.timeFanStop, false, relaySmallroomOn);
   }
   if (force(config.relayBedroom, &relayBedroomOn)==false) {
       relayBedroomOn = thermostat(config.fanTemperature, config.fanGiterezis, 
       getTemperatureFromFilter(radiatorBedRoom),
       config.timeFanStart, config.timeFanStop, false, relayBedroomOn);
   }
  relayOn();
}