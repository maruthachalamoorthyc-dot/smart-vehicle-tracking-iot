# Circuit Diagrams & Wiring

## NEO-6M GPS -> ESP32
| NEO-6M | ESP32                      |
|--------|----------------------------|
| VCC    | 3.3V (or 5V via regulator) |
| GND    | GND                        |
| TX     | GPIO 16 (RX2)              |
| RX     | GPIO 17 (TX2)              |

## SIM800L GSM -> ESP32 (backup)
| SIM800L | ESP32                     |
|---------|---------------------------|
| VCC     | 4.0V external (2A supply) |
| GND     | GND                       |
| TX      | GPIO 9 (RX1)              |
| RX      | GPIO 10 (TX1)             |

WARNING: SIM800L is 3.7-4.2V only - do NOT power from ESP32 3.3V pin directly.

Add your Fritzing/circuit images to this folder.
