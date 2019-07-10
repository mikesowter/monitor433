void output(unsigned long code, unsigned int length, unsigned int delay, unsigned int* raw, unsigned int protocol) {

char* lookup(uint32_t code);
char* toHex(uint32_t code);

  if (code == 0) {
    Serial.println("Unknown encoding");
  } else {
    strcpy(alarmText,toHex(code));
    strcat(alarmText," ");
    strcat(alarmText,lookup(code));
    for (int i=0;i<5;i++) thisText[i]=alarmText[i+7];
    if (strcmp(thisText, lastText)==0) {
      if (repCount++ < 3) writeFile();
    } else {
      repCount = 0;
      strcpy(lastText, thisText);
    }
  }
}
