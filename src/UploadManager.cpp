#include "UploadManager.h"
#include <LittleFS.h>

UploadManager::UploadManager() {
    _server = nullptr;
    _fs = nullptr;
}

void UploadManager::begin() {

}

void UploadManager::attach(AsyncWebServer *server, ViraFileSystem *fs) {

  _server = server;
  _fs = fs;

  if (!_server || !_fs) return;

  _server->on("/upload", HTTP_POST,
    [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", "UPLOAD OK");
    },
    [this](AsyncWebServerRequest *request,
        String filename,
        size_t index,
        uint8_t *data,
        size_t len,
        bool final) {

        if (index == 0) {
            Serial.println("Upload Start: " + filename);
        }
        if (len) {
            Serial.println("Writing chunk...");
        }
        if (final) {
            Serial.println("Upload Finished: " + filename);
        }
        handleUpload(request, filename, index, data, len, final);
    }
  );
}

void UploadManager::handleUpload(AsyncWebServerRequest *request,
  String filename,
  size_t index,
  uint8_t *data,
  size_t len,
  bool final) {
  static File uploadFile;

  if (index == 0) {
      String path = "/" + filename;
      uploadFile = LittleFS.open(path, "w");
      Serial.println("Saving: " + path);
  }

  if (len) {
      uploadFile.write(data, len);
  }

  if (final) {
      uploadFile.close();
      Serial.println("Upload Done: " + filename);
  }
}