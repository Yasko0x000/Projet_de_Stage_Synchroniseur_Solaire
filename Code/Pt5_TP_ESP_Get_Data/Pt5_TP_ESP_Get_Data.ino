#include <ESP8266WiFi.h>

const char* ssid = "fuzetea";
const char* password = "guadeloupe";

WiFiServer server(80);
float temperature = 25.5;

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
  htmlPage += "<html>";
  htmlPage += "<head>";
  htmlPage +="<body>";
  htmlPage += "<form action='/savetemp' method='get'>";
  htmlPage += "<input type='text' name='temp' placeholder='Entrez la température'/>";
  htmlPage += "<input type='submit' value='Envoyer'/>";
  htmlPage += "</form>";
  htmlPage += "</body></html>";
  return htmlPage;
}

void loop(){
  WiFiClient client = server.accept();
  // wait for a client (web browser) to connect
  if (client) {
    while (client.available()) {
      String line = client.readStringUntil('\r');
      if (line.startsWith("GET /savetemp?temp=")) {
        int tempStart = line.indexOf("=") + 1;
        int tempEnd = line.indexOf(" ", tempStart);
        String tempString = line.substring(tempStart, tempEnd);
        if(isFloat(tempString))
        {
          temperature = tempString.toFloat();
          Serial.println("Température reçue : " + String(temperature) + "C");
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          client.println(prepareHtmlPage());
        }
        else
        {
          client.println("HTTP/1.1 400 Bad Request");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          client.println("<html><body>Données Invalides</body></html>");
        }
        break;
      }
    }
    client.stop();
  }
  delay(1000);
}

bool isFloat(String myString)
{
  for (byte i = 0; i < myString.length(); i++)
  {
    if (isDigit(myString.charAt(i)) || myString.charAt(i) == '.')
    {
      continue;
    }
    return false;
  }
  return true;
}

