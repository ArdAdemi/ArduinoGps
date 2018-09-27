#include "TinyGPS++.h"
#include "SoftwareSerial.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include<SoftwareSerial.h>


SoftwareSerial serial_connection(0,1); //RX=pin TX-D1 ; TX=pin D8
TinyGPSPlus gps;//This is the GPS object
void setup()
{
  Serial.begin(115200);//This opens up communications to the Serial monitor in the Webmos d1 board
  serial_connection.begin(9600);//This opens up communications to the NEO-6M GPS Module 
  Serial.println("GPS Start");//Just show to the monitor that the sketch has started
   WiFi.begin("name", "password");   // Write name of your wifi and password
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
 
  }
}
void loop()
{
  while(serial_connection.available())//While there are characters to come from the GPS
  {
    gps.encode(serial_connection.read());//This feeds the serial NMEA data into the library one char at a time
  }
  if(gps.location.isUpdated())//This will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in
  {
   float latitude=gps.location.lat();
   float longitude=gps.location.lng();
    if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
     StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
     JsonObject& JSONencoder = JSONbuffer.createObject(); 
    
     JSONencoder["id"] = 7; //this is the id to know the gps that is sending the data
     JSONencoder["longitude"] =latitude; //this is the latitude
     JSONencoder["latitude"]=longitude;  //this is longitude
     char JSONmessageBuffer[300];
     JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
     
     HTTPClient http;    //Declare object of class HTTPClient
 
     http.begin("Write your endpoint");     //Specify request destination for example "http://192.168.43.167:8000/api/v1/petlocation"
     http.addHeader("Content-Type", "application/json");  //Specify content-type header
 
     int httpCode = http.POST(JSONmessageBuffer);   //Send the request
     String payload = http.getString();                                        //Get the response payload
 
     Serial.println(httpCode);   //Print HTTP return code
     Serial.println(payload);    //Print request response payload
 
     http.end();  //Close connection
 
  } else {
     Serial.println("Error in WiFi connection");
  }
  delay(30000);  //Send a request every 30 seconds (30000)
  }
}
