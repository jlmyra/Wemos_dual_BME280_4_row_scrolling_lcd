//**************************************************************
//***********Function to Scroll Row 0 on LCD*******************
//**************************************************************

void moveLetters(String row0Line){
/*LCD line 1
  int stringStart, stringStop = 0; //Initialize Row 0 Scrolling Letter Counter
  int scrollCursor = screenWidth;  //Initialize Row 0 Scrolling Letter variable
  String mlr01 = "BME280-1 ";     //Text for scrolling lcd Row 0-space required at end of string to clear the screen
  String mlr02 = "Ambient T:";    //Text for scrolling lcd Row 0
  String mlr03 = "F RH:";         //Text for scrolling lcd Row 0
  String mlr04 = "% BP:";         //Text for scrolling lcd Row 0
  String mlr05 = "in Hg ";        //Text for scrolling lcd Row 0
  String mlr0;                   //Text for scrolling lcd Row 0
*/

  ML_currentMillis = millis();
  if (ML_currentMillis - ML_previousMillis > ML_interval) {
      ML_previousMillis = ML_currentMillis; 
       
      if(oldmlr0.length() != row0Line.length() && DSR3_previousMillis > GDS_interval){
    stringStart = stringStop = 0;
    scrollCursor = screenWidth;

   Serial.println();
   Serial.println("                ##########################################################");   
   Serial.println("                @@@@@@@@@@@@ mlr0 Resetting start, stop & width @@@@@@@@@@");
   Serial.println("                ##########################################################");
   Serial.println();
   
   oldmlr0 = row0Line;
  }
  /*    
  mlr0 = numericalDate + timeF + mlr02 + temperatureBME1 + char(223) +
             mlr03 + humidityBME1 + mlr04 + baropressBME1 + mlr05;
  */
    lcd.setCursor(scrollCursor, 0);
    lcd.print(row0Line.substring(stringStart,stringStop));
            
      if(stringStart == 0 && scrollCursor > 0)
      {
      scrollCursor--;
      stringStop++;
      } 
      else if (stringStart == stringStop)
      {
      stringStart = stringStop = 0;
      scrollCursor = screenWidth;
      } 
      else if (stringStop == row0Line.length() && scrollCursor == 0) 
      {
      stringStart++;
      } 
      else 
      {
      stringStart++;
      stringStop++;
      }       
    }
  }

//**************************************************************
//***********Function to Scroll Row 0 on LCD*******************
//**************************************************************
