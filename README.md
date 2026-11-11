# LoRa Tabanlı Kablosuz Sensör Ağı ile Ortam Değişkeni İzleme

Erciyes Üniversitesi Elektrik-Elektronik Mühendisliği bitirme projesi (Aralık 2025).

2 uç düğüm ve 1 ağ geçidinden oluşan, yıldız topolojili bir LoRa (868 MHz) sensör ağı. Uç düğümler sıcaklık, nem, ışık şiddeti, hava kalitesi (TVOC) ve toprak nemi verilerini toplar; ağ geçidi bu verileri ThingSpeak bulut platformuna aktarır.

> English summary: A star-topology LoRa (868 MHz) wireless sensor network with 2 end nodes and 1 gateway, measuring temperature, humidity, light, TVOC and soil moisture, with cloud monitoring on ThingSpeak. Custom PCB designed in Altium Designer.

![Sistem blok diyagramı](images/system-diagram.png)

## Öne Çıkanlar

- EBYTE E22-900T22D LoRa modülü ile 1,38 km saha testi, paket kaybı olmadan
- Uç düğüm ve ağ geçidi için Altium PCB tasarımı (Kerem Çetinkaya), 3D yazıcı ile üretilmiş koruyucu kutular (ekip arkadaşları)
- MATLAB ile SF7-SF12 kapsama ve veri hızı simülasyonu
- I2C ve analog sensör entegrasyonu, özel veri paketi formatı
- ThingSpeak ile gerçek zamanlı izleme

## Sistem Mimarisi

| Katman | Bileşenler |
|---|---|
| Uç düğüm | Arduino Nano, SHT31, BH1750, SGP30, FC-28, EBYTE E22-900T22D, 18650 pil |
| Ağ geçidi | Arduino Uno, EBYTE E22-900T22D, ESP8266 |
| Bulut | ThingSpeak |

**Veri paketi formatı:** `<DüğümID,Sıcaklık,Nem,ToprakNemi,TVOC,Işık>`

Örnek: `<1,24.5,45.0,35.0,48,1200>`

## PCB Tasarımı

![PCB 3D görünüm](images/pcb-3d.png)
![PCB üst katman](images/pcb-top.png)

- Araç: Altium Designer
- Tasarım: uç düğüm kartı ve Arduino Uno üzerine takılan ağ geçidi kartı (shield), katman sayısı: [?]
- Öne çıkan tasarım kararları: Nano 5V UART çıkışı ile LoRa 3.3V RX pini arasında gerilim bölücü, analog/dijital hat ayrımı, güç hatlarının akıma göre kalınlaştırılması, AMS1117 ve LM2596 ile güç mimarisi
- Üretim: [üretici / yöntem]
- Gerber dosyaları: `hardware/pcb/`

## Saha Testi

| Parametre | Değer |
|---|---|
| Mesafe | 1,38 km (kuş uçuşu), paket kaybı gözlenmedi |
| Ortam | Kayseri Millet Bahçesi çevresi: ağaçlık alan, su kütleleri, hafif engebe |
| Anten | 868 MHz, 5 dBi SMA |
| LoRa ayarları | [SF, bant genişliği, hava veri hızı] |
| Sonuç | Test mesafesinin üst sınırına ulaşılmadı |

## Kurulum

1. `firmware/node/` içindeki kodu Arduino Nano'ya yükle. Düğüm numarası için kodun başındaki `NODE_ID` değerini ayarla (1 veya 2).
2. `firmware/gateway/` içindeki kodu Arduino Uno'ya yükle.
3. Gateway kodunda aşağıdaki alanları kendi bilgilerinle doldur:
   - `AG_ADI`, `AG_SIFRESI`: Wi-Fi bilgileri
   - `API_KEY_1`, `API_KEY_2`: ThingSpeak kanal yazma anahtarları

> **Not:** API anahtarlarını ve şifreleri asla repoya yükleme.

### Gerekli Arduino kütüphaneleri

- Adafruit SHT31
- Adafruit SGP30
- BH1750
- SoftwareSerial

## Proje Ekibi

| İsim 
|---|---|
| Kerem Çetinkaya
| Yusuf Dikici 
| Tümer Demirkol 

Danışman: Prof. Dr. Ömer Galip Saraçoğlu

## Bilinen Sınırlar ve Geliştirme Fikirleri

- Düğümler şu an `delay()` ile bekliyor; gerçek derin uyku modu ile pil ömrü uzatılabilir.
- Yıldız topoloji yerine mesh yapıya geçilerek kapsama genişletilebilir.
- Arduino Uno + ESP8266 yerine tek bir ESP32 ile ağ geçidi sadeleştirilebilir.


## İletişim

Kerem Çetinkaya · kerem.cetinkayaeem@gmail.com · [LinkedIn bağlantısı]
