#include "Gallery.h"

Gallery::Gallery() {
    _server = nullptr;
    _fs = nullptr;
}

void Gallery::begin() {

}

void Gallery::attach(AsyncWebServer *server, ViraFileSystem *fs) {

    _server = server;
    _fs = fs;

    if (!_server || !_fs) return;

    setupRoutes();
}

void Gallery::setupRoutes() {

    _server->on("/files", HTTP_GET, [this](AsyncWebServerRequest *request) {

        String json = listFilesJSON("/");

        request->send(200, "application/json", json);
    });

    _server->on("/storage", HTTP_GET, [this](AsyncWebServerRequest *request) {

        String json = "{";

        json += "\"total\":" + String(_fs->totalBytes()) + ",";
        json += "\"used\":" + String(_fs->usedBytes()) + ",";
        json += "\"free\":" + String(_fs->freeBytes());

        json += "}";

        request->send(200, "application/json", json);
    });



_server->on("/search", HTTP_GET, [this](AsyncWebServerRequest *request) {

    if (!request->hasParam("q")) {
        request->send(400, "text/plain", "Missing query");
        return;
    }

    String q = request->getParam("q")->value();

    String json = "[";
    bool first = true;

#if defined(ESP8266)

    Dir dir = LittleFS.openDir("/");

    while (dir.next()) {

        String name = dir.fileName();

        if (name.indexOf(q) == -1) continue;

        if (!first) json += ",";
        first = false;

        json += "{";
        json += "\"name\":\"" + name + "\",";
        json += "\"size\":" + String(dir.fileSize());
        json += "}";
    }

#endif

    json += "]";

    request->send(200, "application/json", json);
});


_server->onNotFound([](AsyncWebServerRequest *request) {

    String path = request->url();

    if (LittleFS.exists(path)) {

        String contentType = "text/plain";

        if (path.endsWith(".jpg")) contentType = "image/jpeg";
        else if (path.endsWith(".png")) contentType = "image/png";
        else if (path.endsWith(".html")) contentType = "text/html";
        else if (path.endsWith(".mp4")) contentType = "video/mp4";

        request->send(LittleFS, path, contentType);

    } else {
        request->send(404, "text/plain", "Not Found");
    }
});

    _server->on("/delete", HTTP_GET, [this](AsyncWebServerRequest *request) {

        if (!request->hasParam("name")) {
            request->send(400, "text/plain", "Missing name");
            return;
        }

        String name = request->getParam("name")->value();

        bool ok = _fs->remove(name);

        if (ok)
            request->send(200, "text/plain", "OK");
        else
            request->send(500, "text/plain", "FAIL");
    });
}



String Gallery::listFilesJSON(const String &path) {

    String json = "[";

#if defined(ESP8266)

    Dir dir = LittleFS.openDir(path);

    bool first = true;

    while (dir.next()) {

        String name = dir.fileName();

        if (!first) json += ",";
        first = false;

        json += "{";
        json += "\"name\":\"" + name + "\",";
        json += "\"size\":" + String(dir.fileSize()) + ",";
        
        if (name.endsWith(".jpg") || name.endsWith(".png")) {
            json += "\"type\":\"image\"";
        } else {
            json += "\"type\":\"file\"";
        }

        json += "}";
    }

#endif

    json += "]";

    return json;
}
