#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <Firebase.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#define FIREBASE_HOST
#define FIREBASE_AUTH
#define WIFI_SSID
#define WIFI_PASSWORD

byte lampu = D5;
int status;

void setup() {
  // put your setup code here, to run once:
  // Create an instance of WiFiManager
  WiFiManager wifiManager;

  // Uncomment the line below if you want to reset the WiFi settings (useful during development)
  // wifiManager.resetSettings();

  // Start the WiFiManager configuration portal
  if (!wifiManager.autoConnect("AutoConnectAP")) {
    Serial.println("Failed to connect and hit timeout");
    delay(3000);
    // Reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(5000);
  }

  // Connected to Wi-Fi
  Serial.println("Connected to Wi-Fi");

  // Print local IP address
  Serial.println(WiFi.localIP());

  // Continue with the rest of your setup code
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.stream("/lamp");

  pinMode(D5, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Firebase.failed()) {
    Serial.print(Firebase.error());
  }

  status = Firebase.getInt("lamp");
  Serial.print(status);
  if (status > 1) {
    digitalWrite(lampu, HIGH);
  } else {
    digitalWrite(lampu, LOW);
  }

  delay(50);
}