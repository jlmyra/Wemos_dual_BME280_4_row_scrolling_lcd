//**************************************************************
//***************Function to Write ThingSpeak*******************
//**************************************************************
void writeThingSpeak() {
  
  //getNTC_Time();
  
  getNTC_Time(dateArr, numericalDate, timeF);
  
  // set the fields with the values
  ThingSpeak.setField(1,timeFPtr); //Time
  ThingSpeak.setField(2,numericalDatePtr); //Date
  ThingSpeak.setField(3,avgTempBME1); //Ambient T
  ThingSpeak.setField(4,avgHumidBME1); //Ambient Rh
  ThingSpeak.setField(5,avgTempBME2); //HC T
  ThingSpeak.setField(6,avgHumidBME2); //HC Rh
  ThingSpeak.setField(7,avgBpBME1); //BP Ambient
  
  // write to the ThingSpeak channel
  //Serial.println("at TS writeFields"); Serial.println(" ");

  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  
  if(x == 200){
    Serial.println("Thingspeak update successful.");
    y = 0;
  }
  else
   {
    y++;
    lcd.clear();
    lcd.setCursor(0,2); lcd.print("Problem updating TS ");
    lcd.setCursor(0,3); lcd.print("HTTP error: "); lcd.print(String(x));
    delay(3000);
    Serial.println("@@@@@@@@@@@@@@@@ Problem updating channel. HTTP error code @@@@@@@@@@@@@@@@@" + String(x)); Serial.println();
    if (y==10){
      while(0);
    }
  }
//Serial.println();
Serial.println(row0Ptr);
Serial.println(row2Ptr);
Serial.println(row3Ptr);
Serial.println();
}

//**************************************************************
//***********END Function to Write ThingSpeak*******************
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
