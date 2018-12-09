//
//   The HTML PAGE
//
const char PAGE_NTPConfiguration[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<a href="/admin"  class="btn btn--s"><</a>&nbsp;&nbsp;<strong>Налаштування часу</strong>
<hr>
<form action="" method="get">
<table border="0"  cellspacing="0" cellpadding="3" >
<tr><td align="right">NTP сервер:</td><td><input type="text" id="ntpserver" name="ntpserver" maxlength="172" value=""></td></tr>
<tr><td align="right">Обновляти кожні:</td><td><input type="text" id="update" name="update" size="3"maxlength="6" value=""> хвилин</td></tr>
<tr><td>Час. пояс</td><td>
<select  id="tz" name="tz">
  <option value="-120">(GMT-12:00)</option>
  <option value="-110">(GMT-11:00)</option>
  <option value="-100">(GMT-10:00)</option>
  <option value="-90">(GMT-09:00)</option>
  <option value="-80">(GMT-08:00)</option>
  <option value="-70">(GMT-07:00)</option>
  <option value="-60">(GMT-06:00)</option>
  <option value="-50">(GMT-05:00)</option>
  <option value="-40">(GMT-04:00)</option>
  <option value="-35">(GMT-03:30)</option>
  <option value="-30">(GMT-03:00)</option>
  <option value="-20">(GMT-02:00)</option>
  <option value="-10">(GMT-01:00)</option>
  <option value="0">(GMT+00:00)</option>
  <option value="10">(GMT+01:00)</option>
  <option value="20">(GMT+02:00)</option>
  <option value="30">(GMT+03:00)</option>
  <option value="35">(GMT+03:30)</option>
  <option value="40">(GMT+04:00)</option>
  <option value="45">(GMT+04:30)</option>
  <option value="50">(GMT+05:00)</option>
  <option value="55">(GMT+05:30)</option>
  <option value="57">(GMT+05:45)</option>
  <option value="60">(GMT+06:00)</option>
  <option value="65">(GMT+06:30)</option>
  <option value="70">(GMT+07:00)</option>
  <option value="80">(GMT+08:00)</option>
  <option value="90">(GMT+09:00)</option>
  <option value="95">(GMT+09:30)</option>
  <option value="100">(GMT+10:00)</option>
  <option value="110">(GMT+11:00)</option>
  <option value="120">(GMT+12:00)</option>
  <option value="120">(GMT+12:00)</option>
  <option value="130">(GMT+13:00)</option>
</select>
</td></tr>
<tr><td align="right">Літній час:</td><td><input type="checkbox" id="dst" name="dst"></td></tr>
<tr><td align="right">Встановити дату:</td><td><input type="date" id="date" name="date" value=""></td></tr>
<tr><td align="right">Встановити час:</td><td><input type="time" id="time" name="time" value=""></td></tr>
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
        setValues("/admin/ntpvalues");
    });
  });
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}
</script>
)=====";


// =======================================================================
//**** Вставляння дати в html код
String getDateValuesHtml() {
  String values ="";
  values += (String)DateTime.year +(String)"-";
    if ((int) DateTime.month <10) {
      values += "0"+ (String)DateTime.month; 
    } else {
      values += (String)DateTime.month; 
    }
    values += "-";
    if ((int) DateTime.day <10) {
      values += "0"+ (String)DateTime.day; 
    } else {
      values += (String)DateTime.day; 
    }
  return values;
}

// =======================================================================
//**** Вставляння часу в html код
String getTimeValuesHtml() {
  String values ="";
    if ((int) DateTime.hour <10) {
      values += "0"+ (String)DateTime.hour; 
    } else {
      values += (String)DateTime.hour; 
    }
    values += ":";
    if ((int) DateTime.minute <10) {
      values += "0"+ (String)DateTime.minute; 
    } else {
      values += (String)DateTime.minute; 
    }
  return values;
}

// =======================================================================
//****Конвертація дати і часу в long
void setDateTime(String _date, String _time) {
  
  
    String _day = (String)_date.charAt(8) + (String)_date.charAt(9);
    String _month = (String)_date.charAt(5) + (String)_date.charAt(6);
    String _year = (String)_date.charAt(0) + (String)_date.charAt(1)+ (String)_date.charAt(2)+ (String)_date.charAt(3);
    String _hour = (String)_time.charAt(0) + (String)_time.charAt(1);
    String _minute = (String)_time.charAt(3) + (String)_time.charAt(4);
    UnixTimestamp = 0;
    for (int i = 1970; i < _year.toInt(); i++) {
      if (LEAP_YEAR(i)) {
        UnixTimestamp += 366 * 24 * 60 *60;
      } else {
        UnixTimestamp += 365 * 24 * 60 *60;
      }
    }
    for (int i = 0; i < _month.toInt()-1; i++ ) {
        UnixTimestamp += monthDays[i] * 24 * 60 *60; 
    }
    for (int i = 1; i < _day.toInt(); i++ ) {
        UnixTimestamp += 24 * 60 *60; 
    }
    UnixTimestamp += _hour.toInt() * 3600 + _minute.toInt() * 60 - 3 *3600;
    DateTime = ConvertUnixTimeStamp(absoluteActualTime);
    server.send_P ( 200, "text/html", PAGE_NTPConfiguration ); 
   
  
}

// =======================================================================
//****Збереження часу
void send_NTP_configuration_html()
{
  if (server.args() > 0 )  // Save Settings
  {
    config.isDayLightSaving = false;
    String temp = "";
    String _date = "";
    String _time = "";
    for ( uint8_t i = 0; i < server.args(); i++ ) {
      if (server.argName(i) == "ntpserver") config.ntpServerName = urldecode( server.arg(i)); 
      if (server.argName(i) == "update") config.Update_Time_Via_NTP_Every =  server.arg(i).toInt(); 
      if (server.argName(i) == "tz") config.timeZone =  server.arg(i).toInt(); 
      if (server.argName(i) == "dst") config.isDayLightSaving = true; 
      if (server.argName(i) == "date") _date = server.arg(i);
      if (server.argName(i) == "time") _time = server.arg(i);
    }
    setDateTime(_date, _time); 
    WriteConfig();
  
  }
  server.send_P ( 200, "text/html", PAGE_NTPConfiguration ); 
    
}

// =======================================================================
//****Налаштування часу
void send_NTP_configuration_values_html()
{
    
  String values ="";
  values += "ntpserver|" + (String) config.ntpServerName + "|input\n";
  values += "update|" +  (String) config.Update_Time_Via_NTP_Every + "|input\n";
  values += "tz|" +  (String) config.timeZone + "|input\n";
  values += "dst|" +  (String) (config.isDayLightSaving ? "checked" : "") + "|chk\n";
  values += "date|" + getDateValuesHtml()  + "|input\n";
  values += "time|" + getTimeValuesHtml() + "|input\n";
  server.send ( 200, "text/plain", values);

}

