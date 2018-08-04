#include <arduino.h>
#include <TimeLib.h>
#include <fs.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <ESP8266mDNS.h>
#include <Ticker.h>
#include <ArduinoOTA.h>
extern "C" {
#include "user_interface.h"
}

ESP8266WebServer server ( 80 );
WiFiUDP udp;
WiFiClient client,dclient;
time_t getNtpTime();
FSInfo fs_info;
File fh;
Ticker secondTick;
volatile int watchDog = 0;

char fileName[] = "/XXyymmdd.csv";
char alarmText[40];
unsigned long getTime();
unsigned long sendNTPrequest(IPAddress& address);
unsigned long getNTPreply();

char ssid[] = "TelstraCF6EC7";
char pass[] = "meauff8qqwn9";        //  your network password
char d2Str[] = "12";
char d8Str[] = "12345.78";
char hexStr[]= "      ";
char thisText[6],lastText[]="12345";
uint8_t repCount=0;

unsigned long t0, t1, minMillis, startMillis, startSeconds, midNight;
unsigned int localPort = 2391;   //  a random local port to listen for UDP packets

IPAddress localIP,timeServerIP,fileServerIP;
IPAddress ip(192, 168, 1, 55);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(192, 168, 1, 1);
const char* ntpServerName = "au.pool.ntp.org";
const char* ftpServerName = "ftp.sowter.com";
const int HTML_SIZE = 10000;
char htmlStr[HTML_SIZE];        // use C strings for storage efficiency
int htmlLen;
const int NTP_PACKET_SIZE = 48;
const int BUFFER_SIZE = 128;
const int ISR_CAP = 128;
byte buffer[BUFFER_SIZE];
char outBuf[128];               // for ftpRcv and errMessage
const int TIMEZONE = 10;
