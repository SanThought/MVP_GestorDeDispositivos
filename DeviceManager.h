#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include "IORequest.h"
#include <queue>
#include <mutex>
#include <string>

class DeviceManager {
public:
    // Métodos públicos
    void submitRequest(const IORequest& request);
    void processRequests();

    // Método público para establecer el buffer del teclado
    void setKeyboardBuffer(const std::string& input);

private:
    std::queue<IORequest> ioQueue;
    std::mutex queueMutex;

    // Métodos privados para manejar los dispositivos
    void handleStorage(const IORequest& request);
    void handleKeyboard(const IORequest& request);
    void handleDisplay(const IORequest& request);

    // Simulación de dispositivos
    std::string storage[100];  // Almacenamiento simulado
    std::string keyboardBuffer; // Buffer del teclado
    std::string displayBuffer;  // Buffer de la pantalla
};

#endif // DEVICEMANAGER_H