#include <arduino.h>
#include <fs.h>
#include <ESP8266WebServer.h>
#include "functions.h"

void addCstring(const char* s);

extern char longStr[];
extern File fh;
extern FSInfo fs_info;
extern ESP8266WebServer server;
extern char fileName[],charBuf[],fileSizeStr[];
extern int htmlLen;
extern uint16_t longStrLen;

void handleRoot() {
  char line[80];
  longStr[0]='\0';
  if(!fh.seek(-9900,SeekCur)) fh.seek(0,SeekSet);
  while (fh.available()) {
    int k=fh.readBytesUntil('\r',line,79);
    line[k]='\0';
    addCstring(line);
  }
  server.send ( 200, "text/plain", longStr );
}

void handleDir() {
  longStr[0]='\0';
  ltoa(fs_info.usedBytes,fileSizeStr,10);
  addCstring(ltoa(fs_info.usedBytes,fileSizeStr,10));
	addCstring(" bytes used:\n");
  Dir dir = SPIFFS.openDir("/");
  while (dir.next()) {
    dir.fileName().toCharArray(fileName, 14);
    addCstring("\n");
    addCstring(fileName);
    addCstring("\t");
    itoa(dir.fileSize(),fileSizeStr,10);
    addCstring(fileSizeStr);
  }
  server.send ( 200, "text/plain", longStr );
  //Serial.println(longStr);
}

void handleDel() {
  fh.close();
  SPIFFS.remove("/alarms.csv");
  fh = SPIFFS.open("/alarms.csv", "a+");
  strcpy(charBuf,"<!DOCTYPE html><html><head><HR>Alarms deleted<HR></head></html>");
  server.send ( 200, "text/html", charBuf );
}

void helpPage() {
  longStr[0]='\0';
  addCstring("<!DOCTYPE html><html><body><HR>");
  addCstring("Valid options include:");
  addCstring("<P>");
  addCstring("del");
  addCstring("<P>");
  addCstring("dir");
  addCstring("<P>");
  addCstring("dump");
  addCstring("<HR>");
  addCstring("filename.xyz");
  addCstring("<P>");
  addCstring( "<HR></body></html>" );
  server.send ( 200, "text/html", longStr );
}

void handleNotFound() {
  helpPage();
}

void addCstring(const char* s) {
  // find end of longStr
  uint16_t p;
  for (p=0; p<longStrLen; p++) {
    if ( p > longStrLen-32) {
      Serial.println("long string exceeded");
      break;
    }
    if (longStr[p]=='\0') {
      break;    // p now points to end of old string
    }
  }
  uint16_t q=0;
  for (; p<longStrLen; p++) {
    longStr[p]=s[q];
//    if (s[q]!='\0') Serial.print(s[q]);
    if (s[q++]=='\0') break;
  }
  htmlLen = p;
}
