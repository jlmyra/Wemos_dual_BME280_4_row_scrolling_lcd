//**************************************************************
//**************** Function void getDarkSky()******************
//**************************************************************
  void getDarkSky(){

  checkWiFi(); //check the wifi connection

  // Create the structures that hold the retrieved weather
  DSW_current *current = new DSW_current;
  DSW_hourly *hourly = new DSW_hourly;
  DSW_daily  *daily = new DSW_daily; 
  
  oldmlr0 = mlr0;  //fill variable with previous reading to compare below and in moving letter functions
  oldSegmentDSR2 = segmentDSR2; 
  oldSegmentDSR3 = segmentDSR3;
  
  segmentDSR2 = ""; //Clear lcd line 2 variables
  currSummary = "";  
  currTemp = 0;
  currHumid = 0;
  currPreProb = 0;
  currWind = 0; 
  
  segmentDSR3 = ""; //Clear lcd line 3 variables
  DSR3_todayF = "";
  DSR3_tomorrowF = "";
  DSR3_nextDayF = "";
  DSR3_today = "";
  DSR3_tomorrow= "";
  DSR3_nextDay  = ""; 

 //lcd.clear(); //necessary?
 //delayMicroseconds(2000);

 Serial.println();
  Serial.print("###################################################################################");
  Serial.println("###################################################################################");
  Serial.println("Requesting weather information from DarkSky.net... ");
  
  
  dsw.getForecast(current, hourly, daily, api_key, latitude, longitude, units, language);

  Serial.print("###################################################################################");
  Serial.println("###################################################################################");
    
  Serial.println("Weather from Dark Sky\n");

  // We can use the timezone to set the offset eventually...
  //Serial.print("Timezone            : "); Serial.println(current->timezone);
  
  Serial.println("############### Current weather ###############\n");
  Serial.print("Current time             : "); Serial.println(timeF);
  Serial.print("Current summary          : "); Serial.println(current->summary);
  
  Serial.print("Current precipInten      : "); Serial.println(current->precipIntensity);
  //Serial.print("Current precipType       : "); Serial.println(getMeteoconIcon(current->precipType));
  Serial.print("Current precipProbability: "); Serial.println(current->precipProbability);
  Serial.print("Current temperature      : "); Serial.println(current->temperature);
  Serial.print("Current humidity         : "); Serial.println(current->humidity);
  Serial.print("Current pressure         : "); Serial.println(current->pressure);
  Serial.print("Current wind speed       : "); Serial.println(current->windSpeed);
  Serial.print("Current wind gust        : "); Serial.println(current->windGust);
  Serial.print("Current wind dirn        : "); Serial.println(current->windBearing);

  Serial.println();
  Serial.println("#####################################################");
  Serial.println("#####################################################");
   
//Renew Row 2 Variables 
  //currSummary = (current->summary);  
  currSummary = (hourly->summary[0]); //Use hourly forcast for current conditions may need to adjust the hour
  currTemp = (current->temperature);
  currHumid = (current->humidity);
  currPreProb = (current->precipProbability);
  currWind = (current->windSpeed);
  
//Build Row 2 Moving Letter line

//Below is for reference when building the line contents
/*  
float currTemp = 0.0;
  int currHumid = 0;
  int currPreProb = 0;
  int currWind = 0;
  int DSR2_stringStart, DSR2_stringStop = 0; //Initialize Row 2 Scrolling Letter Counter
  int DSR2_scrollCursor = screenWidth;  // LCD Row 2
  String segmentDSR2; // LCD Row 2
  String DSR2_segment1 = "Outdoor Conditions: ";
  String DSR2_Segment1A = " T:";
  String DSR2_segment2 = "F RH:" ;
  String DSR2_segment3 = "% Precip Chance:";
  String DSR2_segment4 = "% ";
  String DSR2_segment5 = "Wind:";
  String end_DSR2 = "mph "; // LCD Row 2
  String currSummary;
*/
  segmentDSR2 += DSR2_segment1;
  segmentDSR2 += currSummary;              
  segmentDSR2 += DSR2_Segment1A;            
  segmentDSR2 += currTemp;
  segmentDSR2 += char(223); 
  segmentDSR2 += DSR2_segment2;
  segmentDSR2 += currHumid;
  segmentDSR2 += DSR2_segment3;
  segmentDSR2 += currPreProb;
  segmentDSR2 += DSR2_segment4;
  segmentDSR2 += DSR2_segment5; 
  segmentDSR2 += currWind;
  segmentDSR2 += end_DSR2;
   
//LCD ROW 3 3-day forcast contents
  
//Renew DSR3 variables
  DSR3_todayF = (daily->summary[0]); //0 - today, 1 - tomorrow, 2 - Next Day
  DSR3_todayHighTemp = (daily->temperatureHigh[0]);
  DSR3_todayLowTemp = (daily->temperatureLow[0]);
  DSR3_tomorrowF = (daily->summary[1]);
  DSR3_tomorrowHighTemp = (daily->temperatureHigh[1]);
  DSR3_tomorrowLowTemp = (daily->temperatureLow[1]);
  DSR3_nextDayF = (daily->summary[2]);
  DSR3_nextDayHighTemp = (daily->temperatureHigh[2]);
  DSR3_nextDayLowTemp = (daily->temperatureLow[2]);
  DSR3_today = (strTime(daily->time[1]));   //to get the day of the week for the 3 day forecast
  DSR3_tomorrow = (strTime(daily->time[2]));//gets parsed in 'moveDarkSky3'
  DSR3_nextDay = (strTime(daily->time[3]));
  
//Build the moving Row 3 Line

//Below is for reference when building the line contents
/*
  String segmentDSR3; // LCD Row 3
  String DSR3_sp = " "; // LCD Row 3
  String DSR3_today, DSR3_tomorrow, DSR3_nextDay;
  String DSR3_todayF, DSR3_tomorrowF, DSR3_nextDayF;
  String DSR3_segment1 = "Current Forecast: ";
  String DSR3_colon = ": ";
  String DSR3_High_T = " H:";
  String DSR3_Low_T = "  L:";
  
  segmentDSR3 = DSR3_segment1 + 
                DSR3_todayF + DSR3_High_T + (DSR3_todayHighTemp) + DSR3_Low_T + (DSR3_todayLowTemp) + DSR3_sp +
                DSR3_tomorrow.substring(0, 3) + DSR3_colon + DSR3_tomorrowF + DSR3_High_T + (DSR3_tomorrowHighTemp) + 
                DSR3_sp + DSR3_Low_T + (DSR3_tomorrowLowTemp) + DSR3_sp +
                DSR3_nextDay.substring(0, 3) + DSR3_colon + DSR3_nextDayF + DSR3_High_T + (DSR3_nextDayHighTemp) + 
                DSR3_Low_T + (DSR3_nextDayLowTemp) + DSR3_sp;
*/

segmentDSR3 += "Today: ";
segmentDSR3 += DSR3_todayF;
segmentDSR3 += " H:";
segmentDSR3 += DSR3_todayHighTemp;
segmentDSR3 += "  L:";
segmentDSR3 += DSR3_todayLowTemp;
segmentDSR3 += " ";
segmentDSR3 += DSR3_tomorrow.substring(0, 3);
segmentDSR3 += ": ";
segmentDSR3 += DSR3_tomorrowF;
segmentDSR3 += " H:";
segmentDSR3 += DSR3_tomorrowHighTemp;
segmentDSR3 += "  L:";
segmentDSR3 += DSR3_tomorrowLowTemp;
segmentDSR3 += " ";
segmentDSR3 += DSR3_nextDay.substring(0, 3);
segmentDSR3 += ": ";
segmentDSR3 += DSR3_nextDayF;
segmentDSR3 += " H:";
segmentDSR3 += DSR3_nextDayHighTemp;
segmentDSR3 += "  L:";
segmentDSR3 += DSR3_nextDayLowTemp;
segmentDSR3 += " ";

  // Delete to free up space and prevent fragmentation as strings change in length
  delete current;
  delete hourly;
  delete daily;

  //Serial.println();
  //Display old and new lines on the serial monitor
  Serial.println(mlr0); //Line 0

  //compare line length of old and new
  if(oldSegmentDSR2.length() != segmentDSR2.length()){ 
    Serial.println("#################################@@@@@@@@@@@@@@@@@@@@@@@@@ SegmentDSR2 Changed @@@@@@@@@@@@@@@@@@@@@@@@@@@#######################/n");
    Serial.println("                                                           ###################");
  }
  
  Serial.println(oldSegmentDSR2);
  Serial.println(segmentDSR2);
  Serial.print("old: "); Serial.print(oldSegmentDSR2.length()); Serial.print(" new: "); Serial.println(segmentDSR2.length());
  
  if(oldSegmentDSR3.length() != segmentDSR3.length()){
    Serial.println("#################################@@@@@@@@@@@@@@@@@@@@@@@@@ SegmentDSR3 Changed @@@@@@@@@@@@@@@@@@@@@@@@@@@########################ln");
    Serial.println("                                                           ###################"); 
  }
  
  Serial.println(oldSegmentDSR3);
  Serial.println(segmentDSR3);
  Serial.print("old: "); Serial.print(oldSegmentDSR3.length()); Serial.print(" new: "); Serial.println(segmentDSR3.length());
  //DSR2_previousMillis, DSR2_currentMillis, DSR3_previousMillis, DSR3_currentMillis = millis();
   
  Serial.println("################# END DARKSKY ###################");
 }

/***************************************************************************************
**                          Convert unix time to a time string
***************************************************************************************/
String strTime(time_t unixTime)
{
  unixTime += TIME_OFFSET;
  return ctime(&unixTime);
}

//**************************************************************
//************* END Function void getDarkSky()******************
//**************************************************************
