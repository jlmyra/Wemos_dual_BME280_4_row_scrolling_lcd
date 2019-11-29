//**************************************************************
//***********Function to Scroll Row 0 on LCD*******************
//**************************************************************

void moveLetters(char *row0Ptr){

  row0_currentMillis = millis();
  if (row0_currentMillis - row0_previousMillis > row0_interval) {
      row0_previousMillis = row0_currentMillis; 
      
  //Test to see if Line length has changed    
   
    if(old_row0StrLen != new_row0StrLen && row0_previousMillis > GDS_interval)
    {

    stringStart = stringStop = 0;
    scrollCursor = screenWidth;

   Serial.println();
   Serial.println(F("                ##########################################################"));   
   Serial.println(F("                @@@@@@@@@@@@ mlr0 Resetting start, stop & width @@@@@@@@@@"));
   Serial.println(F("                ##########################################################"));
   Serial.println();
   Serial.println(F("Function row0 after strlen"));
   
   old_row0StrLen = strlen(row0Ptr);
    }
    
//Begin lcd.print Routine

    lcd.setCursor(scrollCursor, 0);//scrollCursor starts at 20 stringStart, stringStart start at 0
          
//***-FIRST-'if' to lcd.print the first 20 characters 
       
      if(stringStart == 0 && scrollCursor > 0) //***-FIRST-'if'
      {              
      for (int i = 0; i < stringStop; i++)
        {
      lcd.print (row0Ptr[i]); //***PRINT TO LCD***
        }     
      scrollCursor--;
      stringStop++;          
      } 

 //***-SECOND-'if' to lcd.print End of line reached--reset everything
 
      else
       
      if (stringStart == stringStop) //***-SECOND-'if'
      {
      stringStart = stringStop = 0;
      scrollCursor = screenWidth;     
      } 

//*--THIRD-- if: Print the last 20 characters of the line

  else
  
  if (stringStop == strlen(row0Ptr) && scrollCursor == 0) //*--THIRD-- if: Print the last 20 characters of the line
  {     
        for (int i = stringStart; i< stringStop; i++)
        {
        lcd.print(row0Ptr[i]);//***PRINT TO LCD***
        }
        
      stringStart++;
  }  
//---Fourth if line0: lcd.print next 20 character chunks shifting the line by one character  
      else 
      {      
        for (int i = stringStart; i< stringStop; i++)
        {      
      lcd.print(row0Ptr[i]);//***PRINT TO LCD***
        }
      
      stringStart++;
      stringStop++;      
     }
  }
}

//**************************************************************
//***********Function to Scroll Row 0 on LCD*******************
//**************************************************************
