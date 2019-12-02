//**************************************************************
//*********Function to move Row 3 on LCD*******************
//**************************************************************

void moveDarkSkyR3(char *row3Ptr){

  //TIMER

  row3_currentMillis = millis();
  if (row3_currentMillis - row3_previousMillis > row3_interval) 
    {
    row3_previousMillis = row3_currentMillis; 

//check to see if old line length is different from updated line length, if so, reset counters and restart the line
  if(old_row3StrLen != new_row3StrLen && row3_previousMillis > GDS_interval)  //Using GDS_interval gets beyond the initial darksky read
    {
    row3_stringStart = row3_stringStop = 0; //reset counters
    row3_scrollCursor = screenWidth;
    
   Serial.println();
   Serial.println(F("                ##########################################################"));   
   Serial.println(F("                @@@@@@@@@@@@ row3 Resetting start, stop & width @@@@@@@@@@"));
   Serial.println(F("                ##########################################################"));
   Serial.println();
   
    old_row3StrLen = new_row3StrLen;
    }
    
//Begin lcd.print Routine

    lcd.setCursor(row3_scrollCursor, 3); //Set the Cursor to position 20 (far right)
   
         
//***-FIRST-'if' to lcd.print the first 20 characters 
       
      if(row3_stringStart == 0 && row3_scrollCursor > 0) //***-FIRST-'if'
      {
      for (int i = 0; i < row3_stringStop; i++)
      
      lcd.print (row3Ptr[i]); //***PRINT TO LCD***
      
      row3_scrollCursor--;
      row3_stringStop++;  
      } 

 //***-SECOND-'if' to lcd.print End of line reset everything
 
      else
      
      if (row3_stringStart == row3_stringStop) //***-SECOND-'if'
      {
      row3_stringStart = row3_stringStop = 0;
      row3_scrollCursor = screenWidth;
      
      } 

//*--THIRD-- if: Print the last 20 characters of the line

  else
  if (row3_stringStop == strlen(row3Ptr) && row3_scrollCursor == 0) //*--THIRD-- if: Print the last 20 characters of the line
  {
        for (int i = row3_stringStart; i< row3_stringStop; i++)
        {
        lcd.print(row3Ptr[i]);//***PRINT TO LCD***
        }

      row3_stringStart++;
  } 
  
//---Fourth if line0: lcd.print 20 character arrays - incrementing stringStart by 1 each pass
//   until there is not a full 20 characters and go to THIRD if  

      else {
        for (int i = row3_stringStart; i< row3_stringStop; i++)
        {
        lcd.print(row3Ptr[i]);//***PRINT TO LCD***
        }

      row3_stringStart++;
      row3_stringStop++;      
     }
  }
}

//**************************************************************
//**********END Function to move Row 3 on LCD*******************
//**************************************************************

/*
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, including without limitation the rights to 
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons 
 * to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


 */
