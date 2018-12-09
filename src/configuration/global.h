#define MonitorSpeed 9600
#define EEPROMSize 512
#define bedRoom "28aa1c1018130282"  //Спальня
#define smallRoom "288885ac1f130105"  //Дитяча кімната
#define radiatorBedRoom "28aa35c917130244"  //Батарея спальня
#define radiatorSmallRoom "284a3bb71f1301b5" //Батарея мала кімната	

ESP8266WebServer server(80);              // Веб сервер
struct strConfig {
  boolean dhcp;                         // 1 Byte - EEPROM 16 
  boolean isDayLightSaving;             // 1 Byte - EEPROM 17
  long Update_Time_Via_NTP_Every;       // 4 Byte - EEPROM 18
  long timeZone;                        // 4 Byte - EEPROM 22
  byte  IP[4];                          // 4 Byte - EEPROM 32
  byte  Netmask[4];                     // 4 Byte - EEPROM 36
  byte  Gateway[4];                     // 4 Byte - EEPROM 40
  byte  DNS[4];                         // 4 Byte - EEPROM 44
  String ssid;                          // up to 32 Byte - EEPROM 64
  String password;                      // up to 32 Byte - EEPROM 96
  String ntpServerName;                 // up to 32 Byte - EEPROM 128
  String OpenWeatherKey;                // up to 32 Byte - EEPROM 160
  String OpenWeatherCityId;             // up to 32 Byte - EEPROM 192
  byte relayBoiler;                     // 1 Byte - EEPROM 224
  byte relaySmallroom;                  // 1 Byte - EEPROM 225
  byte relayBedroom;                    // 1 Byte - EEPROM 226
  float nightTemperature;               // 4 Byte - EEPROM 227
  float nightGiterezis;                 // 4 Byte - EEPROM 231
  int timeNightStart;                   // 2 Byte - EEPROM 235
  int timeNightStop;                    // 2 Byte - EEPROM 237   

  float dayTemperature;                 // 4 Byte - EEPROM 239
  float dayGiterezis;                   // 4 Byte - EEPROM 243
  int timeDayStart;                     // 2 Byte - EEPROM 247
  int timeDayStop;                      // 2 Byte - EEPROM 249     

  float eveningTemperature;             // 4 Byte - EEPROM 251
  float eveningGiterezis;               // 4 Byte - EEPROM 255
  int timeEveningStart;                 // 2 Byte - EEPROM 259
  int timeEveningStop;                  // 2 Byte - EEPROM 261     

  float sundayTemperature;              // 4 Byte - EEPROM 263
  float sundayGiterezis;                // 4 Byte - EEPROM 267
  int timeSundayStart;                  // 2 Byte - EEPROM 271
  int timeSundayStop;                   // 2 Byte - EEPROM 273     

  float fanTemperature;                 // 4 Byte - EEPROM 275
  float fanGiterezis;                   // 4 Byte - EEPROM 279
  int timeFanStart;                     // 2 Byte - EEPROM 283
  int timeFanStop;                      // 2 Byte - EEPROM 285

  float morningTemperature;              // 4 Byte - EEPROM 287
  float morningGiterezis;                // 4 Byte - EEPROM 291
  int timeMorningStart;                  // 2 Byte - EEPROM 295
  int timeMorningStop;                   // 2 Byte - EEPROM 297
  
} config;
boolean relayBoilerOn = false;                     // Реле котла
boolean relaySmallroomOn = false;                  // Реле вентилятора малої кімнати
boolean relayBedroomOn = false;                    // Реле вентилятора спальні
TickerScheduler tickerScheduler(7);     // Планувальник задач
boolean firstConnectionNTP = false;			// Перше обновлення Datetime Structure
//int AdminTimeOutCounter = 0;            // Лічильник для вимкнення адміністративного режиму
//boolean firstStart = true;              // Перший старт = true, NTP отримуємо час
long  customWatchdog;                   // WatchDog для виявлення блокування основного циклу. Вбудований WatchDog - це вбудоване програмне забезпечення
long absoluteActualTime, actualTime;
WiFiUDP UDPNTPClient;
volatile unsigned long UnixTimestamp = 0;  // Глобальний час
//int cNTP_Update = 0;                      // Лічильник для оновлення часу через NTP
String y;     // рік
String mon;   // місяць
String wd;    // день тижня
String d;     // день
String h;     // години
String m;     // хвилини
String s;     // секунди

