

//==========================================================
//****Зчитуємо конфігурацію
boolean ReadConfig() {
  Serial.println("Reading Configuration");
  if (EEPROM.read(0) == 'C' && EEPROM.read(1) == 'F'  && EEPROM.read(2) == 'G' )
  {
    Serial.println("Configurarion Found!");
    config.dhcp =   EEPROM.read(16);
    config.isDayLightSaving = EEPROM.read(17);
    config.Update_Time_Via_NTP_Every = EEPROMReadlong(18); // 4 Byte
    config.timeZone = EEPROMReadlong(22); // 4 Byte
    config.IP[0] = EEPROM.read(32);
    config.IP[1] = EEPROM.read(33);
    config.IP[2] = EEPROM.read(34);
    config.IP[3] = EEPROM.read(35);
    config.Netmask[0] = EEPROM.read(36);
    config.Netmask[1] = EEPROM.read(37);
    config.Netmask[2] = EEPROM.read(38);
    config.Netmask[3] = EEPROM.read(39);
    config.Gateway[0] = EEPROM.read(40);
    config.Gateway[1] = EEPROM.read(41);
    config.Gateway[2] = EEPROM.read(42);
    config.Gateway[3] = EEPROM.read(43);
    config.DNS[0] = EEPROM.read(44);
    config.DNS[1] = EEPROM.read(45);
    config.DNS[2] = EEPROM.read(46);
    config.DNS[3] = EEPROM.read(47);
    config.ssid = ReadStringFromEEPROM(64);
    config.password = ReadStringFromEEPROM(96);
    config.ntpServerName = ReadStringFromEEPROM(128);
    config.OpenWeatherKey = ReadStringFromEEPROM(160);
    config.OpenWeatherCityId = ReadStringFromEEPROM(192);
    config.relayBoiler = EEPROM.read(224);
    config.relaySmallroom = EEPROM.read(225);                
    config.relayBedroom = EEPROM.read(226);   

    config.nightTemperature = EEPROM_float_read(227);
    config.nightGiterezis = EEPROM_float_read(231);
    config.timeNightStart = EEPROMReadInt(235);
    config.timeNightStop = EEPROMReadInt(237);

    config.dayTemperature = EEPROM_float_read(239);
    config.dayGiterezis = EEPROM_float_read(243);
    config.timeDayStart = EEPROMReadInt(247);
    config.timeDayStop = EEPROMReadInt(249);

    config.eveningTemperature = EEPROM_float_read(251);
    config.eveningGiterezis = EEPROM_float_read(255);
    config.timeEveningStart = EEPROMReadInt(259);
    config.timeEveningStop = EEPROMReadInt(261);
    
    config.sundayTemperature = EEPROM_float_read(263);
    config.sundayGiterezis = EEPROM_float_read(267);
    config.timeSundayStart = EEPROMReadInt(271);
    config.timeSundayStop = EEPROMReadInt(273);

    config.fanTemperature = EEPROM_float_read(275);
    config.fanGiterezis = EEPROM_float_read(279);
    config.timeFanStart = EEPROMReadInt(283);
    config.timeFanStop = EEPROMReadInt(285);

    config.morningTemperature = EEPROM_float_read(287);
    config.morningGiterezis = EEPROM_float_read(291);
    config.timeMorningStart = EEPROMReadInt(295);
    config.timeMorningStop = EEPROMReadInt(297);

    return true;
  }
  else
  {
    Serial.println("Configurarion NOT FOUND!!!!");
    return false;
  }
}

// =======================================================================
//****Виводимо в консоль інформацію про мережу
void printConfigNetwork() {
  Serial.println("Printing Config");
  Serial.printf("IP:%d.%d.%d.%d\n", config.IP[0],config.IP[1],config.IP[2],config.IP[3]);
  Serial.printf("Mask:%d.%d.%d.%d\n", config.Netmask[0],config.Netmask[1],config.Netmask[2],config.Netmask[3]);
  Serial.printf("Gateway:%d.%d.%d.%d\n", config.Gateway[0],config.Gateway[1],config.Gateway[2],config.Gateway[3]);
  Serial.printf("DNS:%d.%d.%d.%d\n", config.DNS[0],config.DNS[1],config.DNS[2],config.DNS[3]);
  Serial.printf("SSID:%s\n", config.ssid.c_str());
  Serial.printf("PWD:%s\n", config.password.c_str());
}

// =======================================================================
//****Виводимо в консоль інформацію про мережу
void defaultConfig() {
  // DEFAULT CONFIG
    Serial.println("Setting AP mode default parameters");
    config.ssid = "UFA Iot";       // SSID of access point
    config.password = "" ;   // password of access point
    config.dhcp = true;
    config.IP[0] = 192; config.IP[1] = 168; config.IP[2] = 1; config.IP[3] = 105;
    config.Netmask[0] = 255; config.Netmask[1] = 255; config.Netmask[2] = 255; config.Netmask[3] = 0;
    config.Gateway[0] = 192; config.Gateway[1] = 168; config.Gateway[2] = 1; config.Gateway[3] = 1;
    config.DNS[0] = 192; config.DNS[1] = 168; config.DNS[2] = 1; config.DNS[3] = 1;
    config.ntpServerName = "2.ua.pool.ntp.org"; // to be adjusted to PT ntp.ist.utl.pt
    config.Update_Time_Via_NTP_Every =  60;
    config.timeZone = 2;
    config.isDayLightSaving = true;
    config.OpenWeatherKey = "7e12124700dd5ea5e1a8f081bd6f6e48";
    config.OpenWeatherCityId = "707099";

    config.relayBoiler = 0;
    config.relayBedroom = 0;
    config.relaySmallroom = 0; 

    config.nightTemperature = 17.0;
    config.nightGiterezis = 0.5;
    config.timeNightStart = 0;
    config.timeNightStop = 299;

    config.morningTemperature = 20.0;
    config.morningGiterezis = 0.5;
    config.timeMorningStart = 300;
    config.timeMorningStop = 389;

    config.dayTemperature = 19.0;
    config.dayGiterezis = 0.5;
    config.timeDayStart = 390;
    config.timeDayStop = 959;

    config.eveningTemperature = 21;
    config.eveningGiterezis = 0.5;
    config.timeEveningStart = 960;
    config.timeEveningStop = 1379;

    config.sundayTemperature = 21;
    config.sundayGiterezis = 0.5;
    config.timeSundayStart = 360;
    config.timeSundayStop = 1379;

    config.fanTemperature = 40;
    config.fanGiterezis = 10;
    config.timeFanStart = 360;
    config.timeFanStop = 1379;


   
    WiFi.mode(WIFI_AP);  
    WiFi.softAP(config.ssid.c_str());
    Serial.print("Wifi ip:");
    Serial.println(WiFi.softAPIP());
}

