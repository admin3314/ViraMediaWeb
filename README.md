<p align="center">
  <img src="https://img.shields.io/badge/ESP8266%20%7C%20ESP32-ViraMediaWeb-blue?style=for-the-badge"/>
</p>

<h1 align="center">🚀 ViraMediaWeb</h1>
<h5 align="center">Designed By Mostafa MirMousavi</h5>

<p align="center">
Lightweight Web File Manager + Media Server + Mini CDN for ESP8266 / ESP32
</p>

<p align="center">
<img src="https://img.shields.io/badge/Storage-LittleFS-green"/>
<img src="https://img.shields.io/badge/Web-Async%20Server-orange"/>
<img src="https://img.shields.io/badge/Platform-ESP8266%20%7C%20ESP32-blue"/>
<img src="https://img.shields.io/badge/License-MIT-yellow"/>
</p>

---

## ✨ Overview

**ViraMediaWeb** transforms your ESP8266/ESP32 into a powerful embedded web storage system.

It works like a **mini cloud server** directly on your microcontroller.

---

## ⚡ Features

- 📁 Web-based file manager (UI dashboard)
- ⬆️ Drag & Drop file upload
- 🖼️ Image preview in browser
- 📂 File listing via API
- 🗑️ Delete files remotely
- 🌐 Direct file access (`http://ip/vfm`)
- ⚡ Lightweight & fast (LittleFS)
- 🔌 Async Web Server support

---

## 🖥️ Web Interface

---

## 🧠 Supported Platforms

- ESP8266 (NodeMCU / Wemos D1 Mini)
- ESP32 (All variants)

---

## ⚙️ Architecture


ESP8266 / ESP32
↓
LittleFS / SPIFFS Storage
↓
Async Web Server
↓
REST API + Web UI (ViraMediaWeb Panel)


---

## 📦 Installation

### 1. Install Library

Copy this repository into:


Documents/Arduino/libraries/ViraMediaWeb


---

### 2. Required Dependencies

Install these libraries:

- ESPAsyncWebServer
- ESPAsyncTCP (ESP8266)
- AsyncTCP (ESP32)
- LittleFS or SPIFFS

---

## 🚀 Quick Start Example

```cpp id="vira_example"
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ViraMediaWeb.h>

AsyncWebServer server(80);
ViraMediaWeb media;

void setup() {

  Serial.begin(115200);

  WiFi.begin("SSID", "PASSWORD");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Serial.println(WiFi.localIP());

  media.begin();
  media.attach(server);

  server.begin();
}

void loop() {
}

---

🌐 Web Access

After uploading firmware, open:

http://DEVICE_IP/vfm

👉 Dashboard (File Manager UI) will load automatically.

📁 API Endpoints
Route	Method	Description
/	GET	Web UI Dashboard
/upload	POST	Upload file
/files	GET	List all files
/delete?name=	GET	Delete file
/storage	GET	Storage info
🖼 File Access (Direct CDN Mode)

Any uploaded file can be accessed directly:

http://DEVICE_IP/filename.jpg
http://DEVICE_IP/logo.png
http://DEVICE_IP/video.mp4
💡 Use Cases
Smart IoT dashboards
Local network file sharing
Embedded media server
ESP-based mini cloud storage
Industrial monitoring systems
Smart home file interface
🔥 Web UI Features

✔ File upload panel
✔ Storage usage monitor
✔ File list viewer
✔ Image thumbnails
✔ Delete button
✔ View/Open file in new tab
✔ Drag & Drop upload support

⚡ Example Workflow
Connect ESP to WiFi
Open IP in browser
Upload files via web UI
Access files via URL
Use API in your own projects
🧩 Integration Example (Web Project)

You can use uploaded files inside your own website:

<img src="http://DEVICE_IP/logo.png" />
<script>
fetch("http://DEVICE_IP/files")
  .then(r => r.json())
  .then(data => console.log(data));
</script>
🧠 Technical Notes
Fully async architecture (no blocking server calls)
Designed for low memory microcontrollers
Optimized for LAN usage
Works as embedded HTTP file server
👨‍💻 Author

Mostafa MirMousavi (viramedar)
Embedded Systems | Network Engineering | IoT Development | Infrastructure Design

📜 License

MIT License

🚀 ViraMediaWeb Concept

Turn your ESP device into a smart web storage node inside your network


