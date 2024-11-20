#include "DeviceManager.h"
#include "IORequest.h"

int main() {
    DeviceManager dm;

    // Simula una entrada de teclado
    dm.setKeyboardBuffer("Entrada del usuario");

    // Crea algunas solicitudes de I/O
    IORequest req1 = {1, DeviceType::Storage, OperationType::Write, "Datos1", 5};
    IORequest req2 = {2, DeviceType::Storage, OperationType::Read, "", 5};
    IORequest req3 = {3, DeviceType::Keyboard, OperationType::Read, "", 0};
    IORequest req4 = {4, DeviceType::Display, OperationType::Write, "¡Hola, Pantalla!", 0};

    // Enviar las solicitudes al Administrador de Dispositivos
    dm.submitRequest(req1);
    dm.submitRequest(req2);
    dm.submitRequest(req3);
    dm.submitRequest(req4);

    // Procesar las solicitudes
    dm.processRequests();

    return 0;
}