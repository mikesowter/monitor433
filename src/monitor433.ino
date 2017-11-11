/*
  Example for receiving

  https://github.com/sui77/rc-switch/

  If you want to visualize a telegram copy the raw data and
  paste it into http://test.sui.li/oszi/
*/

#include <RCSwitch.h>
#include <monitor433.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  secondTick.attach(1,ISRwatchDog);

  Serial.begin(115200);
  Serial.println("\n433MHz monitor V1.0  2017-11-12");
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("local IP address: ");
  localIP=WiFi.localIP();
  Serial.print(localIP);
  long rssi = WiFi.RSSI();
  Serial.print("    signal strength ");
  Serial.print(rssi);
  Serial.println(" dBm");
  watchDog=0;
  init_OTA();

  udp.begin(localPort);
  WiFi.hostByName(ntpServerName, timeServerIP);
  WiFi.hostByName(ftpServerName, fileServerIP);
  // Set epoch and timers
  startSeconds=getTime();
  setTime(startSeconds);
  //setTime(23,59,30,30,11,2016);
  startMillis = millis();
  dateStamp();

  mySwitch.enableReceive(5);  // Receiver on interrupt 0 => that is pin #2
}

void loop() {
  if (mySwitch.available()) {
    timeStamp();
    output(mySwitch.getReceivedValue(), mySwitch.getReceivedBitlength(), mySwitch.getReceivedDelay(), mySwitch.getReceivedRawdata(),mySwitch.getReceivedProtocol());
    mySwitch.resetAvailable();
  }
  watchDog=0;
  // check for OTA
  ArduinoOTA.handle();
}

void ISRwatchDog () {
  noInterrupts();
  watchDog++;
	if (watchDog == 30) {
    Serial.println("watchDog 30s alert");
  }
  if (watchDog >= 60) {
    Serial.println("watchDog 60s");
    ESP.restart();
  }
  interrupts();
}
