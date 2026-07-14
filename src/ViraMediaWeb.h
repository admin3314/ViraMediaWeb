#ifndef VIRA_MEDIA_WEB_H
#define VIRA_MEDIA_WEB_H

#include <Arduino.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <AsyncTCP.h>
#endif

#include <ESPAsyncWebServer.h>

#include "FileSystem.h"
#include "UploadManager.h"
#include "Gallery.h"
#include "WebUI.h"

class ViraMediaWeb {

public:

    ViraMediaWeb();

    bool begin();

    void attach(AsyncWebServer &server);

    void handle();

private:

    AsyncWebServer* _server;

    ViraFileSystem _fs;
    UploadManager _upload;
    Gallery _gallery;
    WebUI _webui;

    void setupCore();

};

#endif