#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "TestMyCar"   //SSID
#define APPSK  "00000000" //Password
#endif

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

int PIN_Motor_Left_0 = 14;
int PIN_Motor_Left_1 = 12;

int PIN_Motor_Right_0 = 13;
int PIN_Motor_Right_1 = 15;

int PIN_Motor_Up_0 = 0;
int PIN_Motor_Up_1 = 2;

String cssButton1 = "style='text-transform: uppercase; font-weight: bold; background: #3f51b5; padding: 10px 20px; width: 100%; text-decoration: none; color: #fff; border-radius: 10px 0px 0px 10px;'";
String cssButton2 = "style='text-transform: uppercase; font-weight: bold; background: #f44336; padding: 10px 20px; width: 100%; text-decoration: none; color: #fff; '";
String cssButton3 = "style='text-transform: uppercase; font-weight: bold; background: #3f51b5; padding: 10px 20px; width: 100%; text-decoration: none; color: #fff; border-radius: 0px 10px 10px 0px;'";

String cssButton10 = "style='text-transform: uppercase; font-weight: bold; background: #03a9f4; padding: 10px 20px; width: 100%; text-decoration: none; color: #fff; border-radius: 10px 0px 0px 10px;'";
String cssButton30 = "style='text-transform: uppercase; font-weight: bold; background: #03a9f4; padding: 10px 20px; width: 100%; text-decoration: none; color: #fff; border-radius: 0px 10px 10px 0px;'";
String cssButton4 = "style='text-transform: uppercase; font-weight: bold; background: #03a9f4; padding: 10px 20px; width: 100%; text-decoration: none; color: #fff; border-radius: 10px 10px 0 0;'";
String cssButton5 = "style='text-transform: uppercase; font-weight: bold; background: #03a9f4; padding: 10px 20px; width: 100%; text-decoration: none; color: #fff; border-radius: 0 0 10px 10px;'";


String htmlHeadr = "<meta name='viewport' content='width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no' />";
String htmlTop = "<center><h2><a style='text-decoration: none;' href='/'>Custom Forklift App</a></h2></center>";
String htmlElevator = "<hr><center><b>Elevator:</b><br><br> <a " +cssButton1+ " href='/motorUpUp'>Up</a> <a " +cssButton2+ " href='/motorUpStop'>Stop</a> <a " +cssButton3+ " href='/motorUpDown'>Down</a> </center> <br>";

String htmlMoving = "<hr><center> <br><br> <a " +cssButton4+ " href='/motorFata'>Front</a> <br><br><br> <a " +cssButton10+ " href='/motorLeft'>Left&nbsp;</a> <a " +cssButton2+ " href='/motorStop'>Stop</a> <a " +cssButton30+ " href='/motorRight'>Right</a> <br><br><br> <a " +cssButton5+ " href='/motorSpate'>Rear</a> </center> <br>";

String htmlEnd = "<hr>";
void serverReponseFull(){
  server.send(200, "text/html", htmlHeadr + htmlTop +htmlElevator + htmlMoving + htmlEnd);
}
void serverReponseFull(String custom){
  server.send(200, "text/html", htmlHeadr + htmlTop +htmlElevator + htmlMoving + htmlEnd);
}

void handleRoot() {
  serverReponseFull();
}
void motorUpUp(){
  digitalWrite(PIN_Motor_Up_0, false);
  digitalWrite(PIN_Motor_Up_1, true); 
  serverReponseFull();
}
void motorUpStop(){
  digitalWrite(PIN_Motor_Up_0, false);
  digitalWrite(PIN_Motor_Up_1, false); 
  serverReponseFull();
}
void motorUpDown(){
  digitalWrite(PIN_Motor_Up_0, true);
  digitalWrite(PIN_Motor_Up_1, false); 
  serverReponseFull();
}

void motorFata(){
  digitalWrite(PIN_Motor_Left_0, true);
  digitalWrite(PIN_Motor_Left_1, false);
  digitalWrite(PIN_Motor_Right_0, true);
  digitalWrite(PIN_Motor_Right_1, false);
  serverReponseFull();
}
void motorSpate(){
  digitalWrite(PIN_Motor_Left_0, false);
  digitalWrite(PIN_Motor_Left_1, true);
  digitalWrite(PIN_Motor_Right_0, false);
  digitalWrite(PIN_Motor_Right_1, true);
  serverReponseFull();
}
void motorLeft(){
  digitalWrite(PIN_Motor_Left_0, true);
  digitalWrite(PIN_Motor_Left_1, false);
  digitalWrite(PIN_Motor_Right_0, false);
  digitalWrite(PIN_Motor_Right_1, true);
  serverReponseFull();
}
void motorRight(){
  digitalWrite(PIN_Motor_Left_0, false);
  digitalWrite(PIN_Motor_Left_1, true);
  digitalWrite(PIN_Motor_Right_0, true);
  digitalWrite(PIN_Motor_Right_1, false);
  serverReponseFull();
}
void motorStop(){
  digitalWrite(PIN_Motor_Left_0, false);
  digitalWrite(PIN_Motor_Left_1, false);
  digitalWrite(PIN_Motor_Right_0, false);
  digitalWrite(PIN_Motor_Right_1, false);
  serverReponseFull();
}

void setup() {
  
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  pinMode(PIN_Motor_Left_0, OUTPUT);
  pinMode(PIN_Motor_Left_1, OUTPUT);
  pinMode(PIN_Motor_Right_0, OUTPUT);
  pinMode(PIN_Motor_Right_1, OUTPUT);
  pinMode(PIN_Motor_Up_0, OUTPUT);
  pinMode(PIN_Motor_Up_1, OUTPUT);
  Serial.println("Motors are ready to use.");


  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/motorUpUp", motorUpUp);
  server.on("/motorUpStop", motorUpStop);
  server.on("/motorUpDown", motorUpDown);

  server.on("/motorFata", motorFata);
  server.on("/motorSpate", motorSpate);
  server.on("/motorLeft", motorLeft);
  server.on("/motorRight", motorRight);
  server.on("/motorStop", motorStop);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();

}
