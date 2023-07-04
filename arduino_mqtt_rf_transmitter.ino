#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <RCSwitch.h>

// Define the MQTT client and RCSwitch transmitter objects
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
RCSwitch rfTransmitter;

// Wi-Fi credentials
const char* ssid = "ssid";
const char* password = "password";

// MQTT broker configuration
const char* mqttServer = "mqtt.server.com";
const int mqttPort = 1883;
const char* mqttUser = "";
const char* mqttPassword = "";
const char* mqttTopic = "cmnd/do_bell";

// Transmitter information
const uint8_t transmitterPin = D2;
const int transmitterProtocol = 1;
const int transmitterPulseLength = 417;

// Transmission data information
const unsigned long transmissionData = 4310281;
const unsigned int transmissionLength = 24;

// Function to connect to Wi-Fi
void connectToWiFi() {
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to Wi-Fi!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// Function to connect to MQTT broker
void connectToMQTT() {
  Serial.println("Connecting to MQTT server...");
  mqttClient.setServer(mqttServer, mqttPort);
  while (!mqttClient.connected()) {
    if (mqttClient.connect("NodeMCU", mqttUser, mqttPassword)) {
      Serial.println("Connected to MQTT server!");
      mqttClient.subscribe(mqttTopic);
    } else {
      Serial.print("Failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

// Function to handle incoming MQTT messages
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  if (strcmp(topic, mqttTopic) == 0) {
    Serial.println("Sending transmission");
    rfTransmitter.send(transmissionData, transmissionLength);
  }
}

void setup() {
  Serial.begin(115200);

  // Initialize the RCSwitch transmitter
  rfTransmitter.enableTransmit(transmitterPin); // Set the appropriate pin

  rfTransmitter.setProtocol(transmitterProtocol, transmitterPulseLength);

  // Connect to Wi-Fi
  connectToWiFi();

  // Connect to MQTT server
  connectToMQTT();

  // Set MQTT callback function
  mqttClient.setCallback(mqttCallback);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Lost Wi-Fi connection");

    // Attempt to reconnect to Wi-Fi
    connectToWiFi();
  }
  if (!mqttClient.connected()) {
    connectToMQTT();
  }
  mqttClient.loop();
}
