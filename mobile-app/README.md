# Mobile App - MIT App Inventor

## Build Steps
1. Go to https://appinventor.mit.edu and sign in with a Google account.
2. Create a new project: VehicleTrackingApp.
3. Design the screen with:
   - TextBoxes: Start Lat, Start Lng, End Lat, End Lng (route setting)
   - Labels: Current Lat, Current Lng, Trip Count, Status
   - Buttons: "Set Route", "Refresh Location"
   - Web component (non-visible) -> fetch ThingSpeak JSON feed
   - LocationSensor component (optional, on-device GPS)
   - Notifier -> alerts (route deviation, signal loss)
4. Blocks logic:
   - On Refresh click: Web.Get https://api.thingspeak.com/channels/<CH_ID>/feeds/last.json?api_key=<READ_KEY>
   - Parse JSON: field1 = latitude, field2 = longitude, field3 = trip count
   - Tolerance check (abs diff < 0.0005) for start/end detection
   - End reached after start -> increment trip count label
5. Build -> APK -> install on Android phone.

## Alert Rules
- abs(current - expected) > tolerance -> "Route deviation!" alert
- No GPS fix for > 30 s -> "GPS signal lost" alert

Export the .aia file from MIT App Inventor and place it in this folder.
