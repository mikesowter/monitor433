#include <arduino.h>
#include <fs.h>

void diagMess(const char* mess);
char* i2sd(uint8_t b);
char* f2s2(float f);
uint8_t openFile(const char* s);
char* dateStamp();
char* timeStamp();

extern File fh;
extern char alarmText[];

void writeFile() {
  fh.printf("%s %s %s\n",dateStamp(),timeStamp(),alarmText);
  yield();
}
