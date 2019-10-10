//==========================================================
//**** Запит до сервера погоди 
bool httpRequest()
{
  HTTPClient client;
  bool find = false;
  Debug.printf("Connecting ");
  client.begin("http://narodmon.ru/api/sensorsOnDevice?id=8819&uuid=9adbe0b3033881f88ebd825bcf763b43&api_key=Rd3cGZdSAwPz8");
  client.setTimeout(1000);
  int httpCode = client.GET();
  if (httpCode > 0)
  {

    Debug.printf("successfully, code: %d\n", httpCode);
    if (httpCode == HTTP_CODE_OK)
    {
      httpData = client.getString();
      if (httpData.indexOf("name") > -1)
      {
        find = true;
      }
      else
        Debug.println("Failed, json string is not found");
    }
  }
  else
    Debug.printf("failed, error: %s\n", client.errorToString(httpCode).c_str());

  //postingInterval = find ? 600L * 1000L : 60L * 1000L;
  client.end();

  return find;
}

//==========================================================
//**** Парсем відповідь 
bool parseData()
{
  Debug.println(httpData);

  DynamicJsonBuffer jsonBuffer;
  JsonObject &root = jsonBuffer.parseObject(httpData);

  if (!root.success())
  {
    Debug.println("Json parsing failed!");
    return false;
  }
  Oweather.temp = root["sensors"][0]["value"];
  //Debug.println(Oweather.temp);
  httpData = "";
  return true;
}

// =======================================================================
//**** Приймаємо данні про погоду з народного монітору
void getWeatherData()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    httpRequest();
    parseData();
  }

}

