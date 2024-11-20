#include "DeviceManager.h"
#include "IORequest.h"

int main() {
    DeviceManager dm;

    // Simulate keyboard input (this could come from the UI module)
    dm.keyboardBuffer = "Sample Keyboard Input";

    // Create some I/O requests
    IORequest req1 = {1, DeviceType::Storage, OperationType::Write, "Data1", 5};
    IORequest req2 = {2, DeviceType::Storage, OperationType::Read, "", 5};
    IORequest req3 = {3, DeviceType::Keyboard, OperationType::Read, "", 0};
    IORequest req4 = {4, DeviceType::Display, OperationType::Write, "Hello, Display!", 0};

    // Processes submit requests to the Device Manager
    dm.submitRequest(req1);
    dm.submitRequest(req2);
    dm.submitRequest(req3);
    dm.submitRequest(req4);

    // Process the I/O requests
    dm.processRequests();

    return 0;
}
