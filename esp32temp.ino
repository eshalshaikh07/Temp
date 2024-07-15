#include <WiFi.h>
#include <FirebaseESP32.h>
#include "DHT.h"

// Replace with your network credentials
const char* ssid = "Wifi name";
const char* password = "Wifi psw";

// Firebase Project details
const char* FIREBASE_HOST = "firebase id";
const char* FIREBASE_AUTH = "firebase api key";

FirebaseData firebaseData;
FirebaseConfig config;
FirebaseAuth auth;

#define DHTPIN 4     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to Wi-Fi");

  // Assign the Firebase credentials
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  // Print values to the serial monitor
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%  Temperature: ");
  Serial.print(t);
  Serial.print("°C ");
  Serial.print(f);
  Serial.print("°F  Heat index: ");
  Serial.print(hic);
  Serial.print("°C ");
  Serial.print(hif);
  Serial.println("°F");

  // Send values to Firebase Realtime Database
  if (Firebase.ready()) {
    if (Firebase.setFloat(firebaseData, "/DHT11/Humidity", h)) {
      Serial.println("Humidity value sent to Firebase");
    } else {
      Serial.println("Failed to send humidity value to Firebase");
      Serial.println(firebaseData.errorReason());
    }
    
    if (Firebase.setFloat(firebaseData, "/DHT11/Temperature", t)) {
      Serial.println("Temperature value sent to Firebase");
    } else {
      Serial.println("Failed to send temperature value to Firebase");
      Serial.println(firebaseData.errorReason());
    }
    
    if (Firebase.setFloat(firebaseData, "/DHT11/HeatIndexC", hic)) {
      Serial.println("Heat Index (Celsius) value sent to Firebase");
    } else {
      Serial.println("Failed to send heat index value (Celsius) to Firebase");
      Serial.println(firebaseData.errorReason());
    }

    if (Firebase.setFloat(firebaseData, "/DHT11/HeatIndexF", hif)) {
      Serial.println("Heat Index (Fahrenheit) value sent to Firebase");
    } else {
      Serial.println("Failed to send heat index value (Fahrenheit) to Firebase");
      Serial.println(firebaseData.errorReason());
    }
  }
}
