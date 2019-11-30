//**************************************************************
//**************** Function void getDarkSky()******************
//**************************************************************

  void getDarkSky(char *row2Ptr, char *row3Ptr){
     
  int charCntL2A; //set up some containers for row2 and row3 character counts
  int charCntL3A;
  int charCntL3B;
  int charCntL3C;

  // Create the structures that hold the retrieved weather
  
  DSW_current *current = new DSW_current;
  DSW_hourly *hourly = new DSW_hourly;
  DSW_daily  *daily = new DSW_daily;
  DSW_minutely *minutely = new DSW_minutely;
  //minutely = nullptr; // extra
  
  old_row0StrLen = strlen(row0Ptr); //Keeps track of the LCD line character lengths. If they change the counters in
  old_row2StrLen = strlen(row2Ptr); // the moving letter functions have to be reset and the line restarted on the LCD
  old_row3StrLen = strlen(row3Ptr);

  Serial.println();
  Serial.print(F("###################################################################################"));
  Serial.println(F("###################################################################################"));
  Serial.println(F("Requesting weather information from DarkSky.net... "));

//yield(); //caused the sketch to stall here???
  
  //dsw.getForecast(current, hourly, daily, api_key, latitude, longitude, units, language);
  dsw.getForecast(current, minutely, hourly, daily, api_key, latitude, longitude, units, language);


  //Serial display of number of DarkSky accesses since last boot 
  Serial.println();
  Serial.println(F("#####################################################"));
  Serial.println(F("#####################################################"));
  Serial.println();
  
  GDSCounter = GDSCounter + 1;
  
  Serial.print(F("GDSCounter= ")); Serial.print (GDSCounter); Serial.print(F("  uptime minutes = ~")); Serial.print(float (GDSCounter*5)-5); 
  Serial.print(F("   uptime Hours = ~ ")); Serial.println(float (((GDSCounter*5)-5)/60));
  Serial.println();
  Serial.print(F("Free Heap= ")); Serial.println(ESP.getFreeHeap());
  Serial.print(F("Heap Fragmentation= ")); Serial.println(ESP.getHeapFragmentation());
  Serial.print(F("Max Free Block Size= ")); Serial.println(ESP.getMaxFreeBlockSize());
  
  Serial.println(F("#####################################################"));
  Serial.println(F("#####################################################"));
  Serial.println();
  Serial.print(F("###################################################################################"));
  Serial.println(F("###################################################################################"));
    
  Serial.println(F("Weather from Dark Sky\n"));

  // We can use the timezone to set the offset eventually...
  //Serial.print("Timezone            : "); Serial.println(current->timezone);
  
  Serial.println(F("############### Current weather ###############\n"));
  //Serial.print("Current time             : ")); Serial.println(timeF);
  Serial.print(F("Current time             : ")); Serial.print(strTime(current->time));
  Serial.print(F("Current summary          : ")); Serial.println(current->summary);
  Serial.print(F("Current precipInten      : ")); Serial.println(current->precipIntensity);
  //Serial.print("Current precipType       : ")); Serial.println(getMeteoconIcon(current->precipType));
  Serial.print(F("Current precipProbability: ")); Serial.println(current->precipProbability);
  Serial.print(F("Current temperature      : ")); Serial.println(current->temperature);
  Serial.print(F("Current humidity         : ")); Serial.println(current->humidity);
  Serial.print(F("Current pressure         : ")); Serial.println(current->pressure);
  Serial.print(F("Current wind speed       : ")); Serial.println(current->windSpeed);
  Serial.print(F("Current wind gust        : ")); Serial.println(current->windGust);
  Serial.print(F("Current wind dirn        : ")); Serial.println(current->windBearing);

  Serial.println();
  Serial.println(F("#####################################################"));
  Serial.println(F("#####################################################"));
  
//**********Build Row 2 Moving Letter line****************
//Here we build a character array for line 2 (0-3 lines) of the LCD via array pointers to minimize memory fragmentation.
//The array pointer row2Ptr uses row 2 array 'row[85]' to store the characters that will be scrolled on LCD row 2 
//note the array count goes from 0-n while the character count returned by strlen goes from 1-n.
  
  dtostrf((current->temperature), 4, 1, currTempArrayPtr); //convert floats to array pointers
  dtostrf((current->humidity), 3, 0, currHumidArrayPtr);
  dtostrf(current->windSpeed, 2, 0, currWindArrayPtr);
  dtostrf(current->precipProbability, 3, 0, currPreProbArrayPtr);

  for (uint16_t i = 0; i < 19; i++) //'Current Conditions:_' 20 characters
      {
      row2Ptr[i] = row2_segment1_Ptr[i]; //
      }

  charCntL2A = (hourly->summary[0]).length();

  for (uint16_t i = 19, j = 0; i < (charCntL2A + 19)  && j < charCntL2A; i++, j++) //Add Daily Summary to array
      {
      row2Ptr[i] = (hourly->summary[0])[j]; //
      }
      
  row2Ptr[charCntL2A + 19] = ' '; // Add '_T:' to array 
  row2Ptr[charCntL2A + 20] = 'T';
  row2Ptr[charCntL2A + 21] = ':';

  for (uint16_t i = charCntL2A + 22, j = 0; i < charCntL2A + 26  && j < 4; i++, j++) // Add Current Temperature to Array
      {
      row2Ptr[i] = currTempArrayPtr[j]; //
      }
   
  row2Ptr[charCntL2A + 26] = {223}; // Add 'F RH:' to the Array
  row2Ptr[charCntL2A + 27] = 'F';
  row2Ptr[charCntL2A + 28] = ' ';
  row2Ptr[charCntL2A + 29] = 'R';
  row2Ptr[charCntL2A + 30] = 'H';
  row2Ptr[charCntL2A + 31] = ':';

  for (uint16_t i = charCntL2A + 32, j = 0; i < charCntL2A + 35  && j < 3; i++, j++) // Add Current Humidity to Array
      {
      row2Ptr[i] = currHumidArrayPtr[j]; //
      }
  
  for (uint16_t i = charCntL2A + 35, j = 0; i < charCntL2A + 51 && j < 16; i++, j++) // Add "% Precip Chance:" to Array
      {
      row2Ptr[i] = row2_segment3_Ptr[j]; //
      }
  
  for (uint16_t i = charCntL2A + 51, j = 0; i < (charCntL2A + strlen(currPreProbArrayPtr) + 51) && j < strlen(currPreProbArrayPtr); i++, j++) // Add currPreProbArray to Array
      {
      row2Ptr[i] = currPreProbArrayPtr[j]; //
      }

  charCntL2A = charCntL2A + strlen(currPreProbArrayPtr); //incorporate strlen of currPreProbArray into character count
  
  row2Ptr[charCntL2A + 51] = '%'; 
  row2Ptr[charCntL2A + 52] = ' ';

  for (uint16_t i = charCntL2A + 51, j = 0; i < charCntL2A + 58 && j < 7; i++, j++) //Add "%_Wind:" to array
      {
      row2Ptr[i] = row2_segment5_Ptr[j]; //
      }
    
  for (uint16_t i = charCntL2A + 58, j = 0; i < charCntL2A + 60 && j < 2; i++, j++) //Add currWindArray to array
      {
      row2Ptr[i] = currWindArrayPtr[j]; //
      }
  
  for (uint16_t i = charCntL2A + 60, j = 0; i < charCntL2A + 64 && j < 4; i++, j++) //Add "mph_" to array
      {
      row2Ptr[i] = end_row2_Ptr[j]; 
      }

  row2Ptr[charCntL2A + 64] = 0;

  //**************************************************************
  //*************LCD ROW 3 3-day forecast contents****************
  //**************************************************************
//Here we build a character array for line 3 (0-3 lines) of the LCD via array pointers to minimize memory fragmentation.
//The array pointer row3Ptr uses row 2 array 'row3[85]' to store the characters that will be scrolled on LCD row 3
//note the array count goes from 0-n while the character count returned by strlen goes from 1-n. 

  //convert temp floats to string arrays
  dtostrf(daily->temperatureHigh[0], 5, 1, row3_todayHighTempArrayPtr);
  dtostrf(daily->temperatureHigh[1], 5, 1, row3_tomorrowHighTempArrayPtr);
  dtostrf(daily->temperatureHigh[2], 5, 1, row3_nextDayHighTempArrayPtr);
  dtostrf(daily->temperatureLow[0], 5, 1, row3_todayLowTempArrayPtr);
  dtostrf(daily->temperatureLow[1], 5, 1, row3_tomorrowLowTempArrayPtr);
  dtostrf(daily->temperatureLow[2], 5, 1, row3_nextDayLowTempArrayPtr);
  
//Build the array
 
for (uint16_t i = 0; i < 17; i++) //row3_Segment1, 17 characters "Current Forecast:"
    {
      row3Ptr[i] = row3_segment1Ptr[i]; //
    }

charCntL3A = (daily->summary[0].length()); //Length of this segment varies so we need to know its length 
    
for (uint16_t i = 17, j = 0; i < (charCntL3A + 17)  && j < charCntL3A; i++, j++) //today's forecast, ~17 characters, daily->summary[0]
    {
      row3Ptr[i] = ((daily->summary[0])[j]); //     
    }
    
row3Ptr[(charCntL3A + 17)] = 'H';  //High temp abbreviation
row3Ptr[(charCntL3A + 18)] = ':'; //colon

for (uint16_t i = charCntL3A + 19, j = 0; i < charCntL3A + 19 + strlen(row3_todayHighTempArrayPtr) && j < strlen(row3_todayHighTempArrayPtr); i++, j++) // add current high temp to array - row3_todayHighTempArray
    {
      row3Ptr[i] = row3_todayHighTempArrayPtr[j]; //    
    }

charCntL3A = charCntL3A + strlen(row3_todayHighTempArrayPtr);

row3Ptr[charCntL3A + 19] = ' '; //add Space to array
row3Ptr[charCntL3A + 20] = 'L'; //low temp abbreviation
row3Ptr[charCntL3A + 21] = ':'; //colon

for (uint16_t i = charCntL3A + 22, j = 0; i < charCntL3A + 22 + strlen(row3_todayLowTempArrayPtr)  && j < strlen(row3_todayLowTempArrayPtr); i++, j++) //add current Low temp to array
    {
      row3Ptr[i] = row3_todayLowTempArrayPtr[j]; 
    } 

charCntL3A = charCntL3A + strlen(row3_todayLowTempArrayPtr);

row3Ptr[charCntL3A + 22] = ' '; //add s Space to array

for (uint16_t i = charCntL3A + 23, j = 0; i < charCntL3A + 26  && j < 3; i++, j++) //add NEXT DAY abbreviation - 3 chars
    {
      row3Ptr[i] = (strTime(daily->time[1]))[j]; //
    } 

row3Ptr[charCntL3A + 26] = ':'; //add a colon to array

charCntL3B = daily->summary[1].length();

for (uint16_t i = charCntL3A + 27, j = 0; i < (charCntL3A + 27) + charCntL3B  && j < charCntL3B; i++, j++) //add tomorrow forecast to array
    {
      row3Ptr[i] = (daily->summary[1])[j]; //
    } 

charCntL3B = charCntL3A + charCntL3B;

row3Ptr[charCntL3B + 27] = 'H';  //High temp abbreviation
row3Ptr[charCntL3B + 28] = ':';

for (uint16_t i = charCntL3B + 29, j = 0; i < charCntL3B + 29 + strlen(row3_tomorrowHighTempArrayPtr)  && j < strlen(row3_tomorrowHighTempArrayPtr); i++, j++) //add tomorrow high temp to array
    {
      row3Ptr[i] = row3_tomorrowHighTempArrayPtr[j]; //
    } 

charCntL3B = charCntL3B + strlen(row3_tomorrowHighTempArrayPtr);

row3Ptr[charCntL3B + 29] = ' '; //add a Space to array
row3Ptr[charCntL3B + 30] = 'L'; //low temp abbreviation
row3Ptr[charCntL3B + 31] = ':';

for (uint16_t i = charCntL3B + 32, j = 0; i < charCntL3B + 32 + strlen(row3_tomorrowLowTempArrayPtr) && j < strlen(row3_tomorrowLowTempArrayPtr); i++, j++) //add tomorrow low temp
    {
      row3Ptr[i] = row3_tomorrowLowTempArrayPtr[j]; //
    } 

charCntL3B = charCntL3B + strlen(row3_tomorrowLowTempArrayPtr);

row3Ptr[charCntL3B + 32] = ' '; //add a Space to array

for (uint16_t i = charCntL3B + 33, j = 0; i < charCntL3B + 36  && j < 3; i++, j++) //add next Day abbreviation to array
    {
      row3Ptr[i] = strTime(daily->time[2])[j]; //
    } 
    
row3Ptr[charCntL3B + 36] = ':';

charCntL3C = daily->summary[2].length();

for (uint16_t i = charCntL3B + 37, j = 0; i < ( charCntL3B + 37 + charCntL3C ) && j < charCntL3C; i++, j++) //add next Day Forecast
    {
      row3Ptr[i] = (daily->summary[2])[j]; //
    }

charCntL3C = charCntL3C + charCntL3B;

row3Ptr[charCntL3C + 37] = 'H';  //High temp abbreviation
row3Ptr[charCntL3C + 38] = ':';

for (uint16_t i = charCntL3C + 39, j = 0; i < charCntL3C + 39 + strlen(row3_nextDayHighTempArrayPtr)  && j < strlen(row3_nextDayHighTempArrayPtr); i++, j++) //add next Day High abbreviation to array
    {
      row3Ptr[i] = row3_nextDayHighTempArrayPtr[j]; //
    }

charCntL3C = charCntL3C + strlen(row3_nextDayHighTempArrayPtr);

row3Ptr[charCntL3C + 39] = ' '; //add Space to array
row3Ptr[charCntL3C + 40] = 'L';  //High temp abbreviation
row3Ptr[charCntL3C + 41] = ':';

for (uint16_t i = charCntL3C + 41, j = 0; i < charCntL3C + 41 + strlen(row3_nextDayLowTempArrayPtr)  && j < strlen(row3_nextDayLowTempArrayPtr); i++, j++) //add next Day High abbreviation to array
    {
      row3Ptr[i] = row3_nextDayLowTempArrayPtr[j]; //
    }

charCntL3C = charCntL3C + strlen(row3_nextDayLowTempArrayPtr);

row3Ptr[charCntL3C + 41] = ' ';  
row3Ptr[charCntL3C + 42] = 0;

  // Delete to free up space and prevent fragmentation as strings change in length
  delete current;
  delete hourly;
  delete daily;

  //Display old and new lines and line lengths on the serial monitor
  
  //compare line length of old and new
  new_row2StrLen = strlen(row2Ptr);
  if(old_row2StrLen != new_row2StrLen){ 
    Serial.println(F("#################################@@@@@@@@@@@@@@@@@@@@@@@@@ row2 Changed @@@@@@@@@@@@@@@@@@@@@@@@@@@#######################"));
    Serial.println(F("                                                       ###################"));
  }
  
  Serial.print(F("old line 2 length: "));Serial.println(old_row2StrLen);
  Serial.print(F(" new line 2 length: "));Serial.println(strlen(row2Ptr));

  new_row3StrLen = strlen(row3Ptr);
  if(old_row3StrLen != new_row3StrLen){ 
    Serial.println(F("#################################@@@@@@@@@@@@@@@@@@@@@@@@@ row3 Changed @@@@@@@@@@@@@@@@@@@@@@@@@@@########################"));
    Serial.println(F("                                                       ###################")); 
  }
  
  Serial.print(F("old line 3 length: "));Serial.println(old_row3StrLen);
  Serial.print(F(" new line 3 length: "));Serial.println(strlen(row3Ptr));
   
  Serial.println(F("################# END DARKSKY ###################"));
 }

//***************************************************************************************
//**                          Convert unix time to a time string
//***************************************************************************************/
 
  String strTime(time_t unixTime)
  {
    unixTime += TIME_OFFSET;
    return ctime(&unixTime);
  }

//**************************************************************
//************* END Function void getDarkSky()******************
//**************************************************************
