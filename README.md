# Wemos_dual_BME280_4_row_scrolling_lcd with Dark Sky weather data
This is a significantly more capable remake of the Recording Hygrothermograph project here - https://github.com/jlmyra/Recording_HygroThermograph. This version replaces the Arduino 2560, ethernet controller and hacked
router with a Wemos D1 mini. In addition the 2 x 16 display is repleced with a 4 x 20 I2C display. Two rows are used to display data from the dual BME280's and two rows are used to display weather forecast information from Dark Sky. The sketch incorporates functions that scroll the data on 3 lines of the LCD, get time from an NTP server, gets weather data from Dark Sky, and organizes the sketch via multi-tab in the Arduino IDE.
