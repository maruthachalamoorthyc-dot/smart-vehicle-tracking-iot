# Smart Vehicle Tracking and Route Monitoring System using IoT & Mobile Application

A real-time GPS vehicle tracking system built on **ESP32** with dual communication (Wi-Fi + GSM backup),
cloud integration via **ThingSpeak**, and monitoring through a **Web Dashboard** and **Android Mobile App (MIT App Inventor)**.

Mini Project Report - B.E. Electrical and Electronics Engineering, NPR College of Engineering and Technology
(Autonomous Institution, Affiliated to Anna University, Chennai), Natham, Dindigul - 624401

**Team:** Maruthachala Moorthy C (583223105014) | Anwar Khan A (583223105003)
**Supervisor:** Mr. R. Pandi Prabakaran, M.E., (Ph.D.) | **HOD:** Dr. S. Prakash
**Date:** May 2026

---

## Features

- Real-time GPS tracking (NEO-6M module)
- Live map visualization on web dashboard
- Android mobile app (MIT App Inventor)
- Route monitoring with tolerance-based start/end detection
- Automatic trip counting
- Alerts: route deviation, GPS signal loss, communication failure
- Dual communication: Wi-Fi (primary) + GSM/SIM800L (backup)
- Cloud data logging via ThingSpeak

## System Architecture

    GPS Module (NEO-6M)
            |
            v
    ESP32 Microcontroller ---> Wi-Fi --+
            |                          +--> Cloud (ThingSpeak) --> Web App / Mobile App --> User
            +---> GSM (SIM800L backup)-+

## Repository Structure

    smart-vehicle-tracking-iot/
    |-- firmware/esp32_gps/     # Arduino IDE sketch for ESP32
    |-- web-app/                # HTML/CSS/JS dashboard with Leaflet map
    |-- mobile-app/             # MIT App Inventor notes
    |-- docs/                   # Project report & documentation
    |-- circuit-diagrams/       # Hardware wiring guide
    `-- README.md

## Hardware Requirements

| Component        | Purpose                                  |
|------------------|------------------------------------------|
| ESP32 DevKit     | Main MCU (built-in Wi-Fi, low cost)      |
| NEO-6M GPS       | Real-time latitude/longitude             |
| SIM800L GSM      | Backup communication                     |
| Jumper wires     | Interfacing                              |

## Software Requirements

- Arduino IDE (ESP32 core) + TinyGPS++ library
- ThingSpeak account (free channel)
- Leaflet.js (web map) or Google Maps API
- MIT App Inventor (mobile app)
- Web browser + internet

## Getting Started

1. **Hardware:** Wire NEO-6M TX->ESP32 GPIO16 (RX2), RX->GPIO17 (TX2). Connect SIM800L as backup (TX->GPIO9, RX->GPIO10).
2. **Firmware:** Open firmware/esp32_gps/esp32_gps.ino, fill in WIFI_SSID, WIFI_PASSWORD, THINGSPEAK_API_KEY, then upload to ESP32.
3. **ThingSpeak:** Create a channel with fields: latitude, longitude, trip_count, status.
4. **Web app:** Open web-app/index.html in a browser, enter Channel ID + Read API Key, click Start Live Tracking.
5. **Mobile app:** Follow mobile-app/README.md in MIT App Inventor, build APK, install.

## Route Detection Logic (Tolerance Method)

Direct GPS coordinate comparison fails due to signal noise, so the system uses:

    abs(currentLat - refLat) < TOLERANCE (0.0005, ~50 m)

- Vehicle enters start-point radius -> startReached = true
- Vehicle then enters end-point radius -> tripCount++
- Coordinates are set manually through the mobile app

## Results

- Live location updates transmitted to ThingSpeak successfully
- Route detection works reliably with tolerance matching
- Trip count auto-increments on completed journeys
- Continuous operation via GSM backup in low-connectivity areas

## Future Scope

- ML-based route prediction & optimization
- Push notifications / SMS alerts
- Geofencing & speed monitoring
- OBD-II engine diagnostics

## License

MIT License - free for educational use.
