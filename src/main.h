#include <arduino.h>
#include <TimeLib.h>
#include <fs.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266FTPServer.h>
#include <WiFiUdp.h>
#include <ESP8266mDNS.h>
#include <Ticker.h>
#include <ArduinoOTA.h>
#include <RCSwitch.h>
extern "C" {
#include "user_interface.h"
}

ESP8266WebServer server( 80 );
FtpServer ftpSrv;
RCSwitch mySwitch = RCSwitch();
time_t getNtpTime();
FSInfo fs_info;
File fh,fd,fe;
Ticker secondTick;
volatile int watchDog = 0;

char charBuf[128],dateStr[10],timeStr[10],fileSizeStr[10],fileName[14];
char alarmText[50],alarmID[30];
String resetReason = "restart: " + ESP.getResetReason();
char thisText[6],lastText[]="12345";

unsigned long t0, t1, minMillis, startMillis, midNight;
uint8_t oldMin, oldQtr, oldHour, oldDay, oldMonth;

const char* ntpServerName = "au.pool.ntp.org";
uint16_t longStrLen = 10000;
char longStr[10000];        // use C strings for storage efficiency
int htmlLen;
const int NTP_PACKET_SIZE = 48;
const int BUFFER_SIZE = 128;
const int ISR_CAP = 128;
byte buffer[BUFFER_SIZE];
const int TIMEZONE = 10;
