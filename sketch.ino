#include "M5StickCPlus.h" // Include M5StickCPlus library [^1^][7]
#include <WiFi.h> // Include WiFi library [^2^][6]

const char* ssid = "your_wifi_ssid"; // Replace with your wifi network name
const char* password = "your_wifi_password"; // Replace with your wifi network password

void setup() {
  M5.begin(true, true, true); // Initialize M5StickCPlus [^1^][7]
  Serial.printf("Connecting to %s ", ssid); // Print wifi network name
  WiFi.begin(ssid, password); // Connect to wifi network [^2^][6]
  while (WiFi.status() != WL_CONNECTED) { // Wait until connected
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");
}

void loop() {
  int rssi = WiFi.RSSI(); // Get wifi signal strength in dBm 
  Serial.printf("Signal strength: %d dBm\n", rssi); // Print signal strength
  if (rssi > -50) { // If signal is excellent
    M5.BugC.setMotor(0,0,0,0); // Stop moving [^3^][8]
    M5.Lcd.fillScreen(TFT_GREEN); // Display green screen [^1^][7]
    M5.Lcd.setCursor(40,80);
    M5.Lcd.print("Excellent!"); 
  } else if (rssi > -70) { // If signal is good
    M5.BugC.setMotor(100,-100,-100,-100); // Move forward slowly [^3^][8]
    M5.Lcd.fillScreen(TFT_YELLOW); // Display yellow screen [^1^][7]
    M5.Lcd.setCursor(60,80);
    M5.Lcd.print("Good");
  } else { // If signal is poor or none
    M5.BugC.setMotor(-100,-100,-100,-100); // Move backward quickly [^3^][8]
    M5.Lcd.fillScreen(TFT_RED); // Display red screen [^1^][7]
    M5.Lcd.setCursor(40,80);
    M5.Lcd.print("Poor/None");
  }
}
