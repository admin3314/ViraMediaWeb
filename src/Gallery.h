#ifndef VIRA_GALLERY_H
#define VIRA_GALLERY_H

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "FileSystem.h"

class Gallery {

public:

    Gallery();

    void begin();

    void attach(AsyncWebServer *server, ViraFileSystem *fs);

private:

    AsyncWebServer *_server;
    ViraFileSystem *_fs;

    void setupRoutes();

    String listFilesJSON(const String &path);

};

#endif