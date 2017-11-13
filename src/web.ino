
void handleRoot() {
  char line[80];
  htmlStr[0]='\0';
  addCstring("<!DOCTYPE html><html><body><HR>");

  fh.seek(0,SeekSet);
  while (fh.available()) {
    int k=fh.readBytesUntil('\r',line,79);
    line[k]='\0';
    addCstring(line);
    addCstring("<P>");
  }
  addCstring( "<HR></body></html>" );
  //Serial.println(htmlStr);
  server.send ( 200, "text/html", htmlStr );

}

void handleDir() {
  char fileSize[]="999999";

  htmlStr[0]='\0';
  addCstring("<!DOCTYPE html><html><body><HR>");
  Dir dir = SPIFFS.openDir("/");
  while (dir.next()) {
    dir.fileName().toCharArray(fileName, 14);
    addCstring("<P>");
    addCstring(fileName);
    addCstring("&emsp;");
    itoa(dir.fileSize(),fileSize,7);
    addCstring(fileSize);
  }
  addCstring( "<HR></body></html>" );
  server.send ( 200, "text/html", htmlStr );
}

void helpPage() {
  htmlStr[0]='\0';
  addCstring("<!DOCTYPE html><html><body><HR>");
  addCstring("Valid options include:");
  addCstring("<P>");
  addCstring("dir");
  addCstring("<HR>");
  addCstring( "<HR></body></html>" );
  server.send ( 200, "text/html", htmlStr );
}

void handleNotFound() {
  helpPage();
}

void addCstring(char* s) {
  // find end of htmlStr
  uint16_t p;
  for (p=0;p<HTML_SIZE;p++) {
    if ( p>HTML_SIZE-32) {
      Serial.println("HTML_SIZE exceeded");
      break;
    }
    if (htmlStr[p]=='\0') {
      break;    // p now points to end of old string
    }
  }
  uint16_t q=0;
  for (;p<HTML_SIZE;p++) {
    htmlStr[p]=s[q];
//    if (s[q]!='\0') Serial.print(s[q]);
    if (s[q++]=='\0') break;
  }
  htmlLen = p;
}
