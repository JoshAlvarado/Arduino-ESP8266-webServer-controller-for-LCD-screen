//Joshua Alvarado
//8/31/2020
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD
#include <ESP8266HTTPClient.h>
#include "AnotherIFTTTWebhook.h"
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,16,2); 

const char WiFiPassword[] = "xxx"; //wifi name
const char AP_NameChar[] = "xxx" ; // wifi password
#define IFTTT_Key "xxx" //IFTTT to notify you that the screen really changed
#define IFTTT_Event "xxx" 
WiFiServer server(80);
 
String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String html_1 = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'/><meta charset='utf-8'><style>body {font-size:140%;} #main {display: table; margin: auto;  padding: 0 10px 0 10px; } h2,{text-align:center; } .button { padding:10px 10px 10px 10px; width:100%;  background-color: #4CAF50; font-size: 120%;}</style><title>Josh's control Panel </title></head><body><div id='main'><h2>JOSH'S CONTROL PANEL</h2>";
String html_2 = "<form id='F1' action='CLASS'><input class='button' type='submit' value='IN CLASS' ></form><br><form id='F2' action='RECORDING'><input class='button' type='submit' value='RECORDING' ></form><br>";
String html_3 = "<form id='F2' action='MEETING'><input class='button' type='submit' value='IN MEETING' ></form><br><form id='F2' action='XXXX'><input class='button' type='submit' value='XXXX' ></form><br><form id='F2' action='YELLING'><input class='button' type='submit' value='NO YELLING' ></form><br><form id='F2' action='ANNOYING'><input class='button' type='submit' value='ANNOYING' ></form><br><form id='F2' action='CLEAR'><input class='button' type='submit' value='CLEAR THIS' ></form><br>";
String html_4 = "</div></body></html>";
// html_2&3 are both buttons for request
String request = "";

 
void setup() 
{
    Serial.begin(9600);
  Serial.println();
  Serial.print("Wifi connecting to ");
  Serial.println( WiFiPassword );

  WiFi.begin(WiFiPassword,AP_NameChar);

  Serial.println();
  Serial.print("Connecting");

  while( WiFi.status() != WL_CONNECTED ){
      delay(500);
      Serial.print(".");        
  }

  Serial.println();

  Serial.println("Wifi Connected Success!");
  Serial.print("NodeMCU IP Address : ");
  Serial.println(WiFi.localIP() );


  
  boolean conn = WiFi.softAP(AP_NameChar, WiFiPassword);
  server.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("CONNECTED");
  delay(1000);
  lcd.clear();
} // void setup()
 
 
 
void loop() 
{
 
    // Check if a client has connected
    WiFiClient client = server.available();
    if (!client)  {  return;  }
 
    // Read the first line of the request
    request = client.readStringUntil('\r');
 
    if       ( request.indexOf("CLASS") > 0 )  { 
      lcd.setCursor(0, 0);
      lcd.print("I'M IN CLASS");
      lcd.setCursor(0, 1);
      lcd.print("RIGHT NOW");
      send_webhook(IFTTT_Event,IFTTT_Key,"SCREEN CHANGED IN CLASS","value 2","value 3");
    }
    else if  ( request.indexOf("MEETING") > 0 ) {
      lcd.setCursor(0, 0);
      lcd.print("I'M IN A MEETING");
      lcd.setCursor(0, 1);
      lcd.print("RIGHT NOW");
      send_webhook(IFTTT_Event,IFTTT_Key,"SCREEN CHANGED IN MEETING","value 2","value 3");
      }
    if       ( request.indexOf("CLEAR") > 0 )  { 
      lcd.clear();
      send_webhook(IFTTT_Event,IFTTT_Key,"SCREEN CHANGED CLEAR","value 2","value 3");
    }
    else if ( request.indexOf("XXXX") > 0) {
      lcd.setCursor(0, 0);
      lcd.print("I'M XXXX");
      lcd.setCursor(0, 1);
      lcd.print("RIGHT NOW");
      send_webhook(IFTTT_Event,IFTTT_Key,"SCREEN CHANGED XXXX","value 2","value 3");
    }
    if       ( request.indexOf("RECORDING") > 0 )  { 
      lcd.setCursor(0, 0);
      lcd.print("I'M RECORDING");
      lcd.setCursor(0, 1);
      lcd.print("RIGHT NOW");
      send_webhook(IFTTT_Event,IFTTT_Key,"SCREEN CHANGED RECORDING","value 2","value 3");
      }
    else if  ( request.indexOf("YELLING") > 0 ) {
      lcd.setCursor(0, 0);
      lcd.print("I'LL DO IT LATER");
      lcd.setCursor(0, 1);
      lcd.print("LEAVE ME ALONE");
      send_webhook(IFTTT_Event,IFTTT_Key,"SCREEN CHANGED YELLING","value 2","value 3");
    }
    if       ( request.indexOf("ANNOYING") > 0 )  { 
      lcd.setCursor(0, 0);
      lcd.print("YOU GUYS ARE ");
      lcd.setCursor(0, 1);
      lcd.print("ANNOYING");
      send_webhook(IFTTT_Event,IFTTT_Key,"SCREEN CHANGED ANNOYING","value 2","value 3");
      }

 
    client.print( header );
    client.print( html_1 );
    client.print( html_2 );
    client.print( html_3 );
    client.print( html_4);
 

  // The client will actually be disconnected when the function returns and 'client' object is detroyed
 
} // void loop()
