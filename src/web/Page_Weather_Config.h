//
//  HTML PAGE
//

const char PAGE_WeatherSettings[] PROGMEM =  R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<a href="/admin"  class="btn btn--s"><</a>&nbsp;&nbsp;<strong>Налаштування погоди</strong>
<hr>

<form action="" method="post">
<table border="0"  cellspacing="0" cellpadding="3" >
<tr>
  <td align="right">API ключ</td>
  <td><input id="OpenWeatherKey" name="OpenWeatherKey" size="32" value=""></td>
</tr>

<tr>
  <td align="right">cityID</td>
  <td><input type="text" id="OpenWeatherCityId" name="OpenWeatherCityId" value=""></td>
</tr>

<tr><td colspan="2" align="center"><input type="submit" style="width:150px" class="btn btn--m btn--blue" value="Зберегти"></td></tr>
</table>
</form>

<script>


window.onload = function ()
{
  load("style.css","css", function() 
  {
    load("microajax.js","js", function() 
    {
        setValues("/admin/weather-Settings-values");
    });
  });
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",
a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].
appendChild(a)}else if("css"==t){var a=document.createElement("link");
a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},
document.getElementsByTagName("head")[0].appendChild(a)}}



</script>
)=====";

//==========================================================
//**** Збереження конфігурації погоди
void send_weather_config_html()
{
  
  if (server.args() > 0 )  // Save Settings
  { 
    String temp = "";
    for ( uint8_t i = 0; i < server.args(); i++ ) {
      if (server.argName(i) == "OpenWeatherKey") config.OpenWeatherKey = urldecode(server.arg(i)); 
      if (server.argName(i) == "OpenWeatherCityId") config.OpenWeatherCityId = urldecode(server.arg(i));
    }
    WriteConfig();
    
  }
  server.send_P ( 200, "text/html", PAGE_WeatherSettings ); 
  Serial.println(__FUNCTION__); 
   
}

//==========================================================
//**** Встановлюємо данні налаштуваннь серверів погоди
void send_weather_configuration_values_html()
{
  String values ="";
  values += "OpenWeatherKey|" +  (String)  config.OpenWeatherKey +  "|input\n";
  values += "OpenWeatherCityId|" +  (String)  config.OpenWeatherCityId +  "|input\n";
 
  server.send ( 200, "text/plain", values);
  Serial.println(__FUNCTION__); 
}

//==========================================================
//**** Запит до сервера погоди openweather
bool httpRequest() {
  HTTPClient client;
  bool find = false;
  //client.setTimeout(1000);
  Serial.print("Connecting ");
  client.begin("http://" + weatherHost + "/data/2.5/weather?id=" + (String)config.OpenWeatherCityId + "&appid=" + 
  (String)config.OpenWeatherKey);
  int httpCode = client.GET();

  if (httpCode > 0) {
    Serial.printf("successfully, code: %d\n", httpCode);
    if (httpCode == HTTP_CODE_OK) {
      httpData = client.getString();
      if (httpData.indexOf(F("\"main\":{\"temp\":")) > -1) {
       // lastConnectionTime = millis();
        find = true;
      }
      else Serial.println("Failed, json string is not found");
    }
  }
  else Serial.printf("failed, error: %s\n", client.errorToString(httpCode).c_str());

  //postingInterval = find ? 600L * 1000L : 60L * 1000L;
  client.end();

  return find;
}

//==========================================================
//**** Парсем відповідь OpenWeather 
bool parseData() {
  Serial.println(httpData);

  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(httpData);

  if (!root.success()) {
    Serial.println("Json parsing failed!");
    return false;
  }

  Oweather.id       = root["weather"][0]["id"];
  Oweather.main     = root["weather"][0]["main"];
  Oweather.descript = root["weather"][0]["description"];
  Oweather.icon     = root["weather"][0]["icon"];
  Oweather.temp     = root["main"]["temp"];
  Oweather.humidity = root["main"]["humidity"];
  Oweather.pressure = root["main"]["pressure"];
  Oweather.speed    = root["wind"]["speed"];
  Oweather.deg      = root["wind"]["deg"];

  httpData = "";
  return true;
}

// =======================================================================
//**** Приймаємо данні про погоду з openweather
void getOpenWeatherData() {
  if (WiFi.status() == WL_CONNECTED) {
    httpRequest();
    parseData();
  }
  Serial.println("\nWeather");
        Serial.printf("id: %d\n", Oweather.id);
        Serial.printf("main: %s\n", Oweather.main);
        Serial.printf("description: %s\n", Oweather.descript);
        Serial.printf("icon: %s\n", Oweather.icon);
        Serial.printf("temp: %d celsius\n", round(Oweather.temp));
        Serial.printf("humidity: %d %\n", round(Oweather.humidity));
        Serial.printf("pressure: %d hPa or %d mmHg\n", round(Oweather.pressure), round(Oweather.pressure * 0.75));
        Serial.printf("wind's speed: %d\n", round(Oweather.speed));
        Serial.printf("wind's direction: %d\n", round(Oweather.deg));
        Serial.println();
}

// =======================================================================
//**** Напрям вітру
String windDirection() {
if (Oweather.deg>=345 || Oweather.deg<=22) return   "Північний";
if (Oweather.deg>=23 && Oweather.deg<=68) return    "Північно-Східний";
if (Oweather.deg>=69 && Oweather.deg<=114) return   "Східний";
if (Oweather.deg>=115 && Oweather.deg<=160) return  "Південно-східний";
if (Oweather.deg>=161 && Oweather.deg<=206) return  "Південний";
if (Oweather.deg>=207 && Oweather.deg<=252) return  "Південно-західний";
if (Oweather.deg>=253 && Oweather.deg<=298) return  "Західний";
if (Oweather.deg>=299 && Oweather.deg<=344) return  "Північно-західний";
  return "";
}

