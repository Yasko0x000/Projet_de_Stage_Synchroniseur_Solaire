#include <ESP8266WiFi.h>

const char* ssid = "binome_2";
const char* password = "tpRT9025";

WiFiServer server(80);


void setup(){
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  server.begin();
  Serial.printf("Web server started, open %s in a web browser\n", WiFi.localIP().toString().c_str());
}


// prepare a web page to be send to a client (web browser)
String prepareHtmlPage(){
  String htmlPage;
  htmlPage.reserve(1024);               // prevent ram fragmentation
  htmlPage = F("HTTP/1.1 200 OK\r\n"
               "Content-Type: text/html\r\n"
               "Connection: close\r\n"  // the connection will be closed after completion of the response
               "Refresh: 5\r\n"         // refresh the page automatically every 5 sec
               "\r\n"
               "<!DOCTYPE HTML>"
               "<html>"
               "<?php
                  $temp = $_GET[\"temp\"];
                  $date = date(\"Y-m-d H:i:s\");
                  $file = 'temperature.txt';
                  $current = file_get_contents($file);
                  $current .= $date . \" - Température : \" . $temp . \"C\n \";
                  file_put_contents($file, $current);
                ?>"
               "</html>"
                "\r\n");
  return htmlPage;
}



void loop(){
  WiFiClient client = server.accept();
  // wait for a client (web browser) to connect
  if (client)
  {
    Serial.println("\n[Client connected]");
    while (client.connected())
    {
      // read line by line what the client (web browser) is requesting
      if (client.available())
      {
        String line = client.readStringUntil('\r');
        Serial.print(line);
        // wait for end of client's request, that is marked with an empty line
        if (line.length() == 1 && line[0] == '\n')
        {
          client.println(prepareHtmlPage());
          break;
        }
      }
    }
  }

 delay(60000);  // attend 60 secondes avant de répéter la mesure
// Send the response
  
  int temp = random(0, 100);  // génère une température aléatoire entre 0 et 100
  client.print("/temp_data.php?temp=" +String(temp));
  client.println(" HTTP/1.1");
  client.println("Host: YohannTesBeau.com");
  client.println("'<?php $temp = $_GET[\"temp\"]; echo \"Voici la temprérature : $temp\";?>");
  client.stop();
   
 
  


    while (client.available()) {
      // but first, let client finish its request
      // that's diplomatic compliance to protocols
      // (and otherwise some clients may complain, like curl)
      // (that is an example, prefer using a proper webserver library)
      client.read();
    }

    // close the connection:
    client.stop();
    Serial.println("[Client disconnected]");
  }

  
}
