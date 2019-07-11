#include <arduino.h>
#include <fs.h>

void diagMess(const char* mess);
char* i2sd(uint8_t b);
char* f2s2(float f);
uint8_t openFile(const char* s);
char* dateStamp();
char* timeStamp();

extern File fh;
extern char alarmText[40];

byte openFile(char* fileName) {
  fh = SPIFFS.open(fileName, "a+");
  if (!fh) {
    Serial.print(fileName);
    Serial.println(" failed to open");
    return 0;
  }
  return 1;
}

void writeFile() {
  fh.printf("%s %s %s\n",dateStamp(),timeStamp(),alarmText);
  yield();
}
