#ifndef VIRA_UPLOAD_MANAGER_H
#define VIRA_UPLOAD_MANAGER_H

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "FileSystem.h"

class UploadManager {
public:
  UploadManager();
  void begin();
  void attach(AsyncWebServer *server, ViraFileSystem *fs);

private:
  AsyncWebServer *_server;
  ViraFileSystem *_fs;
  void handleUpload(AsyncWebServerRequest *request,
                    String filename,
                    size_t index,
                    uint8_t *data,
                    size_t len,
                    bool final);

};

#endif