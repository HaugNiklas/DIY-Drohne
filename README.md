# DIY-Drohne – ESP32-S3 + STM32F405
 
Eine selbst gebaute, selbst programmierte Drohne mit KI-Erkennung — von Grund auf mit günstigen Komponenten gebaut.
 
> **Student-Projekt** | Start: April 2026 | Ziel: Autonome KI-Drohne unter 250g | Budget: ~150€
 
---
 
## Ziel
 
Ich baue diese Drohne komplett selbst – Hardware, Firmware und KI – um echte Erfahrung in Embedded-Entwicklung (C++/STM32), Regelungstechnik (PID) und KI-Inferenz (Google Coral) zu sammeln. Kein Arduino-Framework, kein fertiger Flight Controller – alles von Grund auf.
 
**Warum unter 250g?** In der EU braucht man ab 250g eine offizielle Drohnenregistrierung. Unter 250g entfällt das.
 
---
 
## Roadmap
 
| Phase | Zeitraum | Ziel | Status |
|-------|----------|------|--------|
| **Phase 1** – Sensor & PID | Woche 1–4 | IMU auslesen, PID-Regler schreiben | 🟡 In Arbeit |
| **Phase 2** – Drohne bauen | Woche 5–10 | Drohne fliegt manuell | ⬜ Offen |
| **Phase 3** – Eigene Firmware | Woche 11–18 | Custom Firmware auf STM32F405 | ⬜ Offen |
| **Phase 4** – KI & Autonomie | Woche 19–28 | Objekterkennung, autonomer Flug | ⬜ Offen |
 
---
 
## Projektstruktur
 
```
DIY-Drohne/
├── phase1-imu/          # MPU-6050 Klasse, Komplementärfilter, PID
├── phase2-drohne/       # ESC, Motoren, Betaflight (geplant)
├── phase3-firmware/     # STM32F405 Custom Firmware, MAVLink (geplant)
├── phase4-ki/           # YOLO, Google Coral, autonomer Flug (geplant)
└── README.md
```
  
## Phase 1 – Aktueller Stand
 
**Stack:** ESP32-S3-Zero + PlatformIO + Arduino Framework
 
### Was bisher funktioniert
- MPU-6050 über I2C auslesen (Accel + Gyro)
- Komplementärfilter → Roll & Pitch in Echtzeit
- Saubere C++ Klassenstruktur (`MPU6050.h` / `MPU6050.cpp`)
### Nächste Schritte
- [ ] Kalibrierung (Offsets)
- [ ] NRF24L01 Funkverbindung
- [ ] PID-Regler implementieren
- [ ] SSD1306 OLED Anzeige
---
## Hardware

| Komponente | Zweck | Preis |
| --- | --- | --- |
| ESP32-S3-Zero | WiFi/BT Companion, spätere Telemetrie | 1,89 € |
| MPU-6050 GY-521 (×2) | Gyroskop + Beschleunigungssensor (IMU) | 1,69 € |
| AHT20 + BMP280 (×2) | Temperatur / Luftfeuchtigkeit / Höhe | 1,09 € |
| NRF24L01+PA+LNA | 2,4GHz Funkverbindung, 1100m Reichweite | 1,49 € |
| SSD1306 OLED 0,96" | Live-Sensordaten anzeigen | 1,29 € |
| Breadboard 830 Punkte | Prototyping ohne Löten | 1,29 € |
| Dupont Kabel 20-polig | Verkabelung | 1,09 € |
| TENSTAR ROBOT (unbekannt) | – | 1,48 € |

## Sonstiges – Werkzeug & Verbrauchsmaterial
 
| Komponente | Zweck | Preis |
|---|---|---|
| Schrumpfschlauch-Set 127pcs | Kabelisolierung & Zugentlastung | 1,09 € |
| Lötzinn 0,8mm 50g (No-clean) | Löten allgemein | 1,69 € |
| Entlötlitze 1,5mm | Fehler ausbessern beim Löten | 0,89 € |
| Lötkolben-Reiniger Ball | Lötspitze sauber halten | 0,65 € |
| Silikon-Löt-/Arbeitsmatte | Hitzeschutz & Arbeitsunterlage | 1,69 € |
| Widerstand-Set 600pcs (30 Werte) | Allgemeine Schaltungstechnik | 1,69 € |
| TP4056 Lademodule ×5 (Micro-USB) | LiPo-Akkus laden & schützen | 0,99 € |


---
 
## Tech Stack
 
| Bereich | Technologie |
|---------|-------------|
| Firmware (Flight Controller) | C++ / STM32 HAL |
| Firmware (Companion) | C++ / Arduino Framework |
| IDE | PlatformIO + VS Code |
| KI-Inferenz | TensorFlow Lite / Google Coral |
| Telemetrie-Protokoll | MAVLink |
| Groundstation | Python |
 
---
