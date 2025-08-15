/*
  Arduino MQTT Subscriber using PubSubClient

  This script connects an ESP32 or ESP8266 board to a Wi-Fi network and an MQTT broker.
  It then subscribes to a specified topic and listens for incoming messages.
  When a message is received, its topic and payload are printed to the Serial Monitor.

  Make sure to install the PubSubClient library from the Arduino Library Manager.
*/

// Include necessary libraries
#include <WiFi.h>  // Use <ESP8266WiFi.h> for ESP8266
#include <PubSubClient.h>

// --- Configuration ---
// Update these with your network and MQTT broker details

// Wi-Fi Credentials
const char* ssid = "SkyLab Academy";
const char* password = "SkyLab_Academy";

// MQTT Broker Details
const char* mqtt_server = "10.71.106.156";  // You can use a public broker for testing
const int mqtt_port = 1883;
const char* mqtt_topic_to_subscribe = "home/livingroom/bme280";
const char* mqtt_client_id = "foo-bar-1337-unique-client-ish";  // Must be unique for each client

// --- Global Variables ---
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

/**
 * @brief Handles incoming MQTT messages.
 * This function is called by the PubSubClient library whenever a message
 * arrives on a topic that the client is subscribed to.
 * @param topic The topic the message was published on.
 * @param payload The message payload.
 * @param length The length of the payload.
 */
void messageCallback(char* topic, byte* payload, unsigned int length) {
  Serial.println("--------------------");
  Serial.print("Message arrived on topic: ");
  Serial.println(topic);

  Serial.print("Message payload: ");
  // Create a buffer to hold the payload and null-terminate it
  char message[length + 1];
  memcpy(message, payload, length);
  message[length] = '\0';
  Serial.println(message);
  Serial.println("--------------------");
}

/**
 * @brief Connects to the Wi-Fi network.
 * It will attempt to connect and print its status to the Serial Monitor.
 */
void setupWifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to WiFi SSID: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

/**
 * @brief Reconnects to the MQTT broker.
 * This function attempts to connect to the broker and subscribe to the topic.
 * It will retry every 5 seconds if the connection fails.
 */
void reconnectMqtt() {
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (mqttClient.connect(mqtt_client_id)) {
      Serial.println("connected!");
      // Subscribe to the topic
      if (mqttClient.subscribe(mqtt_topic_to_subscribe)) {
        Serial.print("Successfully subscribed to topic: ");
        Serial.println(mqtt_topic_to_subscribe);
      } else {
        Serial.print("Failed to subscribe to topic: ");
        Serial.println(mqtt_topic_to_subscribe);
      }
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

/**
 * @brief Standard Arduino setup function.
 * Runs once at the beginning of the program.
 */
void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);
  while (!Serial)
    ;  // Wait for serial port to connect. Needed for native USB port only

  // Connect to Wi-Fi
  setupWifi();

  // Configure the MQTT client
  mqttClient.setServer(mqtt_server, mqtt_port);
  mqttClient.setCallback(messageCallback);
}

/**
 * @brief Standard Arduino loop function.
 * Runs repeatedly after setup() is complete.
 */
void loop() {
  // Check if the client is connected to the MQTT broker
  if (!mqttClient.connected()) {
    reconnectMqtt();
  }

  // This allows the client to process incoming messages and maintain the connection
  mqttClient.loop();
}
