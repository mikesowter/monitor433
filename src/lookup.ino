const uint8_t num = 15;
uint8_t match;
uint32_t iCode,mask;
char  guess[30];

struct table {
  uint32_t code;
  char  meaning[20];
} alarms[num] = {
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
    {0xA38A58,"Gayle's SMOKE"},
    {0xAAAAAA,"Dan's WINDOW"}};

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
  return "unknown alarm";
}
