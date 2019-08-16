//**************************************************************
//****Function to Read the BME1&2 Sensors and report to LCD****
//**************************************************************
          
  void takeReadingBME280(){

  unsigned long TR_currentMillis = millis();
  if (TR_currentMillis - TR_previousMillis > TR_interval) {
  TR_previousMillis = TR_currentMillis;  
  
  if (avgCounterBME == 20) {
     //Read BME280-1 Sensor
     //Serial.print("reading BME 1  avgCounterBME = ");
     //Serial.println(avgCounterBME);

     humidityBME1 = bme1.readHumidity();
     temperatureBME1 = ((bme1.readTemperature() *1.8) + 32);   
     baropressBME1 = ((bme1.readPressure()) * 0.000295333727 );
    
     tempValuesBME1 = tempValuesBME1 + temperatureBME1;
     humidValuesBME1 = humidValuesBME1 + humidityBME1;
     bpValuesBME1 = bpValuesBME1 + baropressBME1;
     /*
     Serial.print("tempValues BME1= "); Serial.print(tempValuesBME1);
     Serial.print(" humidValues BME1= "); Serial.print(humidValuesBME1);
     Serial.print(" avgCounter BME1= "); Serial.print(avgCounterBME);
     Serial.print(" temp BME1= "); Serial.print(temperatureBME1);
     Serial.print(" humidity BME1= "); Serial.println(humidityBME1);
  */
     avgTempBME1 = tempValuesBME1 / (avgCounterBME);
     avgHumidBME1 = humidValuesBME1 / (avgCounterBME); 
     avgBpBME1 = bpValuesBME1 / (avgCounterBME);
     /*
     Serial.print("**Average Temperature BME1= "); Serial.print(avgTempBME1);
     Serial.print(" Average Humidity BME1= "); Serial.print(avgHumidBME1);
     Serial.print(" avgCounterBME= "); Serial.print(avgCounterBME);
     Serial.print(" temp BME1= "); Serial.print(temperatureBME1);
     Serial.print(" humidity BME1= "); Serial.println(humidityBME1);
    */
     tempValuesBME1 = 0.0;
     humidValuesBME1 = 0.0;
     bpValuesBME1 = 0.0;

     //BME2
     //Serial.print("reading BME 2  avgCounterBME = ");Serial.println(avgCounterBME);

     humidityBME2 = bme2.readHumidity();
     temperatureBME2 = ((bme2.readTemperature() * 1.8) + 32);   
    
     lcd.setCursor(0, 1); lcd.print("T:"); lcd.print(temperatureBME2, 1); lcd.print((char)223);              
     lcd.print("F "); lcd.print("H:"); lcd.print(humidityBME2, 1);lcd.print("%");
     
     humidValuesBME2=humidValuesBME2 + humidityBME2;  // Sum accumulation for average calculation
     tempValuesBME2=tempValuesBME2 + temperatureBME2; // Sum accumulation for average calculation
    /*
     Serial.print("  tempValues BME2= "); Serial.print(tempValuesBME2);
     Serial.print(" humidValues BME2= "); Serial.print(humidValuesBME2);
     Serial.print(" avgCounterBME= "); Serial.print(avgCounterBME);
     Serial.print(" temp BME2= "); Serial.print(temperatureBME2);
     Serial.print(" humidity BME2= "); Serial.println(humidityBME2);
*/
     avgHumidBME2 = humidValuesBME2 / (avgCounterBME); // Compute Average Humidity
     avgTempBME2 = tempValuesBME2 / (avgCounterBME);   // Compute Average Temperature
     
     /*
     Serial.print("**Average Temperature BME2= "); Serial.print(avgTempBME2);
     Serial.print(" Average Humidity BME2= "); Serial.print(avgHumidBME2);
     Serial.print(" avgCounterBME= "); Serial.print(avgCounterBME);
     Serial.print(" temp BME2= "); Serial.print(temperatureBME2);
     Serial.print(" humidity BME2= "); Serial.println(humidityBME2);
     
     serialSDprintBME1();   //Run Function to Write Data to Serial Monitor & SD card
     serialSDprintBME2();   //Run Function to Write Data to Serial Monitor & SD card
    */
     //Write averages to THINGSPEAK
     
     writeThingSpeak();
     
     tempValuesBME2 = 0.0;  //Zero out accumulator for next average
     humidValuesBME2 = 0.0;  //Zero out accumulator for next average
     avgCounterBME = 1;    //Zero out accumulator for next average
     }
  else
     {
  //BME1
     //Read BME280-1

     //Serial.print("reading BME 1  avgCounterBME = "); Serial.println(avgCounterBME);

     humidityBME1 = bme1.readHumidity();
     temperatureBME1 = ((bme1.readTemperature() * 1.8) + 32);   
     baropressBME1 = ((bme1.readPressure()) * 0.000295333727 );

     //Accumulate for average calculation
     tempValuesBME1=tempValuesBME1 + temperatureBME1;
     humidValuesBME1=humidValuesBME1 + humidityBME1;
     bpValuesBME1 = bpValuesBME1 + baropressBME1;

mlr0 = numericalDate + timeF + mlr02 + temperatureBME1 + char(223) + mlr03 + humidityBME1 + mlr04 + baropressBME1 + mlr05;
     
    /*
     Serial.print("tempValues BME1= "); Serial.print(tempValuesBME1);
     Serial.print(" humidValues BME1= "); Serial.print(humidValuesBME1);
     Serial.print(" avgCounterBME= "); Serial.print(avgCounterBME);
     Serial.print(" temp BME1= "); Serial.print(temperatureBME1);
     Serial.print(" humidity BME1= "); Serial.println(humidityBME1);
*/
  //BME2
     //Read BME280 #2 
     //Serial.print("reading BME 2  avgCounterBME = "); Serial.println(avgCounterBME);

     humidityBME2 = bme2.readHumidity();
     temperatureBME2 = ((bme2.readTemperature() * 1.8) + 32);
    
     lcd.setCursor(0, 1);               //Display readings on LCD (position 0, line 2)
     lcd.print("T:"); 
     lcd.print(temperatureBME2, 1);
     lcd.print((char)223);              //Degree symbol
     lcd.print("F ");
     lcd.print("RH:");
     lcd.print(humidityBME2, 1);
     lcd.print("%");
     
     humidValuesBME2 = humidValuesBME2 + humidityBME2;  // Sum accumulation for average calculation
     tempValuesBME2 = tempValuesBME2 + temperatureBME2; // Sum accumulation for average calculation
    /*
     Serial.print("  tempValues BME2= "); Serial.print(tempValuesBME2);
     Serial.print(" humidValues BME2= "); Serial.print(humidValuesBME2);
     Serial.print(" avgCounterBME= "); Serial.print(avgCounterBME);
     Serial.print(" temp BME2= "); Serial.print(temperatureBME2);
     Serial.print(" humidity BME2= "); Serial.println(humidityBME2);
     */
      avgCounterBME = avgCounterBME + 1; //Increment the Average Counter
     }
   }
 }

//**************************************************************
//**END Function to Read the BME1&2 Sensor and report to LCD**
//**************************************************************


//*****************************************************************
//**Function to Write BME1 Averages to Serial Monitor**
//*****************************************************************     
void serialSDprintBME1(){
     getNTC_Time();
     Serial.print("*BME1* ");
     Serial.print("Date: "); Serial.print(date); Serial.print(", Time: "); Serial.print(timeF); Serial.print("  ");
     Serial.print(avgTempBME1); Serial.print(", "); Serial.println(avgHumidBME1); 
     }
//**************************************************************
//*END Function to BME1 Write Averages to Serial Monitor*
//**************************************************************


//*****************************************************************
//**Function to Write BME2 Averages to Serial Monitor **
//*****************************************************************      
void serialSDprintBME2(){
     
     Serial.print("*BME2* ");
     Serial.print("Date: "); Serial.print(date); Serial.print(", Time: "); Serial.print(timeF);Serial.print("  ");
     Serial.print(timeDateComma); Serial.print(avgTempBME2); Serial.print(", "); Serial.println(avgHumidBME2);
             
     }
//*****************************************************************
//**END Function to Write BME2 Averages to Serial Monitor**
//***************************************************************** 
