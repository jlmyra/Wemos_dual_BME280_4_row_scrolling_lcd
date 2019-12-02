
void checkWiFi(){
  Serial.print ("Checking wifi");
    int x = 0;
    if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to wifi: "); Serial.println(ssid);
    //WiFi.begin(ssid, password);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
    WiFi.reconnect();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("  Attempting WiFi   ");
    lcd.setCursor(0,1);
    lcd.print("     connection     ");
    
    x = 1;
    
   if (WiFi.status() == WL_IDLE_STATUS) {
    Serial.println("WiFi WL_IDLE_STATUS");
    lcd.setCursor(0,3);
    lcd.print("WiFi WL_IDLE_STATUS");
  }
  if (WiFi.status() == WL_CONNECTION_LOST) {
    Serial.println("WiFi WL_CONNECTION_LOST");
    lcd.setCursor(0,3);
    lcd.print("WiFi WL_CONNECTION_LOST");
  }
  if (WiFi.status() == WL_CONNECT_FAILED) {
    Serial.println("WiFi WL_CONNECT_FAILED");
    lcd.setCursor(0,3);
    lcd.print("WiFi WL_CONNECT_FAILED");
  }
  if (WiFi.status() == WL_DISCONNECTED) {
    Serial.println("WiFi WL_DISCONNECTED");
    lcd.setCursor(0,3);
    lcd.print("WiFi WL_DISCONNECTED");
  }
    while(WiFi.status() != WL_CONNECTED){
      if ( x == 11) {
        while (1);
        }
    lcd.setCursor(0,2);
    lcd.print("attempt: ");
    lcd.print(" ");
    delay(500); 
    lcd.setCursor(10,2);
    lcd.print(x);
    delay(1000);
    
    Serial.print(x); 
    x = x + 1;    
      } 
    }
    
  if(x>0){
  Serial.println();
    }
   //Connect or reconnect to WiFi
  if(WiFi.status() == WL_CONNECTED) {
    Serial.println("  WiFi CONNECTED; ");
    }
  
  }

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
 
