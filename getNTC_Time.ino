//**************************************************************
//**************** Function void getNTC_Time()******************
//**************************************************************
  void getNTC_Time() {
    
  //Serial.println("Getting the Time");

  checkWiFi();
  
    date = "";  // clear the variables
    t = "";
    numericalDate = "";
    
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

    // format the Time variables into strings with proper names for month, day, year
    date += days[weekday(local)-1];
    date += ", ";
    date += months[month(local)-1];
    date += " ";
    date += day(local);
    date += ", ";
    date += year(local);
    date += " ";
    
    // format the Time variables into strings with numerical names for month, day, year
    numericalDate += monthNum[month(local)-1];
    numericalDate += "/";
    numericalDate += day(local);
    numericalDate += "/";
    numericalDate += year(local);
    numericalDate += " ";

    // format the time to 12-hour format with AM/PM and no seconds
    t += hourFormat12(local);
    t += ":";
    if(minute(local) < 10)  // add a zero if minute is under 10
      t += "0";
    t += minute(local);
    t += " ";
    t += ampm[isPM(local)];
    t += " ";
    
  timeF = t; 
    }
    
//**************************************************************
//**************** Function void getNTC_Time()******************
//**************************************************************
