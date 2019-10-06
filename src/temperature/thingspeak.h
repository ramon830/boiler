//==========================================================
//****Стан реле  в thingspeak.com


byte modeRelayToNumber()
{
    byte s = 0;
    if (relaySmallroomOn)
        s += 2;
    if (relayBedroomOn)
        s += 4;
    return s;
}



//==========================================================
//****Записуємо дані в thingspeak.com
void writeToInternet()
{
    if (!isCorrectTemperature())
    {
        return;
    }
    Debug.print("connecting to ");
    Debug.println(hostThingSpeak);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(hostThingSpeak, httpPort))
    {
        Debug.println("connection failed");
        Debug.println();
        Debug.println();
        Debug.println();
        return;
    }
    Debug.println("connected -)");
    Debug.println("");
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
    url += "&field7=";
    url += (String)(relayBoilerOn ? 1 : 0);

    Debug.print("Requesting URL: ");
    Debug.print(hostThingSpeak);
    Debug.println(url);

    // отправляем запрос на сервер
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + hostThingSpeak + "\r\n" +
                 "Connection: close\r\n\r\n");
    client.flush(); // ждем отправки всех данных

    // Read all the lines of the reply from server and print them to Serial
    while (client.available())
    {
        String line = client.readStringUntil('\r');
        //char line = client.read();
        Debug.print(line);
    }

    Debug.println();
    Debug.println("closing connection");
    Debug.println();
}