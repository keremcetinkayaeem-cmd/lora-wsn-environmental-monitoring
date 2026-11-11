# LoRa Tabanlı Kablosuz Sensör Ağı ile Ortam Değişkeni İzleme

Erciyes Üniversitesi Elektrik-Elektronik Mühendisliği bitirme projesi (Haziran 2026).

2 uç düğüm ve 1 ağ geçidinden oluşan, yıldız topolojili bir LoRa (868 MHz) sensör ağı. Uç düğümler sıcaklık, nem, ışık şiddeti, hava kalitesi (TVOC) ve toprak nemi verilerini toplar; ağ geçidi bu verileri ThingSpeak bulut platformuna aktarır.

> English summary: A star-topology LoRa (868 MHz) wireless sensor network with 2 end nodes and 1 gateway, measuring temperature, humidity, light, TVOC and soil moisture, with cloud monitoring on ThingSpeak. Custom PCBs for both the node and the gateway were designed in Altium Designer and manufactured.

![Sistem blok diyagramı](images/system-diagram.png)

## Öne Çıkanlar

- Uç düğüm ve ağ geçidi için Altium Designer'da şema ve PCB tasarımı (Kerem Çetinkaya), üretilmiş kartlar
- EBYTE E22-900T22D LoRa modülü ile 1,38 km saha testi, paket kaybı olmadan
- Tek telli dijital, I2C ve analog sensör entegrasyonu, özel veri paketi formatı
- ThingSpeak ile gerçek zamanlı izleme
- MATLAB ile SF7-SF12 kapsama ve veri hızı simülasyonu
- 3D yazıcı ile üretilmiş koruyucu kutular

## Sistem Mimarisi

| Katman | Bileşenler |
|---|---|
| Uç düğüm | Arduino Nano, DHT11, BH1750, SGP30, FC-28, EBYTE E22-900T22D, 2 x 18650 pil |
| Ağ geçidi | Arduino Uno R3, EBYTE E22-900T22D, ESP-01 (ESP8266) Wi-Fi modülü, LM2596 ve AMS1117 regülatörler, 2 x 18650 pil |
| Bulut | ThingSpeak |

**Veri paketi formatı:** `<DüğümID,Sıcaklık,Nem,ToprakNemi,TVOC,Işık>`

Örnek: `<1,24.5,45.0,35.0,48,1200>`

## Gerçek Donanım

| Uç düğüm | Ağ geçidi |
|---|---|
| ![Uç düğüm](images/node-real.jpg) | ![Ağ geçidi](images/gateway-real.jpg) |

## PCB Tasarımı (Altium Designer)

Prototip önce breadboard üzerinde doğrulandı, ardından şema ve PCB tasarımı yapılıp kartlar üretildi.

| Uç düğüm PCB | Ağ geçidi PCB (Arduino Uno shield) |
|---|---|
| ![Uç düğüm PCB](hardware/pcb/node-pcb.png) | ![Ağ geçidi PCB](hardware/pcb/gateway-pcb.png) |

| Uç düğüm şeması | Ağ geçidi şeması |
|---|---|
| ![Uç düğüm şeması](hardware/schematic/node-schematic.png) | ![Ağ geçidi şeması](hardware/schematic/gateway-schematic.png) |

**Öne çıkan tasarım kararları**

- Arduino Nano'nun 5V UART çıkışı ile LoRa modülünün 3.3V toleranslı RX pini arasında gerilim bölücü direnç ağı
- Analog ve dijital sinyal yollarının ayrılması (EMI'yi azaltmak için)
- Güç hatlarının LoRa iletim anındaki akım dalgalanmalarına göre kalınlaştırılması
- Ağ geçidinde LM2596 (5V) ve AMS1117 (3.3V) ile ayrı regülatör ağları, ESP-01'in akım çekişine uygun güç yolları

## Saha Testi

![Saha testi](images/field-test-1.38km.png)

| Parametre | Değer |
|---|---|
| Mesafe | 1,38 km (kuş uçuşu), paket kaybı gözlenmedi |
| Ortam | Kayseri Millet Bahçesi çevresi: ağaçlık alan, su kütleleri, hafif engebe |
| Anten | 868 MHz, 5 dBi SMA |
| Sonuç | Test mesafesinin üst sınırına ulaşılmadı |

## Bulut İzleme (ThingSpeak)

| Düğüm 1 | Düğüm 2 |
|---|---|
| ![Düğüm 1](images/thingspeak-node1.png) | ![Düğüm 2](images/thingspeak-node2.png) |

## SF7-SF12 Simülasyonu (MATLAB)

Simülasyon, 22 dBm çıkış gücü ve 5 dBi anten kazancı varsayımıyla yapılmıştır. Gerçek ölçüm değildir.

| Kapsama | Veri hızı |
|---|---|
| ![Kapsama](images/sf-coverage-simulation.png) | ![Veri hızı](images/sf-datarate-simulation.png) |

## Kurulum

1. `firmware/node/node.ino` dosyasını Arduino Nano'ya yükle. İkinci düğüm için dosyanın başındaki `NODE_ID` değerini 2 yap.
2. `firmware/gateway/gateway.ino` dosyasını Arduino Uno'ya yükle. Önce Wi-Fi adı, şifresi ve ThingSpeak kanal yazma anahtarlarını (`API_KEY_BURAYA`) kendi bilgilerinle değiştir.
3. Gerekli Arduino kütüphaneleri: Adafruit SGP30, DHT sensor library, hp_BH1750.

> **Not:** Wi-Fi şifresini ve API anahtarlarını asla repoya yükleme.

## Proje Ekibi

| İsim | Katkı |
|---|---|
| Kerem Çetinkaya | Altium şema ve PCB tasarımı (uç düğüm ve ağ geçidi) |
| Yusuf Dikici | Koruyucu kutu tasarımı (Siemens NX), [diğer katkılar] |
| Tümer Demirkol | Koruyucu kutu tasarımı (Siemens NX), [diğer katkılar] |

Danışman: Prof. Dr. Ömer Galip Saraçoğlu

Tam rapor: [docs/rapor.pdf](docs/rapor.pdf)

## Bilinen Sınırlar ve Geliştirme Fikirleri

- Test, 1,38 km ile sınırlı kaldı; maksimum menzil denenmedi.
- Güç tasarrufu için gerçek derin uyku modu eklenebilir.
- Yıldız topoloji yerine mesh yapıya geçilerek kapsama genişletilebilir.
- Arduino Uno + ESP-01 yerine tek bir ESP32 ile ağ geçidi sadeleştirilebilir.

## İletişim

Kerem Çetinkaya · kerem.cetinkayaeem@gmail.com
