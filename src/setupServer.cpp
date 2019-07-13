#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

extern ESP8266WebServer server;

void handleRoot();
void handleNotFound();
void handleDel();
void handleDir();

void setupServer() {
  server.on ( "/", handleRoot );
  server.on ( "/del", handleDel );
  server.on ( "/dir", handleDir );
  server.onNotFound ( handleNotFound );
  server.begin();
  Serial.println( "server started" );
  if ( MDNS.begin ( "mon433" ) ) {
    Serial.print("mDNS responder started: http://mon433.local");
  }
}
