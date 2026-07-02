#include "FileSystem.h"

ViraFileSystem::ViraFileSystem() {

}

bool ViraFileSystem::begin() {

    return LittleFS.begin();

}

File ViraFileSystem::open(const String &path, const char *mode) {

    return LittleFS.open(normalizePath(path), mode);

}

bool ViraFileSystem::exists(const String &path) {

    return LittleFS.exists(normalizePath(path));

}

bool ViraFileSystem::remove(const String &path) {

    return LittleFS.remove(normalizePath(path));

}

bool ViraFileSystem::rename(const String &oldName, const String &newName) {

    return LittleFS.rename(
        normalizePath(oldName),
        normalizePath(newName)
    );

}

bool ViraFileSystem::mkdir(const String &path) {

    return LittleFS.mkdir(normalizePath(path));

}

bool ViraFileSystem::rmdir(const String &path) {

    return LittleFS.rmdir(normalizePath(path));

}

size_t ViraFileSystem::fileSize(const String &path) {

    File file = open(path, "r");

    if (!file)
        return 0;

    size_t size = file.size();

    file.close();

    return size;
}

bool ViraFileSystem::isFile(const String &path) {

    File file = open(path, "r");

    if (!file)
        return false;

    bool result = !file.isDirectory();

    file.close();

    return result;
}

bool ViraFileSystem::isDirectory(const String &path) {

    File file = open(path, "r");

    if (!file)
        return false;

    bool result = file.isDirectory();

    file.close();

    return result;
}

String ViraFileSystem::normalizePath(const String &path) {

    if (path.length() == 0)
        return "/";

    if (path.startsWith("/"))
        return path;

    return "/" + path;
}

uint32_t ViraFileSystem::totalBytes() {

#if defined(ESP8266)

    FSInfo info;
    LittleFS.info(info);
    return info.totalBytes;

#else

    return 0;

#endif
}

uint32_t ViraFileSystem::usedBytes() {

#if defined(ESP8266)

    FSInfo info;
    LittleFS.info(info);
    return info.usedBytes;

#else

    return 0;

#endif
}

uint32_t ViraFileSystem::freeBytes() {

#if defined(ESP8266)

    FSInfo info;
    LittleFS.info(info);
    return info.totalBytes - info.usedBytes;

#else

    return 0;

#endif
}


