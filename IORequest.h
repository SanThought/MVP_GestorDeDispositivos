#ifndef IOREQUEST_H
#define IOREQUEST_H

#include <string>

enum class DeviceType {
    Storage,
    Keyboard,
    Display
};

enum class OperationType {
    Read,
    Write
};

struct IORequest {
    int processId;
    DeviceType device;
    OperationType operation;
    std::string data; // For write operations
    int address;      // For storage operations
};

#endif // IOREQUEST_H
