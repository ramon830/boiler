//
//   The HTML PAGE
//
const char PAGE_Temperature[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<link rel="stylesheet" href="style.css" type="text/css" />
<script src="microajax.js"></script> 
<a href="/admin"  class="btn btn--s"><</a>&nbsp;&nbsp;<strong>Налаштування термостата</strong>
<hr>
<form action="" method="get">
<table border="0"  cellspacing="0" cellpadding="3" style="width:640px" >
<tr><td align="center"><strong>Режим роботи реле</strong></td></tr>
<tr>
<td>Реле котла: </td>
<td>
<select  id="relay_boiler" name="relay_boiler">
  <option value="auto">Автоматичний</option>
  <option value="OFF">Виключено</option>
  <option value="ON">Включено</option>
</select>  
</td>
</tr>

<tr>
<td>Реле вент. малої кімнати: </td>
<td>
<select  id="relay_smallroom" name="relay_smallroom">
  <option value="auto">Автоматичний</option>
  <option value="OFF">Виключено</option>
  <option value="ON">Включено</option>
</select>  
</td>
</tr>

<tr>
<td>Реле вент. спальні: </td>
<td>
<select  id="relay_bedroom" name="relay_bedroom">
  <option value="auto">Автоматичний</option>
  <option value="OFF">Виключено</option>
  <option value="ON">Включено</option>
</select>  
</td>
</tr>



<tr><td align="center"><strong>Нічний режим</strong></td></tr>
<tr>
<td align="center">Задана температура: </td><td><input type="text" id="night_temp" name="night_temp" size="3"></td>
<td align="center">Гістерезис: </td><td><input type="text" id="night_giterezis" name="night_giterezis" size="3"></td>
</tr>
<tr>
<td align="center">Час спрацювання: <input type="time" id="time_night_start" name="time_night_start" value=""></td>
<td align="center">Час зупинки: <input type="time" id="time_night_stop" name="time_night_stop" value=""></td>
</tr>

<tr><td align="center"><strong>Ранковий режим</strong></td></tr>
<tr>
<td align="center">Задана температура: </td><td><input type="text" id="morning_temp" name="morning_temp" size="3"></td>
<td align="center">Гістерезис: </td><td><input type="text" id="morning_giterezis" name="morning_giterezis" size="3"></td>
</tr>
<tr>
<td align="center">Час спрацювання: <input type="time" id="time_morning_start" name="time_morning_start" value=""></td>
<td align="center">Час зупинки: <input type="time" id="time_morning_stop" name="time_morning_stop" value=""></td>
</tr>

<tr><td align="center"><strong>Денний режим</strong></td></tr>
<tr>
<td align="center">Задана температура: </td><td><input type="text" id="day_temp" name="day_temp" size="3"></td>
<td align="center">Гістерезис: </td><td><input type="text" id="day_giterezis" name="day_giterezis" size="3"></td>
</tr>
<tr>
<td align="center">Час спрацювання: <input type="time" id="time_day_start" name="time_day_start" value=""></td>
<td align="center">Час зупинки: <input type="time" id="time_day_stop" name="time_day_stop" value=""></td>
</tr>

<tr><td align="center"><strong>Вечірній режим</strong></td></tr>
<tr>
<td align="center">Задана температура: </td><td><input type="text" id="evening_temp" name="evening_temp" size="3"></td>
<td align="center">Гістерезис: </td><td><input type="text" id="evening_giterezis" name="evening_giterezis" size="3"></td>
</tr>
<tr>
<td align="center">Час спрацювання: <input type="time" id="time_evening_start" name="time_evening_start" value=""></td>
<td align="center">Час зупинки: <input type="time" id="time_evening_stop" name="time_evening_stop" value=""></td>
</tr>

<tr><td align="center"><strong>Режим вихідного дня</strong></td></tr>
<tr>
<td align="center">Задана температура: </td><td><input type="text" id="sunday_temp" name="sunday_temp" size="3"></td>
<td align="center">Гістерезис: </td><td><input type="text" id="sunday_giterezis" name="sunday_giterezis" size="3"></td>
</tr>
<tr>
<td align="center">Час спрацювання: <input type="time" id="time_sunday_start" name="time_sunday_start" value=""></td>
<td align="center">Час зупинки: <input type="time" id="time_sunday_stop" name="time_sunday_stop" value=""></td>
</tr>

<tr><td align="center"><strong>Вентилятори</strong></td></tr>
<tr>
<td align="center">Задана температура: </td><td><input type="text" id="fan_temp" name="fan_temp" size="3"></td>
<td align="center">Гістерезис: </td><td><input type="text" id="fan_giterezis" name="fan_giterezis" size="3"></td>
</tr>
<tr>
<td align="center">Час спрацювання: <input type="time" id="time_fan_start" name="time_fan_start" value=""></td>
<td align="center">Час зупинки: <input type="time" id="time_fan_stop" name="time_fan_stop" value=""></td>
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
      setValues("/admin/temperature"); 
        
    });
  });
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");
a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.
getElementsByTagName("head")[0].appendChild(a)}else if("css"==t)
{var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,
a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}
</script>
)=====" ;

