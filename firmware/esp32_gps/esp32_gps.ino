/*
 * Smart Vehicle Tracking & Route Monitoring System
 * Board: ESP32 DevKit | GPS: NEO-6M | Cloud: ThingSpeak
 * Authors: Maruthachala Moorthy C, Anwar Khan A
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>

// ---------------- CONFIG ----------------
const char* WIFI_SSID     = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
const String THINGSPEAK_API_KEY = "YOUR_THINGSPEAK_WRITE_API_KEY";
const float TOLERANCE = 0.0005;   // ~50 m tolerance for route detection

// Route points (set via app; defaults shown)
float startLat = 10.3523, startLng = 77.9800;
float endLat   = 10.3600, endLng   = 77.9900;

// ---------------- OBJECTS ----------------
TinyGPSPlus gps;
HardwareSerial gpsSerial(2);   // UART2: RX2=16, TX2=17

bool startReached = false;
int  tripCount    = 0;
String statusMsg  = "WAITING";

// ---------------- SETUP ----------------
void setup() {
  Serial.begin(115200);
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);  // NEO-6M

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWiFi Connected!");
}

// ---------------- HELPERS ----------------
bool nearPoint(float lat, float lng, float refLat, float refLng) {
  return (fabs(lat - refLat) < TOLERANCE) && (fabs(lng - refLng) < TOLERANCE);
}

void sendToThingSpeak(float lat, float lng, int trips, String status) {
  if (WiFi.status() != WL_CONNECTED) {
    // TODO: GSM backup (SIM800L) sends via GPRS/SMS here
    Serial.println("WiFi lost — GSM backup would take over");
    return;
  }
  HTTPClient http;
  String url = "http://api.thingspeak.com/update?api_key=" + THINGSPEAK_API_KEY
             + "&field1=" + String(lat, 6)
             + "&field2=" + String(lng, 6)
             + "&field3=" + trips
             + "&field4=" + status;
  http.begin(url);
  int code = http.GET();
  Serial.printf("ThingSpeak update -> HTTP %d\n", code);
  http.end();
}

// ---------------- LOOP ----------------
void loop() {
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());

    if (gps.location.isUpdated()) {
      float lat = gps.location.lat();
      float lng = gps.location.lng();

      // ----- Route detection logic -----
      if (!startReached && nearPoint(lat, lng, startLat, startLng)) {
        startReached = true;
        statusMsg = "START_REACHED";
        Serial.println(">>> Start point reached — trip tracking started");
      }
      else if (startReached && nearPoint(lat, lng, endLat, endLng)) {
        tripCount++;
        startReached = false;   // reset for next trip
        statusMsg = "TRIP_COMPLETED";
        Serial.printf(">>> Trip completed! Total trips: %d\n", tripCount);
      }

      Serial.printf("Lat: %.6f | Lng: %.6f | Trips: %d\n", lat, lng, tripCount);
      sendToThingSpeak(lat, lng, tripCount, statusMsg);
      delay(15000);  // ThingSpeak free tier: 15 s minimum interval
    }
  }
}
