#include <Arduino.h>

unsigned long getTime() {

  while (udp.parsePacket()!= NTP_PACKET_SIZE) {
    sendNTPrequest(timeServerIP);
    delay(1000);
  }
  return getNTPreply();
}

// send an NTP request to the time server at the given address
unsigned long sendNTPrequest(IPAddress& address)
{
  memset(Buffer, 0, BUFFER_SIZE);
  // Initialize values needed to form NTP request
  Buffer[0] = 0b11100011;   // LI, Version, Mode
  Buffer[1] = 0;     // Stratum, or type of clock
  Buffer[2] = 6;     // Polling Interval
  Buffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  Buffer[12]  = 49;
  Buffer[13]  = 0x4E;
  Buffer[14]  = 49;
  Buffer[15]  = 52;
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(Buffer, NTP_PACKET_SIZE);
  udp.endPacket();
}

unsigned long getNTPreply(){
  udp.read(Buffer, NTP_PACKET_SIZE); // read the packet into the buffer
  unsigned long highWord = word(Buffer[40], Buffer[41]);
  unsigned long lowWord = word(Buffer[42], Buffer[43]);
  // this is NTP time :
  unsigned long secsSince1900 = highWord << 16 | lowWord;   // seconds since Jan 1 1900
  // now convert NTP time into Unix time:
  unsigned long GMT = secsSince1900 - 2208988800UL;         // seconds since Jan 1 1970
  //add timezone offset and return
  return GMT + timeZone*3600;
}

void dateStamp() {
  // display of the time on console
  Serial.println();
  Serial.print(year());
  Serial.print("/");
  Serial.print(p2d(month()));
  Serial.print("/");
  Serial.print(p2d(day()));
  Serial.print(" - ");
  timeStamp();
  Serial.println();
}

void timeStamp() {
  Serial.print(p2d(hour()));
  Serial.print(":");
  Serial.print(p2d(minute()));
  Serial.print(":");
  Serial.print(p2d(second()));
  Serial.print("  ");
}

// convert integer into a 2 char string dd
char* p2d(byte b) {
  d2Str[0]=b/10+'0';
  d2Str[1]=b%10+'0';
  return d2Str;
}