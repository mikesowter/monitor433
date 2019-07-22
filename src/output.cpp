#include <arduino.h>

char* lookup(uint32_t code);
char* toHex(uint32_t code);
void writeFile();

uint8_t repCount=0;
extern char thisText[],lastText[],alarmText[];

void output(unsigned long code, unsigned int length, unsigned int delay, unsigned int* raw, unsigned int protocol) {
  if (code == 0) {
    Serial.printf("Unknown encoding! length:%u, raw:%u, protocol:%u\n",length,raw,protocol);
  } else {
    strcpy(alarmText,toHex(code));
    strcat(alarmText," ");
    strcat(alarmText,lookup(code));
    Serial.println(alarmText);
    // eliminate excess triggers
    for (int i=0;i<5;i++) thisText[i] = alarmText[i+7];
    if (strcmp(thisText, lastText)==0) {
      if (repCount++ < 3) writeFile();
    } else {
      repCount = 0;
      strcpy(lastText, thisText);
    }
  }
}
