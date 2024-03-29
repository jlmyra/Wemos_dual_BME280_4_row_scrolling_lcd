//**************************************************************
//**************** Function void getNTC_Time()******************
//**************************************************************

  void getNTC_Time(char *dateArrPtr, char *numericalDatePtr, char *timeFPtr) {
   
// update the NTP client and get the UNIX UTC timestamp 
    timeClient.update();
    unsigned long epochTime =  timeClient.getEpochTime();

    // convert received time stamp to time_t object
    time_t local, utc;
    utc = epochTime;

    // Then convert the UTC UNIX timestamp to local time
    TimeChangeRule usEDT = {"EDT", Second, Sun, Mar, 2, -300};  //UTC - 5 hours - change this as needed
    TimeChangeRule usEST = {"EST", First, Sun, Nov, 2, -360};   //UTC - 6 hours - change this as needed
    Timezone usEastern(usEDT, usEST);
    local = usEastern.toLocal(utc);
   
// Clear the Array's.  with null char \0  (not sure if necessary)

  dateArrPtr[0] = 0;
  numericalDatePtr[0] = 0; 
  timeFPtr[0] = 0; 

  itoa(year(local), yearNumPtr, 10); //convert year integer to string array (integer, array, base)
  itoa(hourFormat12(local), hourNumPtr, 10); //convert hour integer to string array
  itoa(minute(local), minuteNumPtr, 10); //convert hour integer to string array)

//*****Build the dateArr - Alphanumerical date for BME Recorder Boot - Sunday, Feb 7 , 2106 ****

  uint16_t charCnt = 0;
  charCnt = strlen(dayName[weekday(local)-1]);//Get length of weekday - Sunday
   
  for (uint16_t i = 0; i < charCnt; i++) //Weekday (0 - 5)
    {
      dateArrPtr[i] = dayName[weekday(local)-1][i]; //****Add the weekday to the array****
    }
    
  for (uint16_t i = (charCnt), j = 0; (i < (charCnt + 2)) && (j < 2); i++, j++) // Add commaSp (2)
    { 
      dateArrPtr[i] = commaSpPtr[j]; // Add comma space to the array
    }
  
  for (uint16_t i = (charCnt + 2), j = 0; i < ((charCnt + 5 )) && (j < 3); i++, j++) // month (2)
    {
      dateArrPtr[i] = months[month(local)-1][j]; //****add Month abbreviation to the array****
    }
    
  for (uint16_t i = (charCnt + 5), j = 0; i < ((charCnt + 7)) && (j < 2); i++, j++) // date (2)
    {
      dateArrPtr[i] = dayNum[day(local)-1][j]; //Add Day number to the array
    }
    
  for (uint16_t i = (charCnt + 7), j = 0; i < ((charCnt + 9)) && (j < 2); i++, j++) // date (2)
    {
      dateArrPtr[i] = commaSpPtr[j]; //Add comma space to the array;
    }
    
  for (uint16_t i = (charCnt + 9), j = 0; (i < (charCnt + 13)) && (j < 4); i++, j++) // year (4)
    {
      dateArrPtr[i] = yearNumPtr[j]; //Add the year to the array
    }
    
    dateArrPtr[charCnt + 13] = ' ';  //Spaces or blanks to fill the end of line on the LCD
    dateArrPtr[charCnt + 14] = 0; //EOL for the Array

//***********Build numericalDateArray  mm/dd/yyyy***********

  uint16_t monthLen = strlen(monthNum[month(local)-1]);

  for (uint16_t i = 0; i < monthLen; i++)  // 1 digit month
    {
    numericalDatePtr[i] = monthNum[month(local)-1][i];
    }

  numericalDatePtr[monthLen] = '/';  // 2

  if ((strlen(dayNum[day(local)-1])) < 2)
    {
     monthLen--; 
    }
  for (uint16_t i = (monthLen + 1), j = 0; i < (monthLen + 3) && (j < 2); i++, j++)  // 3,4
    {
    numericalDatePtr[i] = dayNum[day(local)-1][j]; 
    }

  numericalDatePtr[monthLen + 3] = '/'; // 5

  for (uint16_t i = (monthLen + 4), j = 0; i < (monthLen + 8) && (j < 4); i++, j++)  // 6,7,8,9
    {
    numericalDatePtr[i] = yearNumPtr[j];
    }

  numericalDatePtr[monthLen + 8] = ' '; //Spaces to fill the end of line on the LCD
  numericalDatePtr[monthLen + 9] = 0; //EOL for the Array

  //********format timeF numerical time: hh:mm am********

  uint16_t hourLen = strlen(hourNumPtr);
  uint16_t minuteLen = strlen(minuteNumPtr); 

  if (hourLen > 1) // 2 digit hour If the strlen of hourNum 1-9, 10, 11, 12 is > than 1
    {
    for (uint16_t i = 0; i < hourLen; i++)
      {
      timeFPtr[i] = hourNumPtr[i]; //Add the hour to the array "hh"
      }
    }
  else          //hourLen is <= to 1, add a space before the hourNum
    { 
    timeFPtr[0] = ' ';   
    timeFPtr[1] = hourNumPtr[0];
    hourLen ++;
    }
    
    timeFPtr[hourLen] = ':';  //Add colon to the array

  if(minuteLen > 1){ 
     
    for (uint16_t i = (hourLen + 1), j = 0; (i < (hourLen + 3)) && (j < 2); i++, j++) // commaSp (2)
      { 
      timeFPtr[i] = minuteNumPtr[j];
      }
    }
   else
    {
    timeFPtr[hourLen + 1] = '0';
    timeFPtr[hourLen + 2] = minuteNumPtr[0];   
    }
    
    timeFPtr[hourLen+3] = ' ';

    for (uint16_t i = (hourLen + 4), j = 0; i < (hourLen + 6) && (j < 2); i++, j++)  // 
      {
      timeFPtr[i] = ampmPtr[isPM(local)][j]; 
      }

    timeFPtr[hourLen + 6] = ' '; //Spaces to fill the end of line on the LCD
    timeFPtr[hourLen + 7] = 0;  //EOL for the Array
      
    }  
//**************************************************************
//**************** Function void getNTC_Time()******************
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
