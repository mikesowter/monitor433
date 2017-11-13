
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

void writeFile(char* alarm) {
  fh.print(p2d(day()));
  fh.print(" ");
  fh.print(p2d(hour()));
  fh.print(":");
  fh.print(p2d(minute()));
  fh.print(":");
  fh.print(p2d(second()));
  fh.print("  ");
  fh.println(alarm);
  yield();
}