// =======================================================================
//****Конвертація часу
String convertTime(int t) {
  String s ="";
  int hour = t/60;
  int minute = t-hour*60;
  if (hour <10) {
      s += "0"+ (String)hour; 
    } else {
      s += (String)hour; 
    }
    s+= ":";
    if (minute <10) {
     s += "0"+ (String)minute; 
    } else {
      s += (String)minute; 
    }
  return s;
}

// =======================================================================
//****Режим роботи
String modeWork(int i) {
  if (i==0) return "auto";
  if (i==1) return "OFF";
  if (i==2) return "ON";
  return "";
}

// =======================================================================
//****Вивід налаштувань термостату
void send_Temperature_configuration_html()
{
  String values ="";
  values += "relay_boiler|" + modeWork(config.relayBoiler) + "|input\n";
  values += "relay_smallroom|" + modeWork(config.relaySmallroom) + "|input\n";
  values += "relay_bedroom|" + modeWork(config.relayBedroom) + "|input\n";

  values += "night_temp|" + (String) config.nightTemperature + "|input\n";
  values += "night_giterezis|" + (String) config.nightGiterezis + "|input\n";
  values += "time_night_start|" + convertTime(config.timeNightStart) + "|input\n";
  values += "time_night_stop|" + convertTime(config.timeNightStop) + "|input\n";

  values += "morning_temp|" + (String) config.morningTemperature + "|input\n";
  values += "morning_giterezis|" + (String) config.morningGiterezis + "|input\n";
  values += "time_morning_start|" + convertTime(config.timeMorningStart) + "|input\n";
  values += "time_morning_stop|" + convertTime(config.timeMorningStop) + "|input\n";

  values += "day_temp|" + (String) config.dayTemperature + "|input\n";
  values += "day_giterezis|" + (String) config.dayGiterezis + "|input\n";
  values += "time_day_start|" + convertTime(config.timeDayStart) + "|input\n";
  values += "time_day_stop|" + convertTime(config.timeDayStop) + "|input\n";

  values += "evening_temp|" + (String) config.eveningTemperature + "|input\n";
  values += "evening_giterezis|" + (String) config.eveningGiterezis + "|input\n";
  values += "time_evening_start|" + convertTime(config.timeEveningStart) + "|input\n";
  values += "time_evening_stop|" + convertTime(config.timeEveningStop) + "|input\n";

  values += "sunday_temp|" + (String) config.sundayTemperature + "|input\n";
  values += "sunday_giterezis|" + (String) config.sundayGiterezis + "|input\n";
  values += "time_sunday_start|" + convertTime(config.timeSundayStart) + "|input\n";
  values += "time_sunday_stop|" + convertTime(config.timeSundayStop) + "|input\n";

  values += "fan_temp|" + (String) config.fanTemperature + "|input\n";
  values += "fan_giterezis|" + (String) config.fanGiterezis + "|input\n";
  values += "time_fan_start|" + convertTime(config.timeFanStart) + "|input\n";
  values += "time_fan_stop|" + convertTime(config.timeFanStop) + "|input\n";

  server.send ( 200, "text/html", values ); 
  Serial.println(__FUNCTION__); 
  
}

