//**************************************************************
//*********Function to move Row 2 on LCD*******************
//**************************************************************

void moveDarkSkyR2(String row2Line){
  //TIMER
  DSR2_currentMillis = millis();
  if (DSR2_currentMillis - DSR2_previousMillis > DSR2_interval) {
  DSR2_previousMillis = DSR2_currentMillis;
  
  //check to see if old line length is different from updated line length, if so, reset counters
  if(oldSegmentDSR2.length() != row2Line.length() && DSR2_previousMillis > GDS_interval){
    DSR2_stringStart = DSR2_stringStop = 0;
      DSR2_scrollCursor = screenWidth;
   Serial.println();
   Serial.println("                ##########################################################");   
   Serial.println("                @@@@@@@@@@@@ DSR2 Resetting start, stop & width @@@@@@@@@@");
   Serial.println("                ##########################################################");
   Serial.println();
   oldSegmentDSR2 = row2Line; //get out of the loop
  }
    //move the letters. Starts at position 20 and letter 1 
    lcd.setCursor(DSR2_scrollCursor, 2);
    lcd.print(row2Line.substring(DSR2_stringStart,DSR2_stringStop));
            
      if(DSR2_stringStart == 0 && DSR2_scrollCursor > 0) //moves of 1st 20 characters moving from row 20 to 1
      {
      DSR2_scrollCursor--;
      DSR2_stringStop++;
      } 
      else if (DSR2_stringStart == DSR2_stringStop) //finished printing the row and start the row over
      {
      DSR2_stringStart = DSR2_stringStop = 0;
      DSR2_scrollCursor = screenWidth;
      } 
      else if (DSR2_stringStop == row2Line.length() && DSR2_scrollCursor == 0) //found the end of the line
      {
      DSR2_stringStart++;
      } 
      else 
      {
      DSR2_stringStart++; //keep going until the end of line is found
      DSR2_stringStop++;
      }       
    }
  }

//**************************************************************
//**********END Function to move Row 2 on LCD*******************
//**************************************************************
