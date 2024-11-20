# **Administrador de Dispositivos (Device Manager)**

Este proyecto implementa un **Administrador de Dispositivos (Device Manager)** para un sistema operativo simulado, capaz de manejar solicitudes de entrada/salida (I/O) para dispositivos clave: **almacenamiento**, **teclado**, y **pantalla**.

El **Device Manager (DM)** utiliza una estructura compartida (`IORequest`) para procesar solicitudes provenientes de otros módulos del sistema operativo (Gestión de Procesos, Memoria, Sistema de Archivos, Interfaz de Usuario, etc.).

---

## **Cómo Funciona**

1. **Interacción a través de `IORequest`**:
   - Los módulos externos envían solicitudes de I/O al DM utilizando la estructura `IORequest`.
   - Las solicitudes se envían al método `submitRequest()` del DM y son procesadas en orden por `processRequests()`.

2. **Simulación de Dispositivos**:
   - **Almacenamiento**: Un arreglo de cadenas simula un disco de 100 bloques.
   - **Teclado**: Un buffer de texto simula entradas del usuario.
   - **Pantalla**: Un buffer de texto simula la salida en pantalla.

---

## **Interfaz del Device Manager**

### Estructura Compartida: `IORequest`

Define cómo estructurar una solicitud de I/O. Está en el archivo `IORequest.h`:

```cpp
struct IORequest {
    int processId;                // ID del proceso que realiza la solicitud
    DeviceType device;            // Tipo de dispositivo: Storage, Keyboard, Display
    OperationType operation;      // Operación: Read, Write
    std::string data;             // Datos para Write (vacío para Read)
    int address;                  // Dirección para Storage (0 para otros)
};
```

### Métodos Públicos del DM

1. **Enviar una solicitud de I/O**:
   - Usa `submitRequest(const IORequest& request)` para agregar una solicitud a la cola del DM.

2. **Procesar solicitudes**:
   - Llama a `processRequests()` para procesar todas las solicitudes pendientes.

3. **Métodos adicionales para interacción directa** (si aplica):
   - `setKeyboardBuffer(const std::string& input)`: Simula entrada en el teclado.
   - `writeToDisplay(const std::string& text)`: Escribe texto en la pantalla.
   - `writeStorage(int address, const std::string& data)`: Escribe datos en almacenamiento.
   - `readStorage(int address)`: Lee datos de almacenamiento.

---

## **Ejemplo de Uso**

### 1. Crear una solicitud de I/O
En el módulo de otro equipo (PM, FSM, UI, etc.), crea una instancia de `IORequest` para representar tu solicitud:

```cpp
IORequest request = {
    1,                          // ID del proceso
    DeviceType::Storage,        // Dispositivo: Almacenamiento
    OperationType::Write,       // Operación: Escribir
    "Hola Mundo",               // Datos a escribir
    10                          // Dirección (para Storage)
};
```

### 2. Enviar la solicitud al DM
Llama al método `submitRequest` del DM para agregar la solicitud a su cola:

```cpp
dm.submitRequest(request);
```

### 3. Procesar solicitudes
El DM procesará las solicitudes pendientes cuando llames a:

```cpp
dm.processRequests();
```

---

## **Integración con Otros Módulos**

- **Gestión de Procesos (PM)**:
  - Enviar solicitudes de I/O usando `submitRequest` y asignar un `processId` único a cada proceso.

- **Sistema de Archivos (FSM)**:
  - Usa dispositivos de almacenamiento (`Storage`) para operaciones de lectura/escritura de bloques.

- **Interfaz de Usuario (UI)**:
  - Simula entradas de teclado con `setKeyboardBuffer`.
  - Escribe en pantalla usando `DeviceType::Display` y `OperationType::Write`.

- **Gestión de Memoria (MM)**:
  - Coordina con el DM si es necesario mapear dispositivos a memoria.

---

## **Compilación y Ejecución**

1. **Compilar**:
   Ejecuta este comando en la terminal para compilar el proyecto:

   ```bash
   g++ -o DeviceManagerTest main.cpp DeviceManager.cpp -std=c++17
   ```

2. **Ejecutar**:
   Corre el ejecutable generado:

   ```bash
   ./DeviceManagerTest    # Linux/Mac
   DeviceManagerTest.exe  # Windows
   ```

---

## **Notas Finales**

- Asegúrate de incluir `IORequest.h` en tu módulo para crear solicitudes compatibles.
- Usa **únicamente** los métodos públicos del `DeviceManager` para interactuar con los dispositivos.
- Si necesitas asistencia con la integración, contáctanos para coordinar cambios o pruebas conjuntas.

¡Gracias por colaborar! 🎉
