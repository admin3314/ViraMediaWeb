#include <ViraMediaWeb.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

const char* ssid = "WIFINAME";
const char* pass = "WIFIPASS";

AsyncWebServer server(80);
ViraMediaWeb media;

void setup() {

  Serial.begin(115200);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");
  Serial.println(WiFi.localIP());

  if (!LittleFS.begin()) {
    Serial.println("FS FAIL");
    return;
  }

  if (!media.begin()) {
    Serial.println("Media Init FAIL");
    return;
  }

  media.attach(server);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {

    String html = R"rawliteral(

        <!DOCTYPE html>
        <html>
        <head>
        <meta charset="UTF-8">
        <title>My Project</title>
        </head>

        <body style="background:#111;color:white;text-align:center;">

        <h2>My Custom Web App</h2>


        <img src="/logo.png" style="width:160px;margin-top:20px;">

        <p>Powered by ESP8266 + ViraMediaWeb</p>


        <script>
        async function loadAssets() {

            let img = document.createElement("img");
            img.src = "/logo.png";
            img.style.width = "120px";
            img.style.marginTop = "20px";

            document.body.appendChild(img);
        }

        loadAssets();
        </script>

        <br><br>

        <a href="/vfm" style="color:#4da3ff;">Open File Manager</a>

        </body>
        </html>

        )rawliteral";

    request->send(200, "text/html", html);
  });


  server.begin();

  Serial.println("ViraMediaWeb Started");
}

void loop() {
  media.handle();
}