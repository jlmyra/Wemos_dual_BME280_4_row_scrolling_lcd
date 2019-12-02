//change log

#include <ESP8266WiFi.h>
#include <WiFiClient.h> //for Thingspeak

WiFiClient client; //for Thingspeak

//********************Location Settings*****************************

//*****BASEMENT WEMOS D1 (myraclegarden.com)
unsigned long myChannelNumber = XXXXXX;  const char * myWriteAPIKey = "XXXXXX"; String api_key = "XXXXXX";
 
//******QUONSET WEMOS D1 (mgcquonset.com)
//unsigned long myChannelNumber = XXXXXX; const char * myWriteAPIKey = "XXXXXX"; String api_key = "XXXXXXX"; //DarkSky API

//********************Location Settings*****************************

//*********************** WIFI SETTINGS **************************
//const char *ssid = "XXXXXX";
const char *ssid = "XXXXXX";
const char *password = "XXXXXX";

//const char *ssid = "XXXXXX";
//const char *password = "xXXXXXXX";

//const char *ssid = "XXXXXX"; //Quonset
//const char *password = "XXXXXX";//Quonset

//***********************End WIFI SETTINGS **************************

//*********************** ThinkSpeak SETTINGS **************************
 
#include "ThingSpeak.h"   //Thingspeak
int y = 0; //Thingspeak upload failure counter

//***********************End ThinkSpeak SETTINGS **************************

//***********************Dark Sky*****************************

#include <JSON_Decoder.h>
#include <DarkSkyWeather.h>

#include <WiFiClientSecure.h>

DS_Weather dsw; // Weather forecast library instance
#define TIME_OFFSET -4UL * 3600UL // UTC + 0 hour

// Set both longitude and latitude to at least 4 decimal places
String latitude =  "40.7464"; // 90.0000 to -90.0000 negative for Southern hemisphere
String longitude = "-74.2764"; // 180.000 to -180.000 negative for West

String units = "us";  // See notes tab - si for international units
String language = "en"; // See notes tab

int gdsCounter = 0;//counter in TakeReadingBME that counts five updates to Thingspeak and then activates getDarkSky
float GDSCounter = 0;//counter for serial display of how many time darksky has been accessed since last boot


  
//***********************END Dark Sky*****************************

//*********************NTC Clock Current Time**********************

#include <WiFiUdp.h>
#include <NTPClient.h> // Include NTPClient library
//#include <TimeLib.h> 
#include <Time.h>
#include <Timezone.h>

// Define NTP properties
#define NTP_OFFSET   60 * 60      // In seconds
#define NTP_INTERVAL 60 * 1000    // In miliseconds
#define NTP_ADDRESS  "north-america.pool.ntp.org"  // change this to whatever pool is closest (see ntp.org)
#define TIMEZONE usET // See NTP_Time.h tab for other "Zone references", UK, usMT etc

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);

  char numericalDate[12]; char *numericalDatePtr = numericalDate;
  char dateArr[24]; char *dateArrPtr = dateArr;
  char timeF[11]; char *timeFPtr = timeF;

  const char commaSp[3] = ", "; const char *commaSpPtr = commaSp;
  const char *dayName[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
  //const char **dayNamePtr = dayName;
  const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Aug", "Sep", "Oct", "Nov", "Dec"} ;
  //const char **monthsPtr = months;
  const char *monthNum[] = {" 1", " 2", " 3", " 4", " 5", " 6", " 7", " 8", " 9", "10", "11", "12"} ;
  //const char **monthNumPtr = monthNum;
  const char *dayNum[] = {" 1", " 2", " 3", " 3", " 5", " 6", " 7", " 8", " 9", "10", "11", "12", "13", "14", "15", "16", 
                          "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31"};
  //const char **dayNumPtr = dayNum;                      
  char hourNum[3]; char *hourNumPtr = hourNum;  // hour integer stored in this array
  char minuteNum[3]; char *minuteNumPtr = minuteNum;  // minute integer stored in this array 
  char yearNum[5]; char *yearNumPtr = yearNum;
  const char *ampm[] = {"AM", "PM"};  const char **ampmPtr = ampm;
  
//*********************NTC Clock Current Time**********************


//*********************** BME280 ***********************
#include <Wire.h>    // imports the wire library for I2C 
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// Create two BME280 instances
/*  
 *  BME 280 Connections
 *  0x76  CSB to V+ (for I2C mode) and SDO to GND
 *  0x77  CSB to V+ (for I2C mode) and SDO to V+
 *  https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BME280-DS002.pdf
 */
  Adafruit_BME280 bme1; //Adafruit_BME280 bme1(0x76); // I2C
  Adafruit_BME280 bme2; //Adafruit_BME280 bme2(0x77); // I2C 

//*********************LCD*********************
  #include <hd44780.h>            // main hd44780 header
  #include <hd44780ioClass/hd44780_I2Cexp.h>  // i2c LCD i/o class header
  const int LCD_COLS = 20;
  const int LCD_ROWS = 4;
  hd44780_I2Cexp lcd;
  
  int scl = 5;  //GPIO5 = D1 WEMOS SCL - YELLOW
  int sda = 4;  //GPIO4 = D2 WEMOS SDA - GREEN 
  
  int screenWidth = 20;   //LCD Display
  int screenHeight = 4;   //LCD Diaplay

//*********************LCD*********************

//LCD Row 0: Date and Sensor Data

  int counter = 0;
  int avgCounterBME = 1;
  
  float avgTempBME1 = 0.0; 
  float avgHumidBME1 = 0.0; 
  float avgBpBME1 = 0.0;
  float temperatureBME1 = 0.0 ;
  float humidityBME1 = 0.0;  
  float tempValuesBME1 = 0.0; 
  float humidValuesBME1 = 0.0; 
  float baropressBME1 = 0.0;
  float bpValuesBME1 = 0.0;

  char row0[77]; char *row0Ptr = row0;  //Text for scrolling lcd Row 0
  
  char ambT[11] = "Ambient T:"; char *ambT_Ptr = ambT;
  char F_RH[6] = "F RH:"; char *F_RH_Ptr = F_RH;
  char perBP[6] = "% BP:"; char *perBP_Ptr = perBP; //Text for scrolling lcd Row 0
  char inHgSp[7] = "in Hg "; char *inHgSpPtr = inHgSp;  //Text for scrolling lcd Row 0
  char degF[2] = {223}; char *degFPtr = degF;
  char tempBME1Array[6]; char *tempBME1ArrayPtr = tempBME1Array;
  char humidBME1Array[6]; char *humidBME1ArrayPtr = humidBME1Array;
  char baroPressBME1Array[6]; char *baroPressBME1ArrayPtr = baroPressBME1Array;
  
  uint16_t old_row0StrLen = 0;
  uint16_t new_row0StrLen = 0;

  uint16_t stringStart, stringStop = 0; //Initialize Row 0 Scrolling Letter Counter
  int scrollCursor = screenWidth;  //Initialize Row 0 Scrolling Letter variable

//LCD Row 1: Sensor Data

  float avgTempBME2 = 0.0;
  float avgHumidBME2 = 0.0;
  float temperatureBME2 = 0.0;
  float humidityBME2 = 0.0; 
  float tempValuesBME2 = 0.0;
  float humidValuesBME2 = 0.0;

// LCD Row 2: Current Conditions

  char row2[85]; char *row2Ptr = row2;
  
  const char *row2_segment1 = "Outdoor Conditions: "; const char *row2_segment1_Ptr = row2_segment1;
  const char *row2_segment3 = "% Precip Chance:"; const char *row2_segment3_Ptr = row2_segment3;
  const char *row2_segment5 = "% Wind:"; const char *row2_segment5_Ptr = row2_segment5;
  const char *end_row2 = "mph "; const char *end_row2_Ptr = end_row2;  // LCD Row 2 
  char currTempArray[6]; char *currTempArrayPtr = currTempArray;  //set up array pointer
  char currHumidArray[4]; char *currHumidArrayPtr = currHumidArray;//set up array pointer
  char currPreProbArray[5]; char *currPreProbArrayPtr = currPreProbArray;
  char currWindArray[4]; char *currWindArrayPtr = currWindArray;

  uint16_t row2_stringStart, row2_stringStop = 0; //Initialize Row 2 Scrolling Letter Counter
  int row2_scrollCursor = screenWidth;  // LCD Row 2
  
  uint16_t old_row2StrLen = 0;
  uint16_t new_row2StrLen = 0;
 
  // LCD Row 3: Forecast 

  char row3[201]; char *row3Ptr = row3;
  
  char row3_todayHighTempArray[6]; char *row3_todayHighTempArrayPtr = row3_todayHighTempArray;
  char row3_tomorrowHighTempArray[6]; char *row3_tomorrowHighTempArrayPtr = row3_tomorrowHighTempArray;
  char row3_nextDayHighTempArray[6]; char *row3_nextDayHighTempArrayPtr = row3_nextDayHighTempArray;
  char row3_todayLowTempArray[6]; char *row3_todayLowTempArrayPtr = row3_todayLowTempArray;
  char row3_tomorrowLowTempArray[6]; char *row3_tomorrowLowTempArrayPtr = row3_tomorrowLowTempArray;
  char row3_nextDayLowTempArray[6]; char *row3_nextDayLowTempArrayPtr = row3_nextDayLowTempArray;
  const char *row3_segment1 = "Current Forecast:"; const char *row3_segment1Ptr = row3_segment1;

  uint16_t row3_stringStart, row3_stringStop = 0; //Initialize Row 3 Scrolling Letter Counter
  int row3_scrollCursor = screenWidth;  // LCD Row 3
  
  uint16_t old_row3StrLen = 0;
  uint16_t new_row3StrLen = 0;
  
//******************Timers*********************

unsigned long TR_previousMillis = 0; //Take Reading BME280's Timer
unsigned long TR_interval = 3000; //Take Reading BME280's Timer

unsigned long row0_previousMillis = 0; //LCD Row 0 Move Letters
unsigned long row0_interval = 420; //LCD Row 0 Move Letters
unsigned long row0_currentMillis = 0;

unsigned long GDS_previousMillis = 0; //Get DarkSky Update
unsigned long GDS_interval = 300000;  //Every 5 minutes (300000 / 1000 / 60)

unsigned long row2_previousMillis = 0; //DarkSky LCD Row 2 timer
unsigned long row2_interval = 430;  //DarkSky LCD Row 2 timer
unsigned long row2_currentMillis = 0;

unsigned long row3_previousMillis = 0; //DarkSky LCD Row 3 timer
unsigned long row3_interval = 440;  //DarkSky LCD Row 3 timer
unsigned long row3_currentMillis = 0;

//******************Timers*********************

//**************************************************************
//**********************VOID SETUP******************************
//**************************************************************
void setup() {
  
Wire.begin();  //Start I2C

Serial.begin(1000000);  //Fast to stop it holding up the stream

//*******************LCD Set-up**********************************

int status;

  // initialize LCD with number of columns and rows: 
  // hd44780 returns a status from begin() that can be used
  // to determine if initalization failed.
  // the actual status codes are defined in <hd44780.h>
  status = lcd.begin(LCD_COLS, LCD_ROWS);
  if(status) // non zero status means it was unsuccesful
  {
    status = -status; // convert negative status value to positive number

    // begin() failed so blink error code using the onboard LED if possible
    hd44780::fatalError(status); // does not return
  }

  // turn on automatic line wrapping
  // which automatically wraps lines to the next lower line and wraps back
  // to the top when at the bottom line
  // NOTE: 
  // noLineWrap() can be used to disable automatic line wrapping.
  // _write() can be called instead of write() to send data bytes
  // to the display bypassing any special character or line wrap processing.
  lcd.lineWrap();
//*******************LCD Set-up**********************************


//*******************Set up WiFi connection**********************

const char* deviceName = "Jims_ESP8266";

 WiFi.disconnect();  //Prevent connecting to wifi based on previous configuration
 WiFi.hostname(deviceName);
 WiFi.mode(WIFI_STA); //This line hides the viewing of ESP as wifi hotspot

 WiFi.begin(ssid, password);

//*******************Start NTC Clock**********************

timeClient.begin();

//***********************Start ThingSpeak****************************

ThingSpeak.begin(client);  //Thingspeak  

//***************Run Function BME280 RecorderBoot********************    
 /*
  * check BME 280's, check wifi connection, get the time 
  * initialize the LCD, run first DarkSky
  * 
  */
  bme280RecorderBoot();
  
//*********************BME280 Sensor Temp Correction************************

//bme1.setTempCal(-0.6);     // Arduino 2-Temp was reading high - subtract 0.6 degrees 
//bme2.setTempCal(-0.4);     // Temp was reading high - subtract 0.4 degrees

//bme1.setTempCal(-1.4);     // Arduino 1-Temp was reading high - subtract 0.6 degrees 
//bme2.setTempCal(-1.6);     // Temp was reading high - subtract 0.4 degrees

//*********************BME280 Sensor Temp Correction************************
   
  }  //End void setup()

//**************************************************************
//**********************END VOID SETUP**************************
//**************************************************************


//**************************************************************
//************************VOID LOOP*****************************
//**************************************************************

  void loop() {
  
  takeReadingBME280(row0, numericalDate, timeF); //Read and Average BME280 measurements
  
  moveLetters(row0);  //LCD Row 0
  
  moveDarkSkyR2(row2); //LCD Row 2
  
  moveDarkSkyR3(row3); //LCD Row 3
  
 //getDarkSky timing handled by takeBME280 update thingspeak - every 5 minutes 
 /* 
  
  unsigned long GDS_currentMillis = millis();  // Get DarkSky Update every 5 minutes
  if (GDS_currentMillis - GDS_previousMillis > GDS_interval) {
      GDS_previousMillis = GDS_currentMillis;
    
      getDarkSky();  
    }
*/
  }

//**************************************************************
//************************END VOID LOOP*************************
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
