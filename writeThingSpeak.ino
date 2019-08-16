//**************************************************************
//***************Function to Write ThingSpeak*******************
//**************************************************************
void writeThingSpeak() {
  
  getNTC_Time();
  
  checkWiFi();

   /*
  //Serial.println("void thingspeak");
  //Serial.println(" ");

 if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi CONNECTED");
  }
  if (WiFi.status() == WL_IDLE_STATUS) {
    Serial.println("WiFi WL_IDLE_STATUS");
  }
  if (WiFi.status() == WL_CONNECTION_LOST) {
    Serial.println("WiFi WL_CONNECTION_LOST");
  }
  if (WiFi.status() == WL_CONNECT_FAILED) {
    Serial.println("WiFi WL_CONNECT_FAILED");
  }
  if (WiFi.status() == WL_DISCONNECTED) {
    Serial.println("WiFi WL_DISCONNECTED");
  }
  
  //Serial.println(" ");
  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
  Serial.print("Attempting to connect to ssid: "); Serial.println(ssid);
  while(WiFi.status() != WL_CONNECTED){
  WiFi.begin(ssid, password);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
  Serial.print(".");
  delay(1000);     
    } 
  //Serial.println("Connected.");
    }
    */
  //Serial.println("At setting TS fields");
  // set the fields with the values
  ThingSpeak.setField(1,timeF); //Time
  ThingSpeak.setField(2,date); //Date
  ThingSpeak.setField(3,avgTempBME1); //Ambient T
  ThingSpeak.setField(4,avgHumidBME1); //Ambient Rh
  ThingSpeak.setField(5,avgTempBME2); //HC T
  ThingSpeak.setField(6,avgHumidBME2); //HC Rh
  ThingSpeak.setField(7,avgBpBME1); //BP Ambient
  
  // write to the ThingSpeak channel
  //Serial.println("at TS writeFields"); Serial.println(" ");

  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  
  if(x == 200){
    Serial.println("Thingspeak update successful.");
    y = 0;
  }
  else{
    y++;
    lcd.clear();
    lcd.setCursor(0,2); lcd.print("Problem updating TS ");
    lcd.setCursor(0,3); lcd.print("HTTP error: "); lcd.print(String(x));
    delay(3000);
    Serial.println("@@@@@@@@@@@@@@@@ Problem updating channel. HTTP error code @@@@@@@@@@@@@@@@@" + String(x)); Serial.println();
    if (y=10){
      while(0);
    }
  }
//Serial.println();
Serial.println(mlr0);
Serial.println(segmentDSR2);
Serial.println(segmentDSR3);
Serial.println();
}

//**************************************************************
//***********END Function to Write ThingSpeak*******************
//**************************************************************