// =======================================================================
//**** Завантаження мережі
void configLoad() {
  bool CFG_saved = false;
  int WIFI_connected = false;
  Serial.begin(MonitorSpeed);

  //**** Конфігурація мережі
  EEPROM.begin(EEPROMSize); // Визначити простір EEPROM 512Bytes для зберігання даних
  CFG_saved = ReadConfig();
  if (CFG_saved)  //якщо конфігурація ще не збережена, завантаження за замовчуванням
  {    
      // Підключення ESP8266 до локальної мережі WIFI в режимі станції
      Serial.println("Booting");
      WiFi.mode(WIFI_STA);
    // Якщо dhcp не сконфігуровано
    if (!config.dhcp)
    {
      WiFi.config(IPAddress(config.IP[0], config.IP[1], config.IP[2], config.IP[3] ),
        IPAddress(config.Gateway[0], config.Gateway[1], config.Gateway[2], config.Gateway[3] ),
          IPAddress(config.Netmask[0], config.Netmask[1], config.Netmask[2], config.Netmask[3] ),
            IPAddress(config.DNS[0], config.DNS[1], config.DNS[2], config.DNS[3] ));
    }
        WiFi.begin(config.ssid.c_str(), config.password.c_str());
        printConfigNetwork();
        WIFI_connected = WiFi.waitForConnectResult();
  
        if(WIFI_connected!= WL_CONNECTED )
        {
          Serial.println("Connection Failed! activating to AP mode...");
          Serial.print("Wifi ip:");Serial.println(WiFi.localIP());
        }
  }
  if ( (WIFI_connected!= WL_CONNECTED) or !CFG_saved)
  {
    defaultConfig();
  }
}

// =======================================================================
//**** Старт сервера
void startHTTPServer() {

  server.on ( "/", []() {
      Serial.println("index.html");
      server.send_P ( 200, "text/html", PAGE_Index);  
    }  );

   server.on ( "/temperature-config.html", save_Temperature_configuration_html);  
   

  server.on ( "/admin", []() {
      Serial.println("admin.html");
      server.send_P ( 200, "text/html", PAGE_AdminMainPage);  
    }  );
  
    server.on ( "/favicon.ico",   []() {
      Serial.println("favicon.ico");
      server.send( 200, "text/html", "" );
    }  );

    // Network config
    server.on ( "/config.html", send_network_configuration_html);

     // Info Page
    server.on ( "/info.html", []() {
      Serial.println("info.html");
      server.send_P ( 200, "text/html", PAGE_Information );
    }  );

    
    server.on ( "/ntp.html", send_NTP_configuration_html );
    server.on ( "/weather-config.html", send_weather_config_html  );

    //server.on ( "/temperature-config.html", send_Temperature_configuration_html);
    
    server.on ( "/style.css", []() {
      Serial.println("style.css");
      server.send_P ( 200, "text/plain", PAGE_Style_css );
    } );
    server.on ( "/microajax.js", []() {
      Serial.println("microajax.js");
      server.send_P ( 200, "text/plain", PAGE_microajax_js );
    } );
    server.on ( "/admin/values", send_network_configuration_values_html );
    server.on ( "/admin/connectionstate", send_connection_state_values_html );
    server.on ( "/admin/infovalues", send_information_values_html );
    server.on ( "/admin/ntpvalues", send_NTP_configuration_values_html );
    server.on ( "/admin/weather-Settings-values", send_weather_configuration_values_html);
    server.on ( "/admin/index-values", send_index_values_html);
    server.on ( "/admin/temperature", send_Temperature_configuration_html);
    //server.on ( "/admin/save-weather-config",     send_weather_config_html);
     server.onNotFound ( []() {
      Serial.println("Page Not Found");
      server.send ( 400, "text/html", "Page not Found" );
    }  );
    server.begin();
    Serial.println( "HTTP server started" );
}

// =======================================================================
//**** Конфігурація реле
void relaySetup() {
  pinMode(5, OUTPUT); //D1
  digitalWrite(5, 1);
  pinMode(4, OUTPUT); //D2
  digitalWrite(4, 1);
  pinMode(0, OUTPUT); //D3
  digitalWrite(0, 1);
  pinMode(2, OUTPUT); //D4
  digitalWrite(2, 1);
}

// =======================================================================
//**** Конфігурація безпровідної прошивки
void startArduinoOTA() {
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
Serial.println(WiFi.localIP());
}

// =======================================================================
//**** Конфігурація логів
void startLog() {
  Debug.begin(config.IP[0]+(String)"."+config.IP[1]+(String)"."+config.IP[2]+(String)"."+config.IP[3]);
  Debug.setResetCmdEnabled(true);
  Debug.showTime(true);
}

