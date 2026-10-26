# ESP32 Kablosuz Hareket Algılama Sistemi

[English](README.md) | **Türkçe**

Bu proje, iki ESP32 geliştirme kartı, bir PIR hareket sensörü ve bir OLED ekran kullanılarak geliştirilmiş kablosuz hareket algılama sistemidir.

ESP32 kartları arasında ESP-NOW haberleşme protokolü kullanılarak Wi-Fi yönlendiricisine ihtiyaç duyulmadan hareket bilgisi aktarılır.

## Özellikler

- ESP-NOW ile iki ESP32 arasında kablosuz haberleşme
- HC-SR501 PIR sensörüyle hareket algılama
- 128×64 OLED ekranda hareket durumunun görüntülenmesi
- Hareket algılandığında LED ile uyarı verilmesi
- Haberleşme kesildiğinde bağlantı uyarısı gösterilmesi

## Kullanılan Donanımlar

- 2 adet ESP32 geliştirme kartı
- 1 adet HC-SR501 PIR hareket sensörü
- 1 adet SSD1306 OLED ekran (128×64, I2C)
- Jumper kablolar
- USB güç bağlantıları

## Çalışma Mantığı

Sistem, verici ve alıcı olmak üzere iki ESP32 kartından oluşmaktadır.

**Verici ESP32**, PIR sensörünün dijital çıkışını okuyarak hareket durumuna göre iki farklı mesaj gönderir:

- `HAREKET`: Hareket algılandı.
- `NORMAL`: Hareket algılanmadı.

Bu mesajlar ESP-NOW protokolü üzerinden alıcı ESP32'ye iletilir.

**Alıcı ESP32**, gelen mesajı değerlendirerek OLED ekranı ve üzerindeki mavi LED'i kontrol eder.

| Durum | OLED Ekran | LED |
|---|---|---|
| Hareket algılandı | UYARI | Yanıyor |
| Hareket algılanmadı | NORMAL | Sönük |
| 5 saniye geçerli mesaj alınmadı | BAGLANTI YOK | Sönük |

## Pin Bağlantıları

### Verici ESP32 – PIR Sensörü

| PIR Sensörü | ESP32 |
|---|---|
| VCC | VIN / 5V |
| OUT | GPIO27 |
| GND | GND |

### Alıcı ESP32 – OLED Ekran

| OLED Ekran | ESP32 |
|---|---|
| VCC | 3V3 |
| GND | GND |
| SDA | GPIO21 |
| SCL | GPIO22 |

Mavi uyarı LED'i için ESP32'nin GPIO2 pini kullanılmaktadır.

## Kullanılan Yazılım ve Kütüphaneler

- Arduino IDE
- ESP32 Arduino Core
- WiFi.h
- esp_now.h
- Wire.h
- Adafruit GFX Library
- Adafruit SSD1306 Library

## Proje Dosya Yapısı

```text
ESP32-Wireless-Motion-Detection/
├── transmitter/
│   └── transmitter.ino
├── receiver/
│   └── receiver.ino
├── README.md
└── README_TR.md
```

## Gelecekte Yapılabilecek Geliştirmeler

- Sesli uyarı için buzzer eklenmesi
- Hareket olaylarının kaydedilmesi
- Pil ile taşınabilir kullanım
- Devre için özel koruyucu kutu tasarlanması

## Geliştirici

Yağız Yılmaz  
Bilgisayar Mühendisliği Öğrencisi