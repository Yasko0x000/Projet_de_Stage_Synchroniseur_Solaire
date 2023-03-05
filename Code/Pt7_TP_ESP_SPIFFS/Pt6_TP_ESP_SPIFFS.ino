#include <FS.h> 

void setup(){
  SPIFFS.begin(); 
      SPIFFS.format();
      SPIFFS.end(); 
      File f = SPIFFS.open("/test.txt", "w");
      f.println("premiere ligne"); 
      f.available();
      f.readStringUntil('\n');
      f.close();
}

void loop(){}
