//==========================================================
//****Повертаємо час і дату
void getTime(){
  
    h = String (DateTime.hour/10) + String (DateTime.hour%10);
    
    m = String (DateTime.minute/10) + String (DateTime.minute%10);
    s = String (DateTime.second/10 + String (DateTime.second%10));

    d = String (DateTime.day);

    y = String (DateTime.year);
     
    if (DateTime.month == 1) mon = "Січня";
    if (DateTime.month == 2) mon = "Лютого";
    if (DateTime.month == 3) mon = "Березня";
    if (DateTime.month == 4) mon = "Квітня";
    if (DateTime.month == 5) mon = "Травня";
    if (DateTime.month == 6) mon = "Червня";
    if (DateTime.month == 7) mon = "Липня";
    if (DateTime.month == 8) mon = "Серпня";
    if (DateTime.month == 9) mon = "Вересняя";
    if (DateTime.month == 10) mon = "Жовтня";
    if (DateTime.month == 11) mon = "Листопада";
    if (DateTime.month == 12) mon = "Грудня";

    if (DateTime.wday == 2) wd = "Понеділок";
    if (DateTime.wday == 3) wd = "Вівторок";
    if (DateTime.wday == 4) wd = "Середа";
    if (DateTime.wday == 5) wd = "Четвер";
    if (DateTime.wday == 6) wd = "П'ятниця";
    if (DateTime.wday == 7) wd = "Субота";
    if (DateTime.wday == 1) wd = "Неділя";
    
}

//==========================================================
//****Перша синхронізація з NTP сервером
void firstGetNTPtime() {
    if(WiFi.status() == WL_CONNECTED && !firstConnectionNTP){
        getNTPtime();
        
    }
    if(firstConnectionNTP) {
        tickerScheduler.disable(2);
    }

}

//==========================================================
//****Дата і час перетворюється в символи
String printDateTime () {
    String dt = String (DateTime.day) + "." +
    String (DateTime.month) + "." +
    String (DateTime.year)+ " --- " +
    String (DateTime.hour/10) + String (DateTime.hour%10) + ":" +
    String (DateTime.minute/10) + String (DateTime.minute%10) + ":" +
    String (DateTime.second/10) + String (DateTime.second%10);
    
    return dt;
}
