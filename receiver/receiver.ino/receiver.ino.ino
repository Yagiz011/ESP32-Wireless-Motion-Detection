#include <WiFi.h>
#include <Wire.h>
#include <esp_now.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define EKRAN_GENISLIK 128
#define EKRAN_YUKSEKLIK 64

Adafruit_SSD1306 ekran(
  EKRAN_GENISLIK,
  EKRAN_YUKSEKLIK,
  &Wire,
  -1
);

const int blueLed = 2;

unsigned long sonMesajZamani = 0;
bool mesajAlindi = false;
bool hareketVar = false;

portMUX_TYPE veriKilidi = portMUX_INITIALIZER_UNLOCKED;

// ESP-NOW mesajı geldiğinde çalışır
void mesaj(
  const esp_now_recv_info_t *bilgi,
  const uint8_t *veri,
  int len
) {
  bool yeniHareket;

  if (len == 7 && memcmp(veri, "HAREKET", 7) == 0) {
    yeniHareket = true;
  }
  else if (len == 6 && memcmp(veri, "NORMAL", 6) == 0) {
    yeniHareket = false;
  }
  else {
    return;
  }

  portENTER_CRITICAL(&veriKilidi);

  hareketVar = yeniHareket;
  mesajAlindi = true;
  sonMesajZamani = millis();

  portEXIT_CRITICAL(&veriKilidi);
}

void setup() {
  Serial.begin(115200);

  pinMode(blueLed, OUTPUT);
  digitalWrite(blueLed, LOW);

  // OLED başlat
  Wire.begin(21, 22);

  if (!ekran.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED BASLATILAMADI!");
    while (true) {
      delay(1000);
    }
  }

  ekran.clearDisplay();
  ekran.setTextSize(2);
  ekran.setTextColor(SSD1306_WHITE);

  ekran.setCursor(40, 12);
  ekran.println("OLED");

  ekran.setCursor(34, 36);
  ekran.println("HAZIR");

  ekran.display();
  delay(3000);

  // ESP-NOW başlat
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW HATASI!");
    while (true) {
      delay(1000);
    }
  }

  esp_now_register_recv_cb(mesaj);

  Serial.println("ALICI HAZIR!");
}

void loop() {
  bool gelenHareket;
  bool gelenMesaj;
  unsigned long sonZaman;

  portENTER_CRITICAL(&veriKilidi);

  gelenHareket = hareketVar;
  gelenMesaj = mesajAlindi;
  sonZaman = sonMesajZamani;

  portEXIT_CRITICAL(&veriKilidi);

  bool baglantiVar = gelenMesaj &&
                     (millis() - sonZaman < 5000);

  ekran.clearDisplay();
  ekran.setTextSize(2);
  ekran.setTextColor(SSD1306_WHITE);

  if (!baglantiVar) {
    ekran.setTextSize(2);
    ekran.setCursor(22, 28);
    ekran.println("BAGLANTI");
    ekran.setCursor(46,46);
    ekran.println("YOK");

    digitalWrite(blueLed, LOW);
  }
  else if (gelenHareket) {
    ekran.setCursor(34, 24);
    ekran.println("UYARI");

    digitalWrite(blueLed, HIGH);
  }
  else {
    ekran.setCursor(28, 24);
    ekran.println("NORMAL");

    digitalWrite(blueLed, LOW);
  }

  ekran.display();
  delay(100);
}