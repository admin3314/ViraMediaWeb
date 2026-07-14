#include "ViraMediaWeb.h"

ViraMediaWeb::ViraMediaWeb() {
    _server = nullptr;
}

bool ViraMediaWeb::begin() {
    if (!_fs.begin()) {
        return false;
    }
    return true;
}

void ViraMediaWeb::attach(AsyncWebServer &server) {

    _server = &server;

    _upload.attach(_server, &_fs);
    _gallery.attach(_server, &_fs);
    _webui.attach(_server); 
}

void ViraMediaWeb::setupCore() {
    _upload.attach(_server, &_fs);
    _gallery.attach(_server, &_fs);
}

void ViraMediaWeb::handle() {

}