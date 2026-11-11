#include <SoftwareSerial.h>

// DİKKAT: Gerçek Wi-Fi bilgilerini ve ThingSpeak anahtarlarını
// bu dosyaya yazıp repoya YÜKLEME. Sadece kendi bilgisayarında doldur.
String agAdi = "WIFI_ADI";
String agSifresi = "WIFI_SIFRESI";
String ip = "184.106.153.149"; // ThingSpeak sunucu IP adresi

String apiKey1 = "API_KEY_BURAYA"; // Düğüm 1
String apiKey2 = "API_KEY_BURAYA"; // Düğüm 2

SoftwareSerial esp(8, 9);
SoftwareSerial lora(10, 11);

void setup() {
  Serial.begin(9600);
  lora.begin(9600);
  esp.begin(9600);

  Serial.println("\n--- AKILLI GATEWAY SISTEMI BASLATILDI ---");
  esp.listen();

  esp.println("AT");
  while(!esp.find("OK")){
    esp.println("AT");
    Serial.println("ESP8266 Bekleniyor...");
    delay(1000);
  }
  Serial.println(">>> ESP8266 Bulundu!");

  esp.println("AT+CWMODE=1");
  while(!esp.find("OK")){
    esp.println("AT+CWMODE=1");
    delay(500);
  }

  Serial.println(">>> Aga Baglaniliyor: " + agAdi);
  esp.println("AT+CWJAP=\""+agAdi+"\",\""+agSifresi+"\"");
  while(!esp.find("OK")){
    Serial.print(".");
    delay(500);
  }
  Serial.println("\n>>> Aga Baglanildi! Internet Hazir.");

  lora.listen();
  Serial.println(">>> LoRa Dinleniyor, paketler bekleniyor...");
}

void loop() {
  if (lora.available()) {
    String gelenVeri = lora.readStringUntil('\n');
    gelenVeri.trim();

    if (gelenVeri.startsWith("<") && gelenVeri.endsWith(">")) {
      Serial.println("\n----------------------------------");
      Serial.println("LoRa'dan Veri Geldi: " + gelenVeri);

      gelenVeri.replace("<", "");
      gelenVeri.replace(">", "");

      int i1 = gelenVeri.indexOf(',');
      int i2 = gelenVeri.indexOf(',', i1 + 1);
      int i3 = gelenVeri.indexOf(',', i2 + 1);
      int i4 = gelenVeri.indexOf(',', i3 + 1);
      int i5 = gelenVeri.indexOf(',', i4 + 1);

      String id = gelenVeri.substring(0, i1);
      String t = gelenVeri.substring(i1 + 1, i2);
      String h = gelenVeri.substring(i2 + 1, i3);
      String toprak = gelenVeri.substring(i3 + 1, i4);
      String tvoc = gelenVeri.substring(i4 + 1, i5);
      String isik = gelenVeri.substring(i5 + 1);

      Serial.println("--- Parcalanan Veriler ---");
      Serial.println("Dugum ID: " + id);
      Serial.println("DHT11 Sicaklik: " + t + " C | Nem: %" + h);
      Serial.println("FC28 Toprak Nem: " + toprak);
      Serial.println("SGP30 TVOC: " + tvoc);
      Serial.println("BH1750 Isik: " + isik);

      String aktifApiKey = "";
      if (id == "1") {
        aktifApiKey = apiKey1;
        Serial.println(">>> Hedef: Kanal 1");
      } else if (id == "2") {
        aktifApiKey = apiKey2;
        Serial.println(">>> Hedef: Kanal 2");
      } else {
        Serial.println("HATA: Bilinmeyen Dugum ID'si! Pas geciliyor.");
        return;
      }

      esp.listen();
      esp.println("AT+CIPSTART=\"TCP\",\""+ip+"\",80");
      if(esp.find("Error")){
        Serial.println("Baglanti Hatasi (CIPSTART Error)");
      } else {
        String veri = "GET /update?api_key=" + aktifApiKey;
        veri += "&field1=" + t;
        veri += "&field2=" + h;
        veri += "&field3=" + toprak;
        veri += "&field4=" + tvoc;
        veri += "&field5=" + isik;
        veri += "\r\n\r\n";

        esp.print("AT+CIPSEND=");
        esp.println(veri.length() + 2);

        delay(1000);
        if(esp.find(">")){
          esp.print(veri);
          Serial.println(">>> Veri ThingSpeak'e basariyla gonderildi!");
        } else {
          Serial.println("Hata: '>' isareti gelmedi, yollanamadi.");
        }
      }

      esp.println("AT+CIPCLOSE");
      lora.listen();
      Serial.println(">>> LoRa tekrar dinleniyor...");
    }
  }
}
