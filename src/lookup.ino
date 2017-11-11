const uint8_t num = 10;

struct table {
  uint32_t code;
  char  meaning[20];
} alarms[num] = {
    {0xDCB622,"study PIR"},
    {0x886626,"stair PIR"},
    {0x43AE26,"dining PIR"},
    {0xCA0466,"not used"},
    {0xD4C066,"not used"},
    {0xEDEC06,"front DOOR"},
    {0xBCEC06,"back DOOR"},
    {0xF08626,"pool PIR"},
    {0x8FF406,"laundry DOOR"}}; 

char* lookup(uint32_t code) {
  for (int i=0;i<num;i++) {
    if (code == alarms[i].code) return alarms[i].meaning;
  }
  return "unknown alarm";
}
