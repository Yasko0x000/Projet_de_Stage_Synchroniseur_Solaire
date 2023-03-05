#include <ESP8266WiFi.h>
#include <ArduinoHA.h>

#define BROKER_ADDR     IPAddress(192,168,1,104)
#define WIFI_SSID       "binome_2"
#define WIFI_PASSWORD   "tpRT9025"

WiFiClient client;
HADevice device;
HAMqtt mqtt(client, device);

// "led" is unique ID of the switch. You should define your own ID.
HASwitch led("led");

void onSwitchCommand(bool state, HASwitch* sender)
{
    digitalWrite(LED_BUILTIN, (state ? HIGH : LOW));
    sender->setState(state); // report state back to the Home Assistant
}

// function callback
void onStateChangeCallback(bool state, HASwitch* sender) {
    Serial.print("Switch state changed to: ");
    Serial.println(state);
}

void setup() {
    Serial.begin(115200);
    Serial.println("Starting...");

    // Unique ID must be set!
    byte mac[WL_MAC_ADDR_LENGTH];
    WiFi.macAddress(mac);
    device.setUniqueId(mac, sizeof(mac));

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    // connect to wifi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500); // waiting for the connection
    }
    Serial.println();
    Serial.println("Connected to the network");

    // set device's details (optional)
    device.setName("NodeMCU");
    device.setSoftwareVersion("1.0.0");

    // handle switch state
    led.onCommand(onSwitchCommand);
    led.setName("My LED"); // optional

    mqtt.begin(BROKER_ADDR);
}
void loop() {
    mqtt.loop();
}
