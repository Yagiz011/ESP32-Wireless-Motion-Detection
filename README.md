**English** | [Türkçe](README_tr.md)


# ESP32 Wireless Motion Detection System

A wireless motion detection system developed using two ESP32 development boards, a PIR motion sensor, and an OLED display. The project uses the ESP-NOW communication protocol to transmit motion data without requiring a Wi-Fi router.

## Features

- Wireless communication between two ESP32 boards using ESP-NOW
- Motion detection using an HC-SR501 PIR sensor
- Real-time motion status displayed on a 128x64 OLED screen
- LED warning when motion is detected
- Communication timeout detection

## Hardware Components

- 2 × ESP32 development boards
- 1 × HC-SR501 PIR motion sensor
- 1 × SSD1306 OLED display (128x64, I2C)
- Jumper wires and USB power connections

## How It Works

The transmitter ESP32 reads the digital output of the PIR sensor and sends one of two messages to the receiver using ESP-NOW.

- `HAREKET`: Motion detected
- `NORMAL`: No motion detected

The receiver ESP32 displays the current status on the OLED screen and controls its onboard LED.

| Received Status | OLED Display | LED |
|---|---|---|
| Motion detected | UYARI | ON |
| No motion | NORMAL | OFF |
| No valid message for 5 seconds | BAGLANTI YOK | OFF |

## Pin Connections

**Transmitter ESP32**

| PIR Sensor | ESP32 |
|---|---|
| VCC | VIN / 5V |
| OUT | GPIO27 |
| GND | GND |

**Receiver ESP32**

| OLED Display | ESP32 |
|---|---|
| VCC | 3V3 |
| GND | GND |
| SDA | GPIO21 |
| SCL | GPIO22 |

The onboard warning LED uses GPIO2.

## Software and Libraries

- Arduino IDE
- ESP32 Arduino Core
- WiFi.h
- esp_now.h
- Wire.h
- Adafruit GFX Library
- Adafruit SSD1306 Library

## Project Structure

```text
ESP32-Wireless-Motion-Detection/
├── transmitter/
│   └── transmitter.ino
├── receiver/
│   └── receiver.ino
└── README.md
```

## Future Improvements

- Add a buzzer for audible alerts
- Improve motion event logging
- Add battery-powered operation
- Design a compact enclosure

## Author

Yağız Yılmaz  
Computer Engineering Student