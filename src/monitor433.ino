
#include <RCSwitch.h>
#include <monitor433.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  secondTick.attach(1,ISRwatchDog);

  Serial.begin(115200);
  Serial.println("\n433MHz monitor V1.0  2017-12-12");
  Serial.println(ESP.getResetReason());
  Serial.println(ESP.getCoreVersion());
//  Serial.println(ESP.getSdkVersion());
//  Serial.println(ESP.getFlashChipSize());
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

  //if(!SPIFFS.format()||!SPIFFS.begin())     //use to format SPIFFS drive
  if(!SPIFFS.begin())
  {
    Serial.println("SPIFFS.begin failed");
  }
  SPIFFS.info(fs_info);
  Serial.print(fs_info.totalBytes);
  Serial.println(" bytes available");
  Serial.print(fs_info.usedBytes);
  Serial.println(" bytes used:");
  openFile("/alarms.csv");

  server.on ( "/", handleRoot );
  server.on ( "/del", handleDel );
  server.on ( "/dir", handleDir );
  server.on ( "/dump", handleDump );
  server.onNotFound ( handleNotFound );
  server.begin();
  Serial.println ( "HTTP server started" );
  server.handleClient();

  mySwitch.enableReceive(5);  // Receiver on interrupt 0 => that is pin #2
}

void loop() {
  if (mySwitch.available()) {
    timeStamp();
    output(mySwitch.getReceivedValue(), mySwitch.getReceivedBitlength(), mySwitch.getReceivedDelay(), mySwitch.getReceivedRawdata(),mySwitch.getReceivedProtocol());
    mySwitch.resetAvailable();
    delay(5000);
  }
  watchDog=0;
  // check for OTA
  ArduinoOTA.handle();
  server.handleClient();
  fh.flush();
}

void ISRwatchDog () {
  noInterrupts();
  watchDog++;
	if (watchDog == 30) {
    Serial.println("watchDog 30s alert");
  }
  if (watchDog >= 60) {
    Serial.println("watchDog 60s reset");
    fh.close();
    ESP.restart();
  }
  interrupts();
}