String weatherHost = "api.openweathermap.org"; //Адрес сервера погоди
//HTTPClient client;
String weatherDescription = "";
String weatherLocation = "";
float OpenWeatherTemp;
int OpenWeatherHumidity;
int OpenWeatherPressure;
float OpenWeatherWindSpeed;
int OpneWeatherWindDeg;
int OpenWeatherClouds;
String OpenWeatherWeatherString;

struct weather_structure {
  unsigned int id;
  const char* main;
  const char* icon;
  const char* descript;
  float temp;
  float pressure;
  byte  humidity;
  float speed;
  float deg;
} Oweather;
String httpData;

#define ONE_WIRE_BUS D5 //Пін вимірювання температури
#define ONE_WIRE_MAX_DEV 4 //Максимальне число термометрів
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
int numberOfDevices; //Число знайдених пристроїв
DeviceAddress devAddr[ONE_WIRE_MAX_DEV];  //Масив термометрів
float tempDev[ONE_WIRE_MAX_DEV]; //Масив температур
struct Temperature_struct {
String address;
float temperature;
} tempArray[ONE_WIRE_MAX_DEV];  //Масив температур

const char* hostThingSpeak = "api.thingspeak.com"; //Адрес для передачі данних
const char* apikeyThingSpeak="X7AJ51P6BMPP2MMJ"; // ключ від thingsspeak.com

#define HOST_NAME "spirit"
RemoteDebug Debug;
 
//==========================================================
//****Записуємо числа типу String
void WriteStringToEEPROM(int beginaddress, String string){
  char  charBuf[string.length() + 1];
  string.toCharArray(charBuf, string.length() + 1);
  for (int t =  0; t < sizeof(charBuf); t++)
  {
    EEPROM.write(beginaddress + t, charBuf[t]);
  }
}

//==========================================================
//****Читаємо числа типу String
String  ReadStringFromEEPROM(int beginaddress) {
  volatile byte counter = 0;
  char rChar;
  String retString = "";
  while (1)
  {
    rChar = EEPROM.read(beginaddress + counter);
    if (rChar == 0) break;
    if (counter > 31) break;
    counter++;
    retString.concat(rChar);
  }
  return retString;
}


//==========================================================
//****Читаємо числа типу long
long EEPROMReadlong(long address) {
  //Read the 4 bytes from the eeprom memory.
  long four = EEPROM.read(address);
  long three = EEPROM.read(address + 1);
  long two = EEPROM.read(address + 2);
  long one = EEPROM.read(address + 3);
  return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) +
    ((one << 24) & 0xFFFFFFFF);
}

//==========================================================
//****Записуємо числа типу long
void EEPROMWritelong(int address, long value){
  byte four = (value & 0xFF);
  byte three = ((value >> 8) & 0xFF);
  byte two = ((value >> 16) & 0xFF);
  byte one = ((value >> 24) & 0xFF);

  //Write the 4 bytes into the eeprom memory.
  EEPROM.write(address, four);
  EEPROM.write(address + 1, three);
  EEPROM.write(address + 2, two);
  EEPROM.write(address + 3, one);
}

//==========================================================
//****Читаємо числа типу float
float EEPROM_float_read(int addr) {    
  byte raw[4];
  for(byte i = 0; i < 4; i++) raw[i] = EEPROM.read(addr+i);
  float &num = (float&)raw;
  return num;
}

//==========================================================
//****Записуємо числа типу float
void EEPROM_float_write(int addr, float num) {
  byte raw[4];
  (float&)raw = num;
  for(byte i = 0; i < 4; i++) EEPROM.write(addr+i, raw[i]);
}

//==========================================================
//****Читаємо числа типу int
unsigned int EEPROMReadInt(int p_address)
        {
        byte lowByte = EEPROM.read(p_address);
        byte highByte = EEPROM.read(p_address + 1);

        return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
        }


//==========================================================
//****Записуємо числа типу int
void EEPROMWriteInt(int p_address, int p_value)
        {
        byte lowByte = ((p_value >> 0) & 0xFF);
        byte highByte = ((p_value >> 8) & 0xFF);

        EEPROM.write(p_address, lowByte);
        EEPROM.write(p_address + 1, highByte);
        }


