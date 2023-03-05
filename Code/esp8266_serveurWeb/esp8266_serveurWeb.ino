#include <Arduino.h>
// Load Wi-Fi library
#include <ESP8266WiFi.h>

//Temp data 
#include <Ethernet.h>
#include <SPI.h>

// Replace with your network credentials
const char* SSID = "binome_2"; 
const char* PASSWORD = "tpRT9025";

// Set web server port number to 80
WiFiServer server(443);

//Temp data
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

EthernetClient client;


void setup() {

  Serial.begin(115200);    

  // Connect to Wi-Fi network with SSID and PASSWORD
  Serial.print("Connecting to ");
  Serial.println(SSID);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(5500);
    Serial.print("_");
  }
  // Print local IP address 
  Serial.println("WiFi connected at IP address:");
  Serial.println(WiFi.localIP());

 // Start Web Server
  server.begin();


 
  
// Main loop
void loop(){
  // Create a client and listen for incoming clients
  WiFiClient client = server.available();   
  
  // Do nothing if server is not available
  if (!client) {
     return;
  }
  
  // Wait a client 
  while(!client.available()){}
  
  // A new client is connected, get the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
/*
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1) 
  {
    digitalWrite(output, HIGH);
    value = HIGH;
  } 
  if (request.indexOf("/LED=OFF") != -1)
  {
    digitalWrite(output, LOW);
    value = LOW;
  }
  
  // Display GPIO status
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); 

  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.print("GPIO status: "); 

  if(value == HIGH) {
    client.print("ON");  
  } else {
    client.print("OFF");
  }

  client.println("<br><br>");
  client.println("Switch manually GPIO state");
  client.println("<br><br>");
  client.println("Turn <a href=\"/LED=ON\">ON</a><br>");
  client.println("Turn <a href=\"/LED=OFF\">OFF</a><br>");
  client.println("</html>");

  Serial.println("");
*/
//temp data
  if (client.connect(server, 443) {
    int temp = random(0, 100);  // génère une température aléatoire entre 0 et 100
    client.print("GET /script.php?temp=");
    client.print(temp);
    client.println(" HTTP/1.1");
    client.println("Host: example.com");
    client.println();
    client.stop();
  }
  delay(60000); // attend 60 secondes avant de répéter la mesure
  
}