// =======================================================================
//****Час в хвилини
int timeToString(String _time) {
  String _hour = (String)_time.charAt(0) + (String)_time.charAt(1);
  String _minute = (String)_time.charAt(3) + (String)_time.charAt(4);
  return 60*_hour.toInt()+_minute.toInt();
}

// =======================================================================
//****Збереження налаштувань термостата
void save_Temperature_configuration_html()
{
  if (server.args() > 0 )  // Save Settings
  {
      
    for ( uint8_t i = 0; i < server.args(); i++ ) {
      if (server.argName(i) == "relay_boiler") {
        if (server.arg(i) == "auto")  config.relayBoiler = 0;
        if (server.arg(i) == "ON")  config.relayBoiler = 2;
        if (server.arg(i) == "OFF")  config.relayBoiler = 1;
      }
      if (server.argName(i) == "relay_smallroom") {
        if (server.arg(i) == "auto")  config.relaySmallroom = 0;
        if (server.arg(i) == "ON")  config.relaySmallroom = 2;
        if (server.arg(i) == "OFF")  config.relaySmallroom = 1;
      }
      if (server.argName(i) == "relay_bedroom") {
        if (server.arg(i) == "auto")  config.relayBedroom = 0;
        if (server.arg(i) == "ON")  config.relayBedroom = 2;
        if (server.arg(i) == "OFF")  config.relayBedroom = 1;
      }
      if (server.argName(i) == "night_temp") config.nightTemperature = server.arg(i).toFloat(); 
      if (server.argName(i) == "night_giterezis") config.nightGiterezis = server.arg(i).toFloat();
      if (server.argName(i) == "time_night_start") config.timeNightStart = timeToString(server.arg(i));  
      if (server.argName(i) == "time_night_stop") config.timeNightStop = timeToString(server.arg(i)); 

      if (server.argName(i) == "morning_temp") config.morningTemperature = server.arg(i).toFloat(); 
      if (server.argName(i) == "morning_giterezis") config.morningGiterezis = server.arg(i).toFloat();
      if (server.argName(i) == "time_morning_start") config.timeMorningStart = timeToString(server.arg(i));  
      if (server.argName(i) == "time_morning_stop") config.timeMorningStop = timeToString(server.arg(i)); 

      if (server.argName(i) == "day_temp") config.dayTemperature = server.arg(i).toFloat(); 
      if (server.argName(i) == "day_giterezis") config.dayGiterezis = server.arg(i).toFloat();
      if (server.argName(i) == "time_day_start") config.timeDayStart = timeToString(server.arg(i));  
      if (server.argName(i) == "time_day_stop") config.timeDayStop = timeToString(server.arg(i)); 
      
      if (server.argName(i) == "evening_temp") config.eveningTemperature = server.arg(i).toFloat(); 
      if (server.argName(i) == "evening_giterezis") config.eveningGiterezis = server.arg(i).toFloat();
      if (server.argName(i) == "time_evening_start") config.timeEveningStart = timeToString(server.arg(i));  
      if (server.argName(i) == "time_evening_stop") config.timeEveningStop = timeToString(server.arg(i));

      if (server.argName(i) == "sunday_temp") config.sundayTemperature = server.arg(i).toFloat(); 
      if (server.argName(i) == "sunday_giterezis") config.sundayGiterezis = server.arg(i).toFloat();
      if (server.argName(i) == "time_sunday_start") config.timeSundayStart = timeToString(server.arg(i));  
      if (server.argName(i) == "time_sunday_stop") config.timeSundayStop = timeToString(server.arg(i));

      if (server.argName(i) == "fan_temp") config.fanTemperature = server.arg(i).toFloat(); 
      if (server.argName(i) == "fan_giterezis") config.fanGiterezis = server.arg(i).toFloat();
      if (server.argName(i) == "time_fan_start") config.timeFanStart = timeToString(server.arg(i));  
      if (server.argName(i) == "time_fan_stop") config.timeFanStop = timeToString(server.arg(i));
 

    }
     
    WriteConfig();
  
  }
  server.send_P ( 200, "text/html", PAGE_Temperature ); 
  Serial.println(__FUNCTION__); 
  
}


