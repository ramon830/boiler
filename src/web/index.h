//
//   The HTML PAGE
//
const char PAGE_Index[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<link rel="stylesheet" href="style.css" type="text/css" />
<script src="microajax.js"></script> 
<a href="/admin"  class="btn btn--s"><</a>&nbsp;&nbsp;<strong>Мережева інформація</strong>
<hr>
<table border="0"  cellspacing="0" cellpadding="3" style="width:640px" >
<tr><td align="right">Дата :</td><td><span id="x_clock"></span></td></tr>
<tr><td align="center"><strong>Погода OpenWeatherMap</strong></td></tr>
<tr><td align="right">Температура на вулиці :</td><td><span id="temp_in"></span> &deg;С</td></tr>
<tr><td align="right">Тиск  :</td><td><span id="pressure"></span> мм рт.ст.</td></tr>
<tr><td align="right">Вологість :</td><td><span id="humidity"></span> %</td></tr>
<tr><td align="right">Швидкість вітру   :</td><td><span id="wind_speed"> </span>м/с</td></tr>
<tr><td align="right">Вітер :</td><td><span id="wind_direc"></span></td></tr>
<tr><td align="center"><strong>Температури</strong></td></tr>
<tr><td align="right">Мала кімната</td><td><span id="SmallRoom"></span> &deg;С</td></tr>
<tr><td align="right">Спальня</td><td><span id="BedRoom"></span> &deg;С</td></tr>
<tr><td align="right">Батарея малої кімнати</td><td><span id="RadiatorSmallRoom"> м/с</span> &deg;С</td></tr>
<tr><td align="right">Батарея спальні</td><td><span id="RadiatorBedRoom"></span> &deg;С</td></tr>
<tr><td align="center"><strong>Стан реле</strong></td></tr>
<tr><td align="right">Реле котла: </td><td><span id="relayBoilerOn"></span></td></tr>
<tr><td align="right">Реле вентилятора мал. кімнати: </td><td><span id="relaySmallroomOn"></span></td></tr>
<tr><td align="right">Реле вентилятора спальні: </td><td><span id="relayBedroomOn"></span></td></tr>

</table>
<script>

window.onload = function ()
{
  load("style.css","css", function() 
  {
    load("microajax.js","js", function() 
    {
        setInterval(function() {
            setValues("/admin/index-values");
        }, 1000)
        
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
//****Стан реле в текст
String relayOnToString(boolean relay) {
  if (relay) {
    return "Включено";
  } 
  return "Виключено";
}

// =======================================================================
//****Встановлюємо значення
void send_index_values_html() {
    String values ="";
    values += "x_clock|" + printDateTime() +  "|div\n";
    values += "temp_in|" + (String)(round(Oweather.temp) - 273.15) +  "|div\n";
    values += "pressure|" + (String)(round(Oweather.pressure * 0.75)) +  "|div\n";
    values += "humidity|" + (String)(round(Oweather.humidity))  +  "|div\n";
    values += "wind_speed|" + (String)(round(Oweather.speed))  +  "|div\n";
    values += "wind_direc|" + windDirection() +  "|div\n";

    values += "SmallRoom|" + (String)getTemperatureFromFilter(smallRoom)  +  "|div\n";
    values += "BedRoom|" + (String)getTemperatureFromFilter(bedRoom)   +  "|div\n";
    values += "RadiatorSmallRoom|" + (String)getTemperatureFromFilter(radiatorSmallRoom)   +  "|div\n";
    values += "RadiatorBedRoom|" + (String)getTemperatureFromFilter(radiatorBedRoom)  +  "|div\n";
    values += "relayBoilerOn|" + (String)relayOnToString(relayBoilerOn)  +  "|div\n";
    values += "relaySmallroomOn|" + (String)relayOnToString(relaySmallroomOn)  +  "|div\n";
    values += "relayBedroomOn|" + (String)relayOnToString(relayBedroomOn)  +  "|div\n";

  server.send ( 200, "text/plain", values);
  
}