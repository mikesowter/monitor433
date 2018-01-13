const uint8_t num = 25;
uint8_t match;
uint32_t iCode,mask;
char  guess[30];

struct table {
  uint32_t code;
  char  meaning[20];
} alarms[] = {
    {0x367851,"armed away FOB1"},
    {0x367852,"disarmed FOB1"},
    {0x367854,"armed home FOB1"},
    {0x367858,"SOS on FOB1"},
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
  for (int i=0;i<num;i++) {
    if (code == alarms[i].code) return alarms[i].meaning;
  }
  for (int i=0;i<num;i++) {
    match = 0;
    mask = 0xF00000;
    iCode = alarms[i].code;
    strcpy(guess,alarms[i].meaning);
    strcat(guess," ??");
    for (int j=0;j<6;j++) {
      if ((code&mask)==(iCode&mask)) if (++match > 4) return guess;
      mask >>= 4;
    }
  }
  return " is unknown";
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
