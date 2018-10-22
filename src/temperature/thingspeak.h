//==========================================================
//****Стан реле  в thingspeak.com
/*
б. спальні/ б. м. кімнати/ котел
000
001
010
011
100
101
110
111
*/
byte modeRelayToNumber() {
    byte s =0;
    if (relayBoilerOn) s+=1;
    if(relaySmallroomOn) s+=2;
    if(relayBedroomOn) s+=4;
    return s;
}

//==========================================================
//****Записуємо дані в thingspeak.com
void writeToInternet() {

Serial.print("connecting to ");
Serial.println(hostThingSpeak);

// Use WiFiClient class to create TCP connections
WiFiClient client;
const int httpPort = 80;
if (!client.connect(hostThingSpeak, httpPort)) {
Serial.println("connection failed");
Serial.println();
Serial.println();
Serial.println();
return;
}
Serial.println("connected -)");
Serial.println("");
// Создаем URI для запроса
String url = "/update?key=";
url += apikeyThingSpeak;
url += "&field1=";
    url += (String)getTemperatureFromFilter(smallRoom);
    url += "&field2=";
    url += (String)getTemperatureFromFilter(bedRoom);
    url += "&field3=";
    url += (String)getTemperatureFromFilter(radiatorSmallRoom);
    url += "&field4=";
    url += (String)getTemperatureFromFilter(radiatorBedRoom);
    url += "&field5=";
    url += (String)modeRelayToNumber();
    url += "&field6=";
    url += (String)(round(Oweather.temp) - 273.15);
    
Serial.print("Requesting URL: ");
Serial.print(hostThingSpeak);
Serial.println(url);



// отправляем запрос на сервер
client.print(String("GET ") + url + " HTTP/1.1\r\n" +
"Host: " + hostThingSpeak + "\r\n" +
"Connection: close\r\n\r\n");
client.flush(); // ждем отправки всех данных


// Read all the lines of the reply from server and print them to Serial
while(client.available()){
String line = client.readStringUntil('\r');
//char line = client.read();
Serial.print(line);
}

Serial.println();
Serial.println("closing connection");
Serial.println();
}