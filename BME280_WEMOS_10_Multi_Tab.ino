//moved the string building to getDarkSky from the moving letter functions

//Scrolling LCD Row 0, 2, 3
//new time function

#include <ESP8266WiFi.h>
#include <WiFiClient.h>

WiFiClient client;

//********************Location Settings*****************************

//*****BASEMENT WEMOS D1 (myraclegarden.com)
//unsigned long myChannelNumber = 79378;  const char * myWriteAPIKey = ""; String api_key = "";
 
//******QUONSET WEMOS D1 (mgcquonset.com)
unsigned long myChannelNumber = 77784;/*ThingSpeak*/ const char * myWriteAPIKey = ""; String api_key = ""; //DarkSky API

//********************Location Settings*****************************

//*********************** WIFI SETTINGS **************************
const char *ssid = "DeMEtEr";
//const char *ssid = "DiOnySyS";
const char *password = "";

//const char *password = "";

//char ssid[] = "JLM_iPhone";
//char password[] = "";

//const char *ssid = "Maplewood_GC"; //Quonset
//const char *password = "";//Quonset

//***********************End WIFI SETTINGS **************************

//*********************** ThinkSpeak SETTINGS **************************
 
#include "ThingSpeak.h"   //Thingspeak
int y = 0; //Thingspeak upload failure counter

//***********************End ThinkSpeak SETTINGS **************************

//***********************Dark Sky*****************************

#include <JSON_Decoder.h>
#include <DarkSkyWeather.h>
DS_Weather dsw; // Weather forecast library instance
#define TIME_OFFSET -5UL * 3600UL // UTC + 0 hour

// Set both longitude and latitude to at least 4 decimal places
String latitude =  "40.7464"; // 90.0000 to -90.0000 negative for Southern hemisphere
String longitude = "-74.2764"; // 180.000 to -180.000 negative for West

String units = "us";  // See notes tab - si for international units
String language = "en"; // See notes tab

//***********************END Dark Sky*****************************


//*********************NTC Clock Current Time**********************

#include <WiFiUdp.h>
#include <NTPClient.h> // Include NTPClient library
#include <TimeLib.h> 
#include <Time.h>
#include <Timezone.h>

// Define NTP properties
#define NTP_OFFSET   60 * 60      // In seconds
#define NTP_INTERVAL 60 * 1000    // In miliseconds
#define NTP_ADDRESS  "north-america.pool.ntp.org"  // change this to whatever pool is closest (see ntp.org)
#define TIMEZONE usET // See NTP_Time.h tab for other "Zone references", UK, usMT etc

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);

String numericalDate;
String dayName; //
String date;
String timeF;
String t;
const char * days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"} ;
const char * months[] = {"Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Aug", "Sep", "Oct", "Nov", "Dec"} ;
const char * monthNum[] = {"1", "2", "3", "3", "5", "6", "7", "8", "9", "10", "11", "12"} ;
const char * ampm[] = {"AM", "PM"} ;
char timeDateComma[21];

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

int counter = 0;
int avgCounterBME = 1;

float temperatureBME1 = 0.0, temperatureBME2 = 0.0;
float humidityBME1 = 0.0, humidityBME2 = 0.0;
float avgTempBME1 = 0.0, avgTempBME2 = 0.0;
float tempValuesBME1 = 0.0, tempValuesBME2 = 0.0;
float avgHumidBME1 = 0.0, avgHumidBME2 = 0.0;
float humidValuesBME1 = 0.0, humidValuesBME2 = 0.0;
float baropressBME1 = 0.0;
float bpValuesBME1 = 0.0;
float avgBpBME1 = 0.0;

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
  //LiquidCrystal_I2C lcd(0x27, screenWidth, screenHeight);  // Configure LiquidCrystal_I2C library with 0x27 address, 16 columns and 2 rows
  
  //LCD line 1
  int stringStart, stringStop = 0; //Initialize Row 0 Scrolling Letter Counter
  int scrollCursor = screenWidth;  //Initialize Row 0 Scrolling Letter variable
  String mlr01 = "BME280-1 ";     //Text for scrolling lcd Row 0-space required at end of string to clear the screen
  String mlr02 = "Ambient T:";    //Text for scrolling lcd Row 0
  String mlr03 = "F RH:";         //Text for scrolling lcd Row 0
  String mlr04 = "% BP:";         //Text for scrolling lcd Row 0
  String mlr05 = "in Hg ";        //Text for scrolling lcd Row 0
  String mlr0 = "";                   //Text for scrolling lcd Row 0
  String oldmlr0 = "";
  
  //LCD line 2
  
  float currTemp = 0.0;
  int currHumid = 0;
  int currPreProb = 0;
  int currWind = 0;
  int DSR2_stringStart, DSR2_stringStop = 0; //Initialize Row 2 Scrolling Letter Counter
  int DSR2_scrollCursor = screenWidth;  // LCD Row 2
  String segmentDSR2; // LCD Row 2
  String oldSegmentDSR2 = "";
  String DSR2_segment1 = "Outdoor Conditions: ";
  String DSR2_Segment1A = " T:";
  String DSR2_segment2 = "F RH:" ;
  String DSR2_segment3 = "% Precip Chance:";
  String DSR2_segment4 = "% ";
  String DSR2_segment5 = "Wind:";
  String end_DSR2 = "mph "; // LCD Row 2
  String currSummary;
  
  //LCD Line 3
  int DSR3_stringStart, DSR3_stringStop = 0; //Initialize Row 3 Scrolling Letter Counter
  int DSR3_scrollCursor = screenWidth;  // LCD Row 3
  String segmentDSR3; // LCD Row 3 - Line to be presented on LCD
  String oldSegmentDSR3 = "";
  String DSR3_sp = " "; // LCD Row 3 space
  String DSR3_today, DSR3_tomorrow, DSR3_nextDay; //forcast day to be parsed into 3 letter abbreviation
  String DSR3_todayF, DSR3_tomorrowF, DSR3_nextDayF; //forecast data
  float DSR3_todayHighTemp, DSR3_tomorrowHighTemp, DSR3_nextDayHighTemp = 0.0;
  float DSR3_todayLowTemp, DSR3_tomorrowLowTemp, DSR3_nextDayLowTemp = 0.0;
  String DSR3_segment1 = "Current Forecast: ";
  String DSR3_colon = ": ";
  String DSR3_High_T = " H:";
  String DSR3_Low_T = " L:";
  
  String clearRow = "                    ";
//*********************LCD*********************

//******************Timers*********************

unsigned long TR_previousMillis = 0; //Take Reading BME280's Timer
unsigned long TR_interval = 3000; //Take Reading BME280's Timer

unsigned long ML_previousMillis = 0; //LCD Row 0 Move Letters
unsigned long ML_interval = 325; //LCD Row 0 Move Letters
unsigned long ML_currentMillis = 0;

unsigned long GDS_previousMillis = 0; //Get DarkSky Update
unsigned long GDS_interval = 300000;  //Every 5 minutes (300000 / 1000 / 60)

unsigned long DSR2_previousMillis = 0; //DarkSky LCD Row 2 timer
unsigned long DSR2_interval = 350;  //DarkSky LCD Row 2 timer
unsigned long DSR2_currentMillis = 0;

unsigned long DSR3_previousMillis = 0; //DarkSky LCD Row 3 timer
unsigned long DSR3_interval = 300;  //DarkSky LCD Row 3 timer
unsigned long DSR3_currentMillis = 0;

//******************Timers*********************

//**************************************************************
//**********************VOID SETUP******************************
//**************************************************************
void setup() {
  
Wire.begin();  //Start I2C

Serial.begin(230400);  //Fast to stop it holding up the stream

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
//Static IP address configuration
/*
IPAddress staticIP(192,168,1,55);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);
*/
const char* deviceName = "Jims_ESP8266";

 WiFi.disconnect();  //Prevent connecting to wifi based on previous configuration
 WiFi.hostname(deviceName);
 WiFi.mode(WIFI_STA); //This line hides the viewing of ESP as wifi hotspot
 //WiFi.config(staticIP, gateway, subnet);

 WiFi.begin(ssid, password);
 //WiFi.config(staticIP, gateway, subnet);

  
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
  
  takeReadingBME280(); //Read and Average BME280 measurements
  
  moveLetters(mlr0);  //LCD Row 0
  
  moveDarkSkyR2(segmentDSR2); //LCD Row 2
  
  moveDarkSkyR3(segmentDSR3); //LCD Row 3
  
  unsigned long GDS_currentMillis = millis();  // Get DarkSky Update every 5 minutes
  if (GDS_currentMillis - GDS_previousMillis > GDS_interval) {
      GDS_previousMillis = GDS_currentMillis;
    
      getDarkSky();  
    }
  }

//**************************************************************
//************************END VOID LOOP*************************
//**************************************************************