//==========================================================
//****Записуємо конфігурацію
void WriteConfig(){

  Debug.println("Writing Config");
  EEPROM.write(0, 'C');
  EEPROM.write(1, 'F');
  EEPROM.write(2, 'G');

  EEPROM.write(16, config.dhcp);
  EEPROM.write(17, config.isDayLightSaving);

  EEPROMWritelong(18, config.Update_Time_Via_NTP_Every); // 4 Byte
  EEPROMWritelong(22, config.timeZone); // 4 Byte

  EEPROM.write(32, config.IP[0]);
  EEPROM.write(33, config.IP[1]);
  EEPROM.write(34, config.IP[2]);
  EEPROM.write(35, config.IP[3]);

  EEPROM.write(36, config.Netmask[0]);
  EEPROM.write(37, config.Netmask[1]);
  EEPROM.write(38, config.Netmask[2]);
  EEPROM.write(39, config.Netmask[3]);

  EEPROM.write(40, config.Gateway[0]);
  EEPROM.write(41, config.Gateway[1]);
  EEPROM.write(42, config.Gateway[2]);
  EEPROM.write(43, config.Gateway[3]);

  EEPROM.write(44, config.DNS[0]);
  EEPROM.write(45, config.DNS[1]);
  EEPROM.write(46, config.DNS[2]);
  EEPROM.write(47, config.DNS[3]);

  WriteStringToEEPROM(64, config.ssid);
  WriteStringToEEPROM(96, config.password);
  WriteStringToEEPROM(128, config.ntpServerName);
  WriteStringToEEPROM(160, config.OpenWeatherKey);
  WriteStringToEEPROM(192, config.OpenWeatherCityId);

  EEPROM.write(224, config.relayBoiler);                     
  EEPROM.write(225, config.relaySmallroom);                 
  EEPROM.write(226, config.relayBedroom);  

  EEPROM_float_write(227, config.nightTemperature);
  EEPROM_float_write(231, config.nightGiterezis);
  EEPROMWriteInt(235,config.timeNightStart);
  EEPROMWriteInt(237, config.timeNightStop);

  EEPROM_float_write(239, config.dayTemperature);
  EEPROM_float_write(243, config.dayGiterezis);
  EEPROMWriteInt(247,config.timeDayStart);
  EEPROMWriteInt(249, config.timeDayStop);

  EEPROM_float_write(251, config.eveningTemperature);
  EEPROM_float_write(255, config.eveningGiterezis);
  EEPROMWriteInt(259,config.timeEveningStart);
  EEPROMWriteInt(261, config.timeEveningStop);

  EEPROM_float_write(263, config.sundayTemperature);
  EEPROM_float_write(267, config.sundayGiterezis);
  EEPROMWriteInt(271,config.timeSundayStart);
  EEPROMWriteInt(273, config.timeSundayStop);
   
  EEPROM_float_write(275, config.fanTemperature);
  EEPROM_float_write(279, config.fanGiterezis);
  EEPROMWriteInt(283,config.timeFanStart);
  EEPROMWriteInt(285, config.timeFanStop); 

  EEPROM_float_write(287, config.morningTemperature);
  EEPROM_float_write(291, config.morningGiterezis);
  EEPROMWriteInt(295,config.timeMorningStart);
  EEPROMWriteInt(297, config.timeMorningStop); 

    // Application Settings here... from EEPROM 299 up to 511 (0 - 511)

  EEPROM.commit();
}

//==========================================================
//**** Перетворення в шістнадцяткову систему
unsigned char h2int(char c){
  if (c >= '0' && c <= '9') {
    return ((unsigned char)c - '0');
  }
  if (c >= 'a' && c <= 'f') {
    return ((unsigned char)c - 'a' + 10);
  }
  if (c >= 'A' && c <= 'F') {
    return ((unsigned char)c - 'A' + 10);
  }
  return (0);
}  

//==========================================================
//**** Парсинг URL
String urldecode(String input) 
{
  char c;
  String ret = "";
  for (byte t = 0; t < input.length(); t++)
  {
    c = input[t];
    if (c == '+') c = ' ';
    if (c == '%')
    {
      t++;
      c = input[t];
      t++;
      c = (h2int(c) << 4) | h2int(input[t]);
    }
    ret.concat(c);
  }
  return ret;
}

//==========================================================
// Перевырка значення мыж 0-255
boolean checkRange(String Value){
  if (Value.toInt() < 0 || Value.toInt() > 255)
  {
    return false;
  }
  else
  {
    return true;
  }
}
