#include "DeviceManager.h"
#include <iostream>

void DeviceManager::submitRequest(const IORequest& request) {
    std::lock_guard<std::mutex> lock(queueMutex);
    ioQueue.push(request);
}

void DeviceManager::processRequests() {
    while (true) {
        IORequest request;

        {
            std::lock_guard<std::mutex> lock(queueMutex);
            if (ioQueue.empty()) {
                break;
            }
            request = ioQueue.front();
            ioQueue.pop();
        }

        switch (request.device) {
            case DeviceType::Storage:
                handleStorage(request);
                break;
            case DeviceType::Keyboard:
                handleKeyboard(request);
                break;
            case DeviceType::Display:
                handleDisplay(request);
                break;
        }
    }
}

void DeviceManager::handleStorage(const IORequest& request) {
    if (request.operation == OperationType::Read) {
        std::string data = storage[request.address];
        std::cout << "Process " << request.processId << " read from storage: " << data << std::endl;
    } else if (request.operation == OperationType::Write) {
        storage[request.address] = request.data;
        std::cout << "Process " << request.processId << " wrote to storage at address "
                  << request.address << ": " << request.data << std::endl;
    }
}

void DeviceManager::handleKeyboard(const IORequest& request) {
    if (request.operation == OperationType::Read) {
        std::cout << "Process " << request.processId << " read from keyboard: " << keyboardBuffer << std::endl;
        keyboardBuffer.clear();
    }
}

void DeviceManager::handleDisplay(const IORequest& request) {
    if (request.operation == OperationType::Write) {
        displayBuffer += request.data;
        std::cout << "Process " << request.processId << " wrote to display: " << request.data << std::endl;
    }
}

void DeviceManager::setKeyboardBuffer(const std::string& input) {
    keyboardBuffer = input;
}