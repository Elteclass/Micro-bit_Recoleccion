// Archivo: cpp/reader.cpp
#include <iostream>
#include <string>
#include <windows.h> // Para la API serial de Windows
#include <cmath>
#include "nlohmann/json.hpp" // La librería que descargamos

// Usar el alias 'json' para la librería
using json = nlohmann::json;

// !!! CAMBIA ESTO por tu puerto serial !!!
const wchar_t* SERIAL_PORT = L"\\\\.\\COM3";
const int BAUD_RATE = CBR_115200; // Constante de Windows

std::string checkAlerts(const json& data) {
    std::string alerts;
    try {
        double ax = data.at("ax");
        double ay = data.at("ay");
        double az = data.at("az");
        double mag = std::sqrt(ax * ax + ay * ay + az * az);

        if (mag > 1.5) alerts += "🚨 Movimiento brusco | ";
        if (data.at("tempC") > 30.0) alerts += "🌡️ Alta temp | ";
        if (data.at("light") < 20) alerts += "🌑 Baja luz | ";
        if (data.at("bat") < 3.0) alerts += "🔋 Batería baja | ";

        return alerts.empty() ? "✅ Todo OK" : alerts;
    }
    catch (json::exception& e) {
        return std::string("Error en clave JSON: ") + e.what();
    }
}

int main() {
    HANDLE hSerial;
    DCB dcbSerialParams = { 0 };
    COMMTIMEOUTS timeouts = { 0 };

    std::cout << "Conectando a " << SERIAL_PORT << "...\n";

    hSerial = CreateFileW(
        SERIAL_PORT,
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Error al abrir el puerto. Verifica que Mu este cerrado.\n";
        return 1;
    }

    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error obteniendo estado\n";
        CloseHandle(hSerial);
        return 1;
    }

    // Configurar Baud Rate, 8 bits, sin paridad, 1 bit de parada
    dcbSerialParams.BaudRate = BAUD_RATE;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.Parity = NOPARITY;
    dcbSerialParams.StopBits = ONESTOPBIT;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error configurando estado\n";
        CloseHandle(hSerial);
        return 1;
    }

    // Configurar timeouts
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    if (!SetCommTimeouts(hSerial, &timeouts)) {
        std::cerr << "Error configurando timeouts\n";
        CloseHandle(hSerial);
        return 1;
    }

    std::cout << "Conectado. Esperando datos... (Presiona Ctrl+C para salir)\n";

    char buffer[256];
    DWORD bytesRead;
    std::string line_buffer;

    while (true) {
        if (ReadFile(hSerial, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
            if (bytesRead > 0) {
                buffer[bytesRead] = '\0'; // Null-terminar lo leído
                line_buffer += buffer; // Acumular en el buffer de línea

                size_t newline_pos;
                while ((newline_pos = line_buffer.find('\n')) != std::string::npos) {
                    std::string line = line_buffer.substr(0, newline_pos);
                    line_buffer.erase(0, newline_pos + 1); // Quitar la línea procesada

                    if (line.empty() || line == "\r") continue; // Corrección de error
                    line.erase(std::remove(line.begin(), line.end(), '\r'), line.end()); // Limpiar '\r'

                    try {
                        json data = json::parse(line);
                        std::string alerts = checkAlerts(data);
                        std::cout << "[" << data.at("id") << "] Temp: " << data.at("tempC") << "°C | " << alerts << "\n";
                    }
                    catch (json::parse_error& e) {
                        std::cerr << "Error JSON en linea: " << line << "\n" << e.what() << "\n";
                    }
                }
            }
        }
    }
    CloseHandle(hSerial);
    return 0;
}