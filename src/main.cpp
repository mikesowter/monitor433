#include "main.h"
#include "functions.h"

void setup() {
  Serial.begin(115200);
  Serial.println("\n433MHz monitor V2.0  2019-07-10");
	// join local network and internet
	joinNet();
	// setup over the air updates
	init_OTA();
	// setup watch dog
	secondTick.attach(1,ISRwatchDog);
	// Set epoch and timers
	setupTime();
	// setup server responses
	setupServer();
	// setup file system and diag files
	setupSPIFFS();
	// setup FTP server
	ftpSrv.begin("mike","iron");
  // setup radio interface
  mySwitch.enableReceive(5);      // Receiver on interrupt 0 => that is pin #2
	// lookup reason for restart
	resetReason.toCharArray(charBuf,resetReason.length()+1);
  diagMess(charBuf);              // restart message
	startMillis = millis();
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
