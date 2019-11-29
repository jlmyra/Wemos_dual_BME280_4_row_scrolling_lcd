//**************************************************************
//****Function to Read the BME1&2 Sensors and report to LCD****
//**************************************************************
          
  void takeReadingBME280(char *row0Ptr, char *numericalDatePtr , char *timeFPtr){

  unsigned long TR_currentMillis = millis();
  if (TR_currentMillis - TR_previousMillis > TR_interval) {
  TR_previousMillis = TR_currentMillis;  
  
  if (avgCounterBME == 20) {
    
     //Read BME280-1 Sensor
     
     humidityBME1 = bme1.readHumidity();
     temperatureBME1 = ((bme1.readTemperature() *1.8) + 32);   
     baropressBME1 = ((bme1.readPressure()) * 0.000295333727 );
    
     tempValuesBME1 = tempValuesBME1 + temperatureBME1;
     humidValuesBME1 = humidValuesBME1 + humidityBME1;
     bpValuesBME1 = bpValuesBME1 + baropressBME1;
     
     avgTempBME1 = tempValuesBME1 / (avgCounterBME);
     avgHumidBME1 = humidValuesBME1 / (avgCounterBME); 
     avgBpBME1 = bpValuesBME1 / (avgCounterBME);
  
     tempValuesBME1 = 0.0;
     humidValuesBME1 = 0.0;
     bpValuesBME1 = 0.0;

     //BME2

     humidityBME2 = bme2.readHumidity();
     temperatureBME2 = ((bme2.readTemperature() * 1.8) + 32);   
    
     lcd.setCursor(0, 1); 
     lcd.print(F("T:")); 
     lcd.print(temperatureBME2, 1); 
     lcd.print((char)223);              
     lcd.print(F("F ")); 
     lcd.print(F("RH:")); 
     lcd.print(humidityBME2, 1);
     lcd.print(F("%"));
     
     humidValuesBME2=humidValuesBME2 + humidityBME2;  // Sum accumulation for average calculation
     tempValuesBME2=tempValuesBME2 + temperatureBME2; // Sum accumulation for average calculation

     avgHumidBME2 = humidValuesBME2 / (avgCounterBME); // Compute Average Humidity
     avgTempBME2 = tempValuesBME2 / (avgCounterBME);   // Compute Average Temperature
     
  //Write averages to THINGSPEAK
     
     writeThingSpeak(); //happens every 1 minutes 3000ms x 20 readings = 60000ms
     
     tempValuesBME2 = 0.0;  //Zero out accumulator for next average
     humidValuesBME2 = 0.0;  //Zero out accumulator for next average
     avgCounterBME = 1;    //Zero out accumulator for next average
      
  //Get DarkSky Counter - Every 5 write thingspeak get darksky
     
    gdsCounter = gdsCounter + 1;
    if (gdsCounter == 5){
      
    yield();
    
    getDarkSky(row2, row3); //**************get dark sky******************
    
    yield();
    gdsCounter = 0;
      
     }
    }
  else
    {
  //BME1
     //Read BME280-1

     humidityBME1 = bme1.readHumidity();
     temperatureBME1 = ((bme1.readTemperature() * 1.8) + 32);   
     baropressBME1 = ((bme1.readPressure()) * 0.000295333727 );

     //Accumulate for average calculation
     tempValuesBME1=tempValuesBME1 + temperatureBME1;
     humidValuesBME1=humidValuesBME1 + humidityBME1;
     bpValuesBME1 = bpValuesBME1 + baropressBME1;

  dtostrf(temperatureBME1, 3, 1, tempBME1ArrayPtr); //convert floats to arrays
  dtostrf(humidityBME1, 3, 1, humidBME1ArrayPtr);
  dtostrf(baropressBME1, 3, 1, baroPressBME1ArrayPtr);

  old_row0StrLen = strlen(row0Ptr);
  row0Ptr[0] = 0;
 
uint16_t dateTimeLen = strlen(timeFPtr) + strlen(numericalDatePtr);

for (unsigned int i = 0; i < strlen(numericalDatePtr); i++){
  row0Ptr[i] = numericalDatePtr[i];
}
for (unsigned int i = strlen(numericalDatePtr), j = 0; i < dateTimeLen && j < strlen(timeFPtr); i++, j++){
  row0Ptr[i] = timeFPtr[j]; 
}
for (int i = dateTimeLen, j = 0; (i < dateTimeLen + 10) && j < 10; i++, j++){
  row0Ptr[i] = ambT_Ptr[j]; 
}
for (int i = (dateTimeLen + 10), j = 0; (i < dateTimeLen + 14) && j < 4; i++, j++){
  row0Ptr[i] = tempBME1ArrayPtr[j]; 
}
for (int i = (dateTimeLen + 14), j = 0; (i < dateTimeLen + 15) && j < 1; i++, j++){
  row0Ptr[i] = degFPtr[j]; 
}
for (int i = (dateTimeLen + 15), j = 0; (i < dateTimeLen + 20) && j < 5; i++, j++){
  row0Ptr[i] = F_RH_Ptr[j]; 
}
for (int i = (dateTimeLen + 20), j = 0; (i < dateTimeLen + 24) && j < 4; i++, j++){
  row0Ptr[i] = humidBME1ArrayPtr[j]; 
}
for (int i = (dateTimeLen + 24), j = 0; (i < dateTimeLen + 29) && j < 5; i++, j++){
  row0Ptr[i] = perBP_Ptr[j]; 
}
for (int i = (dateTimeLen + 29), j = 0; (i < dateTimeLen + 33) && j < 4; i++, j++){
  row0Ptr[i] = baroPressBME1ArrayPtr[j]; 
}
for (int i = (dateTimeLen + 33), j = 0; (i < dateTimeLen + 38) && (j < 5); i++, j++){
  row0Ptr[i] = inHgSpPtr[j]; 
}
row0Ptr[dateTimeLen + 38] = ' ';
row0Ptr[dateTimeLen + 39] = 0;

new_row0StrLen = strlen(row0Ptr);

  //BME2
     //Read BME280 #2 and display on LCD row 1

     humidityBME2 = bme2.readHumidity();
     temperatureBME2 = ((bme2.readTemperature() * 1.8) + 32);
    
     lcd.setCursor(0, 1);               //Display readings on LCD (position 0, row 1 or line 2)
     lcd.print(F("T:")); 
     lcd.print(temperatureBME2, 1);
     lcd.print((char)223);              //Degree symbol
     lcd.print(F("F "));
     lcd.print(F("RH:"));
     lcd.print(humidityBME2, 1);
     lcd.print(F("%"));
     
     humidValuesBME2 = humidValuesBME2 + humidityBME2;  // Sum accumulation for average calculation
     tempValuesBME2 = tempValuesBME2 + temperatureBME2; // Sum accumulation for average calculation
   
     avgCounterBME = avgCounterBME + 1; //Increment the Average Counter
     }
   }
  }
 
//**************************************************************
//**END Function to Read the BME1&2 Sensor and report to LCD**
//**************************************************************
