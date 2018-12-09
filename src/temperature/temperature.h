//==========================================================
//****Конвертація device id to String
String GetAddressToString(DeviceAddress deviceAddress){
  String str = "";
  for (uint8_t i = 0; i < 8; i++){
    if( deviceAddress[i] < 16 ) str += String(0, HEX);
    str += String(deviceAddress[i], HEX);
  }
  return str;
}

//==========================================================
//****Настройки сенсора
void SetupDS18B20(){
  DS18B20.begin();

  Debug.print("Parasite power is: "); 
  if( DS18B20.isParasitePowerMode() ){ 
    Debug.println("ON");
  }else{
    Debug.println("OFF");
  }
  
  numberOfDevices = DS18B20.getDeviceCount();
  Debug.print( "Device count: " );
  Debug.println( numberOfDevices );
   
  DS18B20.requestTemperatures();

  // Loop through each device, print out address
  for(int i=0;i<numberOfDevices; i++){
    // Search the wire for address
    if( DS18B20.getAddress(devAddr[i], i) ){
      //devAddr[i] = tempDeviceAddress;
      Debug.print("Found device ");
      Debug.print(i, DEC);
      Debug.print(" with address: " + GetAddressToString(devAddr[i]));
      Debug.println();
    }else{
      Debug.print("Found ghost device at ");
      Debug.print(i, DEC);
      Debug.print(" but could not detect address. Check power and cabling");
    }

    //Get resolution of DS18b20
    Debug.print("Resolution: ");
    Debug.print(DS18B20.getResolution( devAddr[i] ));
    Debug.println();

    //Read temperature from DS18b20
    float tempC = DS18B20.getTempC( devAddr[i] );
    Debug.print("Temp C: ");
    Debug.println(tempC);
    
  }
  
}

//==========================================================
//****Ініціалізація адрес температур
void setupAddressTemperature() {
  tempArray[0].address = smallRoom;  //Дитяча кімната
  tempArray[1].address = radiatorSmallRoom; 	//Батарея мала кімната	
  tempArray[2].address = bedRoom; 	//Спальня
  tempArray[3].address = radiatorBedRoom; 	//Батарея спальня
}

//==========================================================
//****Добавляння температури 
void addTemperature(String address, float temp) {
  for (int i=0; i<ONE_WIRE_MAX_DEV; i++) {
    if (temp < 0 || temp > 80) {
      SetupDS18B20();
    }
    if (tempArray[i].address == address) {
      tempArray[i].temperature = temp;
      break;
    }
  }

}

//==========================================================
//****Температура з масива
float getTemperatureFromFilter(String address) {
  for (int i=0; i<ONE_WIRE_MAX_DEV; i++) {
    if (tempArray[i].address == address) {
      return tempArray[i].temperature;
    }
  }
}





//==========================================================
//Loop measuring the temperature
void TempLoop(){
    for(int i=0; i<numberOfDevices; i++){
     /* float tempC = DS18B20.getTempC( devAddr [i]); //Measuring temperature in Celsius
      tempDev[i] = tempC; //Save the measured value to the array*/
      addTemperature(GetAddressToString(devAddr[i]), DS18B20.getTempC( devAddr [i]));


    }
    DS18B20.setWaitForConversion(false); //No waiting for measurement
    DS18B20.requestTemperatures(); //Initiate the temperature measurement
  
 
 
  
}

