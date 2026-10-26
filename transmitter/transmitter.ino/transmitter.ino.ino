#include <WiFi.h>
#include <esp_now.h>

const int pirPin=27;

uint8_t aliciAdres[] = {
  0x20, 0x50, 0x0D, 0x14, 0xA9, 0xC8
};


void setup() {
 Serial.begin(115200);
 WiFi.mode(WIFI_STA);
 pinMode(pirPin,INPUT);

esp_err_t sonuc = esp_now_init();

if(sonuc != ESP_OK){
 Serial.println("NO-ESP");
 return;
}
 Serial.println("YES-ESP");

esp_now_peer_info_t aliciBilgisi = {};
memcpy(aliciBilgisi.peer_addr, aliciAdres, 6);
aliciBilgisi.channel = 0;
aliciBilgisi.encrypt = false;
if (esp_now_add_peer(&aliciBilgisi) != ESP_OK) {
  Serial.println("ALICI EKLENEMEDI!");
  return;
}

Serial.println("ALICI EKLENDI!");
}
void loop() {
  int hareket = digitalRead(pirPin);
  const char *mesaj;
  if(hareket==HIGH ){
   mesaj = "HAREKET";
  }else{
    mesaj = "NORMAL";
  }

  esp_err_t sonuc = esp_now_send(
    aliciAdres,
    (const uint8_t *)mesaj,
    strlen(mesaj)
  );

  if (sonuc == ESP_OK) {
    Serial.println("GONDERME ISTEGI BASARILI");
  } else {
    Serial.println("GONDERME HATASI");
  }

  delay(2000);
}