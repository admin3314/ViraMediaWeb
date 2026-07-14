#ifndef VIRA_FILE_SYSTEM_H
#define VIRA_FILE_SYSTEM_H

#include <Arduino.h>

#if defined(ESP8266)
#include <LittleFS.h>
#elif defined(ESP32)
#include <LittleFS.h>
#endif

class ViraFileSystem {

public:

    ViraFileSystem();

    bool begin();

    File open(const String &path, const char *mode);

    bool exists(const String &path);

    bool remove(const String &path);

    bool rename(const String &oldName, const String &newName);

    bool mkdir(const String &path);

    bool rmdir(const String &path);

    bool isFile(const String &path);

    bool isDirectory(const String &path);

    size_t fileSize(const String &path);

    String listFiles(const String &path = "/");

    uint32_t totalBytes();

    uint32_t usedBytes();

    uint32_t freeBytes();

    bool format();

    String normalizePath(const String &path);

};

#endif