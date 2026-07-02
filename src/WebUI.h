#ifndef VIRA_WEB_UI_H
#define VIRA_WEB_UI_H

#include <Arduino.h>
#include <ESPAsyncWebServer.h>

class WebUI {

public:

    WebUI();

    void begin();

    void attach(AsyncWebServer *server);

private:

    AsyncWebServer *_server;

    void setupRoutes();

    String getIndexPage();

};

#endif