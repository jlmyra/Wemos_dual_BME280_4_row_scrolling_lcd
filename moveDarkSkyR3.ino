//**************************************************************
//*********Function to move Row 3 on LCD*******************
//**************************************************************

void moveDarkSkyR3(String row3Line){
  
  DSR3_currentMillis = millis();
  if (DSR3_currentMillis - DSR3_previousMillis > DSR3_interval) {
  DSR3_previousMillis = DSR3_currentMillis; 

  if(oldSegmentDSR3.length() != row3Line.length() && DSR3_previousMillis > GDS_interval){
    DSR3_stringStart = DSR3_stringStop = 0;
    DSR3_scrollCursor = screenWidth;
    
  Serial.println();
   Serial.println("                ##########################################################");   
   Serial.println("                @@@@@@@@@@@@ DSR3 Resetting start, stop & width @@@@@@@@@@");
   Serial.println("                ##########################################################");
  Serial.println();
   
   oldSegmentDSR3 = row3Line;
  }
      
    lcd.setCursor(DSR3_scrollCursor, 3);
    lcd.print(row3Line.substring(DSR3_stringStart,DSR3_stringStop));
            
      if(DSR3_stringStart == 0 && DSR3_scrollCursor > 0)
      {
      DSR3_scrollCursor--;
      DSR3_stringStop++;
      } 
      else if (DSR3_stringStart == DSR3_stringStop)
      {
      DSR3_stringStart = DSR3_stringStop = 0;
      DSR3_scrollCursor = screenWidth;
      } 
      else if (DSR3_stringStop == row3Line.length() && DSR3_scrollCursor == 0) 
      {
      DSR3_stringStart++;
      } 
      else 
      {
      DSR3_stringStart++;
      DSR3_stringStop++;
      }       
    }
  }

//**************************************************************
//**********END Function to move Row 3 on LCD*******************
//**************************************************************
