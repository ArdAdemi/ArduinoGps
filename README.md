# ArduinoGps
Arduino GPS Tracker with NEO-6M (WEBMOS D1 board)

Webmos board D1 is essentially an Arduino with a esp8266 sensor and the pins on arduino boards are not the same as in webmos d1. In this project I am using Webmos D1 board and GPS NEO-6M GPS to make a simple GPS tracker that send request to an endpoint in API. With this GPS you can find location the speed that you have if traveling and the altitude, you can see all the method that you can use in http://arduiniana.org/libraries/tinygpsplus/  which is e library for NEO-6M Gps

You can see how to connect Webmos D1 board with NEO-M
![alt text](https://image.ibb.co/dpOMGp/Webmos_d1.png)

Library that were used:

TinyGPS++;
SoftwareSerial;
ESP8266HTTPClient;
ESP8266WiFi;
ArduinoJson;
SoftwareSerial;
