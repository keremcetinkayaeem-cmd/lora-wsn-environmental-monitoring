LoRa Tabanlı Kablosuz Sensör Ağı ile Ortam Değişkeni İzleme

Erciyes Üniversitesi Elektrik-Elektronik Mühendisliği bitirme projesi (Aralık 2025).

2 uç düğüm ve 1 ağ geçidinden oluşan, yıldız topolojili bir LoRa (868 MHz) sensör ağı. Uç düğümler sıcaklık, nem, ışık şiddeti, hava kalitesi (TVOC) ve toprak nemi verilerini toplar; ağ geçidi bu verileri ThingSpeak bulut platformuna aktarır.

English summary: A star-topology LoRa (868 MHz) wireless sensor network with 2 end nodes and 1 gateway, measuring temperature, humidity, light, TVOC and soil moisture, with cloud monitoring on ThingSpeak. Custom PCB designed in Altium Designer.

Sistem blok diyagramı

Öne Çıkanlar
Altium Designer'da tasarlanmış ve üretilmiş uç düğüm PCB'si
EBYTE E22-900T22D LoRa modülü ile yaklaşık 5 km saha testi
I2C ve analog sensör entegrasyonu, özel veri paketi formatı
ThingSpeak ile gerçek zamanlı izleme
Sistem Mimarisi
Katman	Bileşenler
Uç düğüm	Arduino Nano, SHT31, BH1750, SGP30, FC-28, EBYTE E22-900T22D, 18650 pil
Ağ geçidi	Arduino Uno, EBYTE E22-900T22D, ESP8266
Bulut	ThingSpeak

Veri paketi formatı: <DüğümID,Sıcaklık,Nem,ToprakNemi,TVOC,Işık>

Örnek: <1,24.5,45.0,35.0,48,1200>

PCB Tasarımı

PCB 3D görünüm PCB üst katman

Araç: Altium Designer
Tasarım: [uç düğüm kartı, katman sayısı: ?]
Üretim: [üretici / yöntem]
Gerber dosyaları: hardware/pcb/
Saha Testi
Parametre	Değer
Mesafe	~5 km
Ortam	[açık alan / şehir içi, görüş hattı var mı]
Anten	868 MHz, 5 dBi SMA
LoRa ayarları	[SF, bant genişliği, hava veri hızı]
Sonuç	[paket iletimi gözlemi]
Kurulum
firmware/node/ içindeki kodu Arduino Nano'ya yükle. Düğüm numarası için kodun başındaki NODE_ID değerini ayarla (1 veya 2).
firmware/gateway/ içindeki kodu Arduino Uno'ya yükle.
Gateway kodunda aşağıdaki alanları kendi bilgilerinle doldur:
AG_ADI, AG_SIFRESI: Wi-Fi bilgileri
API_KEY_1, API_KEY_2: ThingSpeak kanal yazma anahtarları

Not: API anahtarlarını ve şifreleri asla repoya yükleme.

Gerekli Arduino kütüphaneleri
Adafruit SHT31
Adafruit SGP30
BH1750
SoftwareSerial
Proje Ekibi
İsim	Katkı
Kerem Çetinkaya	Altium şema ve PCB tasarımı, [diğer katkıların]
Yusuf Dikici	[katkısı]
Tümer Demirkol	[katkısı]

Danışman: Prof. Dr. Ömer Galip Saraçoğlu

Bilinen Sınırlar ve Geliştirme Fikirleri
Düğümler şu an delay() ile bekliyor; gerçek derin uyku modu ile pil ömrü uzatılabilir.
Yıldız topoloji yerine mesh yapıya geçilerek kapsama genişletilebilir.
Arduino Uno + ESP8266 yerine tek bir ESP32 ile ağ geçidi sadeleştirilebilir.
Lisans

[MIT / belirtilmedi]

İletişim

Kerem Çetinkaya · kerem.cetinkayaeem@gmail.com · [LinkedIn bağlantısı]
