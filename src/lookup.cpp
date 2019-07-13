#include <arduino.h>

const uint8_t MAXALARMS = 25;
uint8_t match;
uint32_t iCode,mask;
extern char alarmID[];
char hexStr[]= "      ";

char* lookup(uint32_t code);
char* toHex(uint32_t code);

struct table {
  uint32_t code;
  String meaning;
} alarms[] = {
    {0xA38A51,"armed away FOB1"},
    {0xA38A52,"disarmed FOB1"},
    {0xA38A54,"armed home FOB1"},
    {0xA38A58,"SOS on FOB1"},
    {0x310021,"armed away FOB2"},
    {0x310022,"disarmed FOB2"},
    {0x310024,"armed home FOB2"},
    {0x310028,"SOS on FOB2"},
    {0xDCB622,"study PIR"},
    {0x886626,"stair PIR"},
    {0x43AE26,"dining PIR"},
    {0xF08626,"dungeon PIR"},
    {0xBBBBBB,"garage PIR"},
    {0xCA0466,"bike DOOR"},
    {0xD4C066,"pump DOOR"},
    {0xEDEC06,"front DOOR"},
    {0xBCEC06,"back DOOR"},
    {0x8FF406,"laundry DOOR"},
    {0x9AE5A8,"Dan's SMOKE"},
    {0x4EEEE8,"Court's SMOKE"},
    {0x3ABAE8,"dungeon SMOKE"},
    {0xA38A52,"Gayle's SMOKE"},
    {0xA38A58,"Gayle's PANIC"},
    {0x8FACBF,"System ALARM"},
    {0xD91006,"Dan's WINDOW"}};

char* lookup(uint32_t code) {
  for (int i=0;i<MAXALARMS;i++) {
    if (code == alarms[i].code) {
      alarms[i].meaning.toCharArray(alarmID,alarms[i].meaning.length()+1);
      return alarmID;
    }
  }
  for (int i=0;i<MAXALARMS;i++) {
    uint8_t match = 0;
    uint32_t mask = 0xF00000;
    iCode = alarms[i].code;
    for (int j=0;j<6;j++) {
      if ( (code&mask) ==  (iCode&mask) ) match++;
      if ( match > 4 ) {
        alarms[i].meaning.toCharArray(alarmID,alarms[i].meaning.length()+1);
        strcat(alarmID,(char*)" ??");
        return alarmID;
      }
      mask >>= 4;
    }
  }
  strcpy(alarmID,(char*)" is unknown");
  return alarmID;
}

char* toHex(uint32_t code) {
  for (int i=0;i<6;i++) {
    hexStr[i]=(0xF&(code>>(4*(5-i))))+'0';
    if (hexStr[i]>'9') hexStr[i] += 7; //convert 0X3A into 0x40
    Serial.print(hexStr[i]);
  }
  Serial.println();
  return hexStr;
}
