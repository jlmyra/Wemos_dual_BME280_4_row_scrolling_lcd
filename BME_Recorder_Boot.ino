//**************************************************************
//************* Function void bme280RecorderBoot()**************
//**************************************************************

void bme280RecorderBoot() {

//Greeting
  
  Serial.println(F("***Hello!!!***"));
  Serial.println();
  Serial.println(F("I'm awake"));
  Serial.println();
  lcd.init();
  lcd.backlight();
  lcd.begin(screenWidth,screenHeight);     //initialize the lcd
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("     Hello!     "));
  lcd.setCursor(0, 1);
  lcd.print(F("   I'm awake"));
  delay(2000);

//
//Check BME 280 Sensors connectivity - if not connected-reboot
//
  Serial.println();
  Serial.println(F("Checking Multi Bosch BME280 Barometric Pressure-Humidity-Temp Sensors")); 

  if (!bme1.begin(0x76))
  {
   Serial.println(F("Could not find a First BME280 sensor, check wiring!"));
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print(F("BME1 wiring error"));
   delay(3000);
   while (1);  //infinite loop and crash, restart
  }
  if (!bme2.begin(0x77)) 
  {
   Serial.println(F("Could not find a Second BME280 sensor, check wiring!"));
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("BME2 wiring error");
   delay(3000);
   while (1); //infinite loop and crash, restart
  }
   Serial.println(F("BME-1 and BME-2 are connected")); 
   Serial.println();
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print(F("BME1 Responding"));
   lcd.setCursor(0, 1);
   lcd.print(F("BME2 Responding"));
   delay(2000);

  //Connect to WiFi and Report Status

  lcd.clear();
  lcd.setCursor(0, 0);

  int x = 0;
    if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to wifi: "); Serial.println(ssid);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("  Attempting WiFi   "));
    lcd.setCursor(0,1);
    lcd.print(F("     connection     "));
    
    x = 1; //Connection attempt counter
    
   if (WiFi.status() == WL_IDLE_STATUS) {
    Serial.println("WiFi WL_IDLE_STATUS");
    lcd.setCursor(0,3);
    lcd.print("WiFi WL_IDLE_STATUS");
  }
  if (WiFi.status() == WL_CONNECTION_LOST) {
    Serial.println("WiFi WL_CONNECTION_LOST");
    lcd.setCursor(0,3);
    lcd.print("WiFi WL_CONNECTION_LOST");
  }
  if (WiFi.status() == WL_CONNECT_FAILED) {
    Serial.println("WiFi WL_CONNECT_FAILED");
    lcd.setCursor(0,3);
    lcd.print("WiFi WL_CONNECT_FAILED");
  }
  if (WiFi.status() == WL_DISCONNECTED) {
    Serial.println("WiFi WL_DISCONNECTED");
    lcd.setCursor(0,3);
    lcd.print("WiFi WL_DISCONNECTED");
  }
    while(WiFi.status() != WL_CONNECTED){
      if ( x == 21) {
        while (1);  //If it doesn't connect in 20 tries - reboot
        }
    lcd.setCursor(0,2);
    lcd.print("attempt: ");
    lcd.print(" ");
    delay(500); 
    lcd.setCursor(10,2);
    lcd.print(x);
    delay(1000);
    
    Serial.print(x); 
    x = x + 1;    
      } 
    }
    
  if(x>0){
  Serial.println();
  }
   //Connected to WiFi - display connection info
  if(WiFi.status() == WL_CONNECTED) {
    Serial.print("WiFi CONNECTED; ");
  }

  Serial.println();  
  Serial.print("WiFi IP Address: "); Serial.println(WiFi.localIP());
  Serial.print("ESP8266 MAC: "); Serial.println(WiFi.macAddress());
  //long rssi = WiFi.RSSI();
  Serial.print("RSSI Signal Strength= "); Serial.println(WiFi.RSSI());
  
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi connected");
    lcd.setCursor(0,1); lcd.print("IP= "); lcd.print(WiFi.localIP());
    lcd.setCursor(0,2); lcd.print(WiFi.macAddress());
    lcd.setCursor(0,3); lcd.print("RSSI= "); lcd.print(WiFi.RSSI());

    delay(3000);
    
    lcd.clear();

//Display the current time from NTP Server

    Serial.println("Check time from the NTP Server");
    
    getNTC_Time(dateArr, numericalDate, timeF);
    
      // Send time and date to serial monitor
    Serial.print("");
    Serial.print("Time: "); Serial.println(timeF);
    Serial.print("Date: ");
    //for (int i = 0; i <= 23; i++){
      //Serial.print(dateArr[i]);  
      Serial.print(dateArrPtr);
    //}
      Serial.println();
    //Serial.println(dateArrPtr);

    // Display time and date on the 20x4 LCD
    lcd.setCursor(0, 0);
    lcd.print(timeF);
    lcd.setCursor(0, 1);
    //for (int i = 0; i <= 23; i++){
      //lcd.print(dateArr[i]);
      lcd.print(dateArrPtr);  
    //}
    
    //lcd.print(dateArr);
    delay(3000);
    lcd.clear();

     Serial.println();
     lcd.setCursor(0, 3);             
     lcd.print("**Get Dark Sky Upd**");
     
     getDarkSky(row2, row3);  // call the getDarkSky function and pass row2 and row3 array data which is 0 now.
     
     Serial.println();
  }

//**************************************************************
//**********END Function void bme280RecorderBoot()**************
//**************************************************************
