#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include "IORequest.h"
#include <queue>
#include <mutex>

class DeviceManager {
public:
    // Function for other components to submit I/O requests
    void submitRequest(const IORequest& request);

    // Function to process I/O requests (can be called in a loop or periodically)
    void processRequests();

private:
    std::queue<IORequest> ioQueue;
    std::mutex queueMutex; // To ensure thread safety if needed

    // Device handling methods
    void handleStorage(const IORequest& request);
    void handleKeyboard(const IORequest& request);
    void handleDisplay(const IORequest& request);

    // Simulated devices
    std::string storage[100]; // Simplified storage device
    std::string keyboardBuffer;
    std::string displayBuffer;
};

#endif // DEVICEMANAGER_H
