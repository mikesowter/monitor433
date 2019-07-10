#include <arduino.h>
#include <TimeLib.h>
#include <fs.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266FTPServer.h>
#include <WiFiUdp.h>
#include <ESP8266mDNS.h>
#include <Ticker.h>
#include <ArduinoOTA.h>
#include "secrets.h"
#include <RCSwitch.h>
extern "C" {
#include "user_interface.h"
}

ESP8266WebServer server( 80 );
FtpServer ftpSrv;
RCSwitch mySwitch = RCSwitch();
WiFiUDP udp;
WiFiClient client;
time_t getNtpTime();
FSInfo fs_info;
File fh,fd,fe;
Ticker secondTick;
volatile int watchDog = 0;

char fileName[] = "/XXyymmdd.csv";
char charBuf[128];
char alarmText[40];
String resetReason = "restart: " + ESP.getResetReason();
char thisText[6],lastText[]="12345";
uint8_t repCount=0;

unsigned long t0, t1, minMillis, startMillis, startSeconds, midNight;
uint8_t oldMin, oldQtr, oldHour, oldDay, oldMonth;
unsigned int localPort = 2391;   //  a random local port to listen for UDP packets

const char* ntpServerName = "au.pool.ntp.org";
const int HTML_SIZE = 10000;
char htmlStr[HTML_SIZE];        // use C strings for storage efficiency
int htmlLen;
const int NTP_PACKET_SIZE = 48;
const int BUFFER_SIZE = 128;
const int ISR_CAP = 128;
byte buffer[BUFFER_SIZE];
const int TIMEZONE = 10;
