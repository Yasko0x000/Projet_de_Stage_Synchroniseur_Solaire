#include <PubSubClient.h>
#include <ESP8266WiFi.h>

const char* ssid = "binome_2";
const char* password = "tpRT9025";
const char* mqtt_server = "192.168.1.118";

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Simuler une température
  float temperature = random(0 - 100);

  // Convertir la température en chaîne de caractères
  char temperatureString[10];
  dtostrf(temperature, 1, 2, temperatureString);

  // Publier la température sur le sujet "temperature/room1"
  client.publish("temperature/room1", temperatureString);
  Serial.print("Published temperature: ");
  Serial.println(temperature);
  
  delay(1000);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT... ");
    if (client.connect("ArduinoClient")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=  ");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
