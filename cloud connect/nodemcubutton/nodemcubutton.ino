#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Replace these with your network credentials
#define WIFI_SSID "401"
#define WIFI_PASSWORD "theoscar"

// Firebase project details
const char* FIREBASE_HOST = "cloud-connect-2caee-default-rtdb.firebaseio.com";
const char* FIREBASE_AUTH = "jUwfllE6JNYnieNLBNSrrjq0nylWzPTPxRbEfxaT";

#define BUTTON_PIN D2

FirebaseData firebaseData;
FirebaseConfig firebaseConfig;
FirebaseAuth firebaseAuth;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi");

  // Configure Firebase
  firebaseConfig.host = FIREBASE_HOST;
  firebaseConfig.signer.tokens.legacy_token = FIREBASE_AUTH;

  // Connect to Firebase
  Firebase.begin(&firebaseConfig, &firebaseAuth);
}

void loop() {
  if (digitalRead(BUTTON_PIN) == HIGH) {
    Serial.println("Button Pressed");

    // Send value to Firebase
    if (Firebase.setInt(firebaseData, "/buttonState", 1)) {
      Serial.println("Value sent to Firebase");
    } else {
      Serial.println("Failed to send value");
      Serial.println("Reason: " + firebaseData.errorReason());
    }

    // Debounce delay
    delay(500);
  }
}
