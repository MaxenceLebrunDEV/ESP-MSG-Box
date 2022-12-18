#include <EEPROM.h>
#include <ESP_WiFiManager.h>
#include <ESP_WiFiManager.hpp>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;

byte heart[8] = {
    0b00000,
    0b01010,
    0b11111,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000
};

ESP8266WebServer server(80);

void onscreen(String msg){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(msg);
}

void handleRoot() {  
  server.send(200, "text/html", "<!DOCTYPE html>\
<html>\
<head>\
  <title>MDEV Wi-Fi</title>\
  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
<style>\
html {\
  font-family: Arial, Helvetica, sans-serif; \
  display: inline-block; \
  text-align: center;\
}\
h1 {\
  font-size: 1.8rem; \
  color: white;\
}\
p {\ 
  font-size: 1.4rem;\
}\
.topnav {\ 
  overflow: hidden; \
  background-color: #0A1128;\
}\
body {  \
  margin: 0;\
}\
.content { \
  padding: 5%;\
}\
.card-grid { \
  max-width: 800px; \
  margin: 0 auto;\ 
  display: grid; \
  grid-gap: 2rem; \
  grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));\
}\
.card { \
  background-color: white; \
  box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);\
}\
.card-title { \
  font-size: 1.2rem;\
  font-weight: bold;\
  color: #034078;\
}\
input[type=submit] {\
  border: none;\
  color: #FEFCFB;\
  background-color: #034078;\
  padding: 15px 15px;\
  text-align: center;\
  text-decoration: none;\
  display: inline-block;\
  font-size: 16px;\
  width: 100px;\
  margin-right: 10px;\
  border-radius: 4px;\
  transition-duration: 0.4s;\
  }\
input[type=submit]:hover {\
  background-color: #1282A2;\
}\
input[type=text], input[type=number], select {\
  width: 50%;\
  padding: 12px 20px;\
  margin: 18px;\
  display: inline-block;\
  border: 1px solid #ccc;\
  border-radius: 4px;\
  box-sizing: border-box;\
}\
label {\
  font-size: 1.2rem;\ 
}\
.value{\
  font-size: 1.2rem;\
  color: #1282A2;  \
}\
.state {\
  font-size: 1.2rem;\
  color: #1282A2;\
}\
button {\
  border: none;\
  color: #FEFCFB;\
  padding: 15px 32px;\
  text-align: center;\
  font-size: 16px;\
  width: 100px;\
  border-radius: 4px;\
  transition-duration: 0.4s;\
}\
.button-on {\
  background-color: #034078;\
}\
.button-on:hover {\
  background-color: #1282A2;\
}\
.button-off {\
  background-color: #858585;\
}\
.button-off:hover {\
  background-color: #252524;\
}\
</style>\
</head>\
<body>\
  <div class=\"topnav\">\
    <h1>MDEV Manager</h1>\
  </div>\
  <div class=\"content\">\
    <div class=\"card-grid\">\
      <div class=\"card\">\
        <form action=\"/\" method=\"POST\">\
          <p>\
            <label for=\"ssid\">SSID</label>\
            <input type=\"text\" id=\"ssid\" name=\"ssid\"><br>\
            <label for=\"pass\">Password</label>\
            <input type=\"text\" id=\"pass\" name=\"pass\"><br>\
            <input type =\"submit\" value =\"Submit\">\
          </p>\
        </form>\
      </div>\
    </div>\
  </div>\
</body>\
</html>\
");
}

void handleNotFound() {
  String message = "Erreur 404\n\n";
  server.send(404, "text/plain", message);
}


void send(){
    lcd.createChar(0, heart);
    
    onscreen("By:");
    lcd.print(server.client().remoteIP());
    lcd.setCursor(0, 1);
    lcd.print("I ");
    lcd.write((unsigned char)0);
    lcd.print(" Coffee ! ");

}
void connect(){
  onscreen("Connecting");
  delay(300);
  onscreen("Connecting.");
  delay(300);
  onscreen("Connecting..");
  delay(300);
  onscreen("Connecting...");
  delay(300);
  onscreen("Connecting.");
  delay(300);
  onscreen("Connecting..");
  delay(300);
  onscreen("Connecting...");
  delay(300);
}
void connected(){
 onscreen("Connected");
  delay(3000);
}

void setup(void) {
    Serial.begin(115200);
  delay(3000);
  EEPROM.begin(512);
  Serial.setDebugOutput(true);
    lcd.begin(16, 2);
    lcd.setRGB(255, 0, 255);
    lcd.setCursor(0, 0);

String esid;
  for (int i = 0; i < 32; ++i)
  {
    esid += char(EEPROM.read(i));
  }
   String epass = "";
  for (int i = 32; i < 96; ++i)
  {
    epass += char(EEPROM.read(i));
  }
  WiFi.begin(esid, epass);
  onscreen(esid);
  server.on("/", handleRoot);
  server.on("/send", send);
  server.onNotFound(handleNotFound);
  server.begin();
  
  
}

void loop(void) {
  server.handleClient();
}
