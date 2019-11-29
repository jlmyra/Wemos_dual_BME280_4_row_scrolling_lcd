//**************************************************************
//*********Function to move Row 2 on LCD*******************
//**************************************************************
//This function scrolls the letters of a line from right to left. It was inspired by "Single line scroll from Nishant Arora-https://goo.gl/qPGpWB"
//On each pass through the function a segment of the array is displayed. This segment is created by assessing the conditions below.
//1. The first 20 characters of the line (see First "if" below) The cursor starts at 20 and moves to 0 with each pass. It creates a group of characters
// that increases by one with each pass
//2. The next groups of 20 characters (see Fourth "if' below) When the cursor reaches 0 then it displays a group of characters that takes one off the
// beginning and adds one to the end until it reaches less than 20 characters left
//3. The end of the line that is less than 20 characters (see Third 'if' below)
//4. The last of the 20 characters and spaces have been displayed reset counters and start over (see Second 'if' below)


void moveDarkSkyR2(char *row2Ptr){

  //TIMER
  
  row2_currentMillis = millis();
  if (row2_currentMillis - row2_previousMillis > row2_interval) 
    {
    row2_previousMillis = row2_currentMillis;

//check to see if old line length is different from updated line length, if so, reset counters and restart the line
  if(old_row2StrLen != new_row2StrLen && row2_previousMillis > GDS_interval)  //Using GDS_interval gets beyond the initial darksky read
    {   
    row2_stringStart = row2_stringStop = 0; //reset counters
    row2_scrollCursor = screenWidth;
         
   Serial.println();
   Serial.println(F("                ##########################################################"));   
   Serial.println(F("                @@@@@@@@@@@@ row2 Resetting start, stop & width @@@@@@@@@@"));
   Serial.println(F("                ##########################################################"));
   Serial.println();
   
    old_row2StrLen = new_row2StrLen;
    }
  
//Begin lcd.print Routine

    lcd.setCursor(row2_scrollCursor, 2); //Set the Cursor to position 20 (far right)

         
//***-FIRST-'if' to lcd.print the first 20 characters 
       
   if(row2_stringStart == 0 && row2_scrollCursor > 0) //***-FIRST-'if'
    {
      for (int i = 0; i < row2_stringStop; i++)
      
      lcd.print (row2Ptr[i]); //***PRINT TO LCD***    
      row2_scrollCursor--;
      row2_stringStop++;  
      
   }
   
 //***-SECOND-'if' to lcd.print End of line reset everything
 
  else
      
    if (row2_stringStart == row2_stringStop) //***-SECOND-'if'
    {
    row2_stringStart = row2_stringStop = 0;
    row2_scrollCursor = screenWidth;     
    } 

//*--THIRD-- if: Print the last 20 characters of the line

  else
  
    if (row2_stringStop == strlen(row2Ptr) && row2_scrollCursor == 0) //*--THIRD-- if: Print the last 20 characters of the line
    {
      for (int i = row2_stringStart; i< row2_stringStop; i++)
      {
      lcd.print(row2Ptr[i]);//***PRINT TO LCD***
      }

    row2_stringStart++;
    } 
  
//---Fourth if line0: lcd.print 20 character arrays - incrementing stringStart by 1 each pass
//   until there is not a full 20 characters and go to THIRD if  

  else 
      
    {
      for (int i = row2_stringStart; i< row2_stringStop; i++)
      {
      lcd.print(row2Ptr[i]);//***PRINT TO LCD***
      }

      row2_stringStart++;
      row2_stringStop++;       
    }
  }
}

//**************************************************************
//**********END Function to move Row 2 on LCD*******************
//**************************************************************
