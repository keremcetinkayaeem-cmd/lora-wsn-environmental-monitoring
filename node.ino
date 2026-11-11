#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_SGP30.h>
#include <DHT.h>
#include <hp_BH1750.h>

#define NODE_ID 1 // Kod 2. düğüme yüklenirken buraya 2 yazılır
SoftwareSerial loraSerial(10, 11);

#define DHTPIN 2
#define SOIL_PIN A0

DHT dht(DHTPIN, DHT11);
Adafruit_SGP30 sgp;
hp_BH1750 bh1750;

void setup() {
  Serial.begin(9600);
  loraSerial.begin(9600);

  Serial.println("--- DUGUM 1 BASLATILIYOR ---");
  dht.begin();
  if (!sgp.begin()) Serial.println("HATA: SGP30 bulunamadi!");
  if (!bh1750.begin(BH1750_TO_GROUND)) Serial.println("HATA: BH1750 bulunamadi!");

  Serial.println("Sensorler isiniyor...");
  delay(2000);
  Serial.println("DUGUM 1 HAZIR. OTO-YAYIN MODU AKTIF!");
}

void loop() {
  Serial.println("\n--- Dugum 1: Yeni Veriler Okunuyor ---");

  float t = dht.readTemperature();
  float h = dht.readHumidity();
  int toprakDeger = analogRead(SOIL_PIN);
  int toprak = map(toprakDeger, 1023, 0, 0, 100);

  bh1750.start();
  float lux = bh1750.getLux();

  sgp.IAQmeasure();
  int tvoc = sgp.TVOC;

  String paket = "<1," + String(t,1) + "," + String(h,1) + "," +
   String(toprak) + "," + String(tvoc) + "," + String(lux,0) + ">";

  loraSerial.println(paket);
  Serial.println("Veri LoRa'dan Gonderildi: " + paket);

  // SGP30'u canlı tutan ve diğer düğüme sıra veren 30 saniyelik bekleme
  Serial.println("30 saniye bekleniyor...");
  for (int i = 0; i < 30; i++) {
    sgp.IAQmeasure();
    delay(1000);
  }
}
