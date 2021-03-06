// =======================================================================
//****Переключення реле
void relayOn()
{
    if (!relayBoilerOn)
    {
        digitalWrite(5, 0);
    }
    else
    {
        digitalWrite(5, 1);
    }
    if (relaySmallroomOn)
    {
        digitalWrite(4, 0);
    }
    else
    {
        digitalWrite(4, 1);
    }
    if (relayBedroomOn)
    {
        digitalWrite(0, 0);
    }
    else
    {
        digitalWrite(0, 1);
    }
}

// =======================================================================
//****Режим управління реле
boolean force(byte mode, boolean *relayOn)
{
    if (mode == 1)
    {
        *relayOn = false;
        return true;
    }
    if (mode == 2)
    {
        *relayOn = true;
        return true;
    }
    return false;
}

// =======================================================================
//****Термостат
boolean thermostat(float temperature, float gisterezis, float realTemperature, int startTime,
                   int stopTime, boolean mode, boolean relayOn)
{ 
    //mode - true нагрів, false охолодження
    int realTime = DateTime.hour * 60 + DateTime.minute;
    if ((realTime >= startTime && realTime <= stopTime) ||
        (startTime > stopTime && (realTime >= startTime || realTime <= stopTime)))
    {
        if (mode == true)
        {
            
            if (realTemperature >= (gisterezis + temperature))
            {
                if (relayOn)
                {
                    return false;
                }
            }
            if (realTemperature < temperature)
            {
                if (!relayOn)
                {
                    return true;
                }
            }
        }
        else
        {   
            if (realTemperature > temperature)
            {
                if (!relayOn)
                {
                    return true;
                }
            }
            if (realTemperature <= (temperature - gisterezis))
            {
                if (relayOn)
                {
                    return false;
                }
            }
        }
        if (relayOn)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

// =======================================================================
//****Вихідний день режим
boolean sunday(String address)
{
    return thermostat(config.sundayTemperature, config.sundayGiterezis,
                      getTemperatureFromFilter(address),
                      config.timeSundayStart, config.timeSundayStop, true, relayBoilerOn);
}

// =======================================================================
//****Нічний режим
boolean night(String address)
{
    return thermostat(config.nightTemperature, config.nightGiterezis,
                      getTemperatureFromFilter(address),
                      config.timeNightStart, config.timeNightStop, true, relayBoilerOn);
}

// =======================================================================
//****Ранковий режим
boolean morning(String address)
{
    return thermostat(config.morningTemperature, config.morningGiterezis,
                      getTemperatureFromFilter(address),
                      config.timeMorningStart, config.timeMorningStop, true, relayBoilerOn);
}

// =======================================================================
//****Денний режим
boolean day(String address)
{
    return thermostat(config.dayTemperature, config.dayGiterezis,
                      getTemperatureFromFilter(address),
                      config.timeDayStart, config.timeDayStop, true, relayBoilerOn);
}

// =======================================================================
//****Вечірній режим
boolean evening(String address)
{
    return thermostat(config.eveningTemperature, config.eveningGiterezis,
                      getTemperatureFromFilter(address),
                      config.timeEveningStart, config.timeEveningStop, true, relayBoilerOn);
}

// =======================================================================
//****Вентилятор
boolean fan(String address, boolean relay)
{
    return thermostat(config.fanTemperature, config.fanGiterezis,
                      getTemperatureFromFilter(address),
                      config.timeFanStart, config.timeFanStop, false, relay);
}

// =======================================================================
//****Управління реле
void thermostatControl()
{
    getTime();
    if (force(config.relayBoiler, &relayBoilerOn) == false)
    {
        boolean tempSmallRoom;
        boolean tempBedRoom;
        if (wd == "Субота" || wd == "Неділя")
        {
            if (night(smallRoom))
            {
                setTemperature = config.nightTemperature;
                tempSmallRoom = true;
                //Debug.println("Sunday night small on");
            }
            else if (sunday(smallRoom))
            {
                setTemperature = config.sundayTemperature;
                tempSmallRoom = true;
                //Debug.println("Sunday  small on");
            }
            else
            {
                tempSmallRoom = false;
                //Debug.println("Sunday  small off");
            }
            if (night(bedRoom))
            {
                setTemperature = config.nightTemperature;
                tempBedRoom = true;
                //Debug.println("Sunday night bedroom on");
            }
            else if (sunday(bedRoom))
            {
                setTemperature = config.sundayTemperature;
                tempBedRoom = true;
                //Debug.println("Sunday bedroom on");
            }
            else
            {
                tempBedRoom = false;
                //Debug.println("Sunday bedroom off");
            }
        }
        else
        {
            if (night(smallRoom))
            {
                setTemperature = config.nightTemperature;
                tempSmallRoom = true;
                //Debug.println("night small on");
            }
            else if (morning(smallRoom))
            {
                setTemperature = config.morningTemperature;
                tempSmallRoom = true;
                //Debug.println("morning small on");
            }
            else if (day(smallRoom))
            {
                setTemperature = config.dayTemperature;
                tempSmallRoom = true;
                //Debug.println("day small on");
            }
            else if (evening(smallRoom))
            {
                setTemperature = config.eveningTemperature;
                tempSmallRoom = true;
                //Debug.println("evening small on");
            }
            else
            {
                tempSmallRoom = false;
                //Debug.println("small off");
            }
            if (night(bedRoom))
            {
                setTemperature = config.nightTemperature;
                tempBedRoom = true;
                //Debug.println("night bedroom on");
            }
            else if (morning(bedRoom))
            {
                setTemperature = config.morningTemperature;
                tempBedRoom = true;
                //Debug.println("morning bedroom on");
            }
            else if (day(bedRoom))
            {
                setTemperature = config.dayTemperature;
                tempBedRoom = true;
                //Debug.println("day bedroom on");
            }
            else if (evening(bedRoom))
            {
                setTemperature = config.eveningTemperature;
                tempBedRoom = true;
                //Debug.println("evening bedroom on");
            }
            else
            {
                tempBedRoom = false;
                //Debug.println("bedroom off");
            }
        }
        if (tempBedRoom || tempSmallRoom)
        {
            relayBoilerOn = true;
        }
        else
        {
            relayBoilerOn = false;
        }
    }
    if (force(config.relaySmallroom, &relaySmallroomOn) == false)
    {
        relaySmallroomOn = fan(radiatorSmallRoom, relaySmallroomOn);
    }
    if (force(config.relayBedroom, &relayBedroomOn) == false)
    {
        relayBedroomOn = fan(radiatorBedRoom, relayBedroomOn);
    }
    relayOn();
}