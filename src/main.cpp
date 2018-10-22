#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <WiFiUdp.h>
#include <EEPROM.h>
#include <TickerScheduler.h>
#include <ArduinoJson.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ArduinoOTA.h>
#include "configuration/global.h"
#include "clock/NTP.h"
#include "clock/Time.h"
#include "temperature/temperature.h"
#include "temperature/thermostat.h"
#include "temperature/thingspeak.h"
#include "web/PAGE_Style_css.h"
#include "web/Page_Script_js.h"
#include "web/PAGE_Admin.h"
#include "web/PAGE_NetworkConfiguration.h"
#include "web/Page_Information.h"
#include "web/PAGE_NTPConfiguration.h"
#include "web/Page_Weather_Config.h"
#include "web/PAGE_TemperatureConfig.h"
#include "web/Index.h"
#include "configuration/config.h"





// =======================================================================
void setup() {
  Serial.begin(MonitorSpeed);
  configLoad(); 
  startHTTPServer();
  startArduinoOTA(); 
  SetupDS18B20();
  relaySetup();
  setupAddressTemperature();
  tickerScheduler.add(0, 1000, [&](void*){ISRsecondTick();}, nullptr, true); //Обновлення годинника щосекунди
  tickerScheduler.add(1, config.Update_Time_Via_NTP_Every*60*1000, [&](void*){getNTPtime();}, nullptr, false); // Синхронізація з NTP сервером
  tickerScheduler.add(2, 30*1000, [&](void*){firstGetNTPtime();}, nullptr, true); //Перше обновлення годинника
  tickerScheduler.add(3, 15*60*1000, [&](void*){getOpenWeatherData();}, nullptr, true); //Обновлення погоди Open Weather
  tickerScheduler.add(4, 30*1000, [&](void*){TempLoop();}, nullptr, true); //Вимірювання температури
  tickerScheduler.add(5, 1*1000, [&](void*){thermostatControl();}, nullptr, true); //Робота з реле
  tickerScheduler.add(6, 30*1000, [&](void*){writeToInternet();}, nullptr, true); //Записуємо дані в thingspeak.com
}

void loop() {
    tickerScheduler.update();
    server.handleClient();
    ArduinoOTA.handle();
    customWatchdog = millis();
  
}