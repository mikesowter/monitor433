
//----------------- open file for reading or appending

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
  fh.print(i2sd(day()));
  fh.print(" ");
  fh.print(i2sd(hour()));
  fh.print(":");
  fh.print(i2sd(minute()));
  fh.print(":");
  fh.print(i2sd(second()));
  fh.print("  ");
  fh.println(alarmText);
  yield();
}
