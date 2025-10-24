# 📡 Adquisición de Datos Serial Multi-Lenguaje desde micro:bit

## 📋 Información Académica

- **Autor:** Jaime Antonio Alvarez Crisostomo
- **Materia:** Sistemas Programables
- **Carrera:** Ingeniería en Sistemas Computacionales
- **Institución:** Instituto Tecnológico de Tijuana

---

## 🎯 Descripción del Proyecto

Este es un proyecto integral de la materia de Sistemas Programables, diseñado para demostrar la **interoperabilidad entre hardware embebido y software de alto nivel**. El sistema consiste en un microcontrolador BBC micro:bit que actúa como una estación de sensores, capturando datos del entorno (temperatura, luz y aceleración) y transmitiéndolos en tiempo real a una computadora.

El núcleo del proyecto radica en la implementación de **seis clientes de software independientes**, escritos en:

![Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white)
![JavaScript](https://img.shields.io/badge/JavaScript-F7DF1E?style=for-the-badge&logo=javascript&logoColor=black)
![Node.js](https://img.shields.io/badge/Node.js-339933?style=for-the-badge&logo=nodedotjs&logoColor=white)
![Go](https://img.shields.io/badge/Go-00ADD8?style=for-the-badge&logo=go&logoColor=white)
![C#](https://img.shields.io/badge/C%23-239120?style=for-the-badge&logo=csharp&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Rust](https://img.shields.io/badge/Rust-000000?style=for-the-badge&logo=rust&logoColor=white)
![micro:bit](https://img.shields.io/badge/micro:bit-00ED00?style=for-the-badge&logo=microbit&logoColor=white)
![JSON](https://img.shields.io/badge/JSON-000000?style=for-the-badge&logo=json&logoColor=white)

Cada uno de estos programas es capaz de conectarse al puerto serie, recibir el flujo de datos, interpretarlo y presentarlo al usuario, demostrando cómo un formato de datos estandarizado (JSON) permite que tecnologías completamente dispares consuman la misma fuente de información.

---

## 🏗️ Arquitectura y Funcionamiento

El flujo de trabajo del proyecto es un ciclo simple pero robusto de **"Sensor-a-Pantalla"** que se divide en cuatro etapas clave:

### 1. 📊 Captura (Hardware - micro:bit)
El micro:bit ejecuta un script de MakeCode (JavaScript). En un bucle infinito, el script accede a los sensores integrados para leer:
- La **temperatura ambiente** (en °C)
- El **nivel de luz ambiental** (escala de 0 a 255)
- La **aceleración en el eje X** (datos del giroscopio)

### 2. 📦 Formato (JSON)
Inmediatamente después de la lectura, los tres valores numéricos se empaquetan en un objeto JavaScript y se serializan en un string de formato JSON.

**Ejemplo:**
```json
{"temp_c": 25, "luz": 128, "accel_x": -32}
```

### 3. 📤 Transmisión (Serial)
El micro:bit envía este string JSON a través de la conexión USB usando el protocolo serie (UART). Se utiliza un **baud rate de 38400** para una comunicación rápida y estable. La función `serial.writeLine()` añade un carácter de nueva línea (`\n`) al final de cada JSON, actuando como delimitador.

### 4. 💻 Consumo (PC - Multi-Lenguaje)
En la computadora, uno de los seis scripts se ejecuta:
1. Solicita al sistema operativo acceso al puerto COM correcto (ej. COM3)
2. Configura la conexión para que coincida con el baud rate del micro:bit (38400)
3. Entra en un bucle de escucha, leyendo datos hasta detectar el delimitador (`\n`)
4. Parsea el string JSON, convirtiéndolo en una estructura de datos nativa
5. Imprime los datos estructurados en la consola

---

## 🛠️ Tecnologías Utilizadas

### Hardware
- **Controlador:** BBC micro:bit V2
- **Sensores:** Temperatura, fotodiodo (luz) y acelerómetro integrados

### Software (micro:bit)
- **Plataforma:** Microsoft MakeCode
- **Lenguaje:** JavaScript (para MakeCode)

### Software (PC - Clientes)

#### 🐍 Python (v3.x)
- **Biblioteca Clave:** `pyserial` para gestión del puerto serie
- **Manejo de JSON:** Biblioteca nativa `json`

#### 🟨 JavaScript (Node.js)
- **Biblioteca Clave:** `serialport` para conexión al puerto y `ReadlineParser` para división por líneas
- **Manejo de JSON:** Métodos nativos `JSON.parse()`

#### 🐹 Go (Golang)
- **Biblioteca Clave:** `github.com/tarm/serial` para E/S serial
- **Manejo de JSON:** Biblioteca nativa `encoding/json` para unmarshalling en structs

#### 💜 C# (.NET 6+)
- **Biblioteca Clave:** `System.IO.Ports.SerialPort` (paquete NuGet)
- **Manejo de JSON:** Biblioteca nativa `System.Text.Json`

#### 🦀 Rust
- **Biblioteca Clave:** Crate `serialport` para gestión del puerto
- **Manejo de JSON:** Crates `serde` (framework) y `serde_json` (motor JSON)

#### ⚡ C++ (MSVC / Visual Studio)
- **Biblioteca Clave:** Boost.Asio para operaciones de E/S asíncronas
- **Manejo de JSON:** `nlohmann/json`
- **Gestor de Paquetes:** `vcpkg` para instalar dependencias

### Protocolos
- **Comunicación:** Serial (UART sobre USB)
- **Formato de Datos:** JSON

---

## 🚀 Guía de Configuración y Ejecución

### Requisitos Previos
1. **Flashear el micro:bit:** Carga el archivo `.hex` (compilado con el script de MakeCode a 38400 baud) en tu micro:bit
2. **Identificar el Puerto:** Conecta el micro:bit y verifica su puerto COM en el Administrador de Dispositivos (ej. COM3)
3. **Actualizar Scripts:** Edita el script del lenguaje que deseas probar y cambia la variable del puerto (ej. `PUERTO_SERIAL = "COM3"`)
4. **Exclusividad de Puerto:** Asegúrate de que solo un programa esté usando el puerto a la vez

### Instrucciones de Ejecución

#### 🐍 Python
```bash
cd pc-scripts/python
pip install pyserial
python leer_serial.py
```

#### 🟨 Node.js
```bash
cd pc-scripts/javascript-node
npm install serialport
node leer_serial.js
```

#### 🐹 Go
```bash
cd pc-scripts/go
go mod tidy  # Descarga dependencias
go run leer_serial.go
```

#### 💜 C# (.NET)
```bash
cd pc-scripts/csharp
dotnet run  # Restaura, compila y ejecuta
```

#### ⚡ C++ (Visual Studio)
1. Asegúrate de tener `vcpkg` integrado y las bibliotecas `boost-asio` y `nlohmann-json` instaladas
2. Abre el archivo `.sln` del proyecto en Visual Studio
3. Asegúrate de que la arquitectura de compilación esté en x64
4. Presiona F5 para compilar y ejecutar

#### 🦀 Rust
```bash
cd pc-scripts/rust-lector
cargo run  # Descarga, compila y ejecuta
```

---

## 📊 Tabla Comparativa de Lenguajes

| Lenguaje | Biblioteca(s) Clave(s) | Complejidad de Configuración | Manejo de JSON | Observaciones Técnicas |
|----------|------------------------|------------------------------|----------------|------------------------|
| 🐍 **Python** | `pyserial` | **Baja.** `pip install pyserial` | Nativo (`json`) | **Pro:** El más rápido de implementar. Ideal para scripting y prototipado.<br>**Contra:** Requiere intérprete y dependencias; menos robusto para concurrencia a gran escala. |
| 🟨 **Node.js** | `serialport` | **Baja.** `npm install serialport` | Nativo (`JSON.parse`) | **Pro:** Modelo asíncrono perfecto para E/S. `ReadlineParser` simplifica la lectura.<br>**Contra:** Requiere `node_modules` y npm. |
| 🐹 **Go** | `tarm/serial` | **Media.** `go mod tidy` | Nativo (`encoding/json`) | **Pro:** Compila a binario único sin dependencias. Excelente concurrencia (goroutines). Manejo de errores explícito.<br>**Contra:** Ligeramente más verboso que Python/JS. |
| 💜 **C#** | `System.IO.Ports` | **Media.** Requiere proyecto .NET y paquete NuGet | Nativo (`System.Text.Json`) | **Pro:** Fuerte tipado y excelente integración con IDE. `ReadLine()` simple y robusto.<br>**Contra:** Ligado al ecosistema .NET. |
| ⚡ **C++** | Boost.Asio<br>`nlohmann/json` | **Muy Alta.** Requiere `vcpkg`, configuración compleja de enlazador | Biblioteca externa | **Pro:** Control total sobre hardware y rendimiento.<br>**Contra:** Extremadamente verboso. Alto riesgo de errores de memoria. |
| 🦀 **Rust** | `serialport`<br>`serde_json` | **Media.** `cargo` gestiona todo | Biblioteca externa (`serde`) | **Pro:** Garantías de seguridad de memoria. Manejo de errores robusto con `Result` y `match`.<br>**Contra:** Curva de aprendizaje pronunciada. |

---

## 💭 Reflexión Final

### ¿Qué lenguaje resultó más sencillo para manejar el puerto serial?

**Python** y **JavaScript (Node.js)** empatan como los más sencillos:

- **Python:** La biblioteca `pyserial` es extremadamente directa. Leer una línea (`ser.readline()`) es casi idéntico a leer un archivo de texto. Ideal para prototipado rápido.

- **Node.js:** Aunque requiere un poco más de configuración, su naturaleza asíncrona y basada en eventos (`parser.on('data', ...)`) se siente la más natural para este tipo de tarea.

### ¿Qué lenguaje ofrece mejor manejo de errores?

**🦀 Rust, sin duda.**

Mientras que C# y Python usan `try...catch` (que puede "esconder" errores) y Go usa la verificación explícita de `if err != nil`, el sistema de Rust es superior para un desarrollo robusto.

El uso de los tipos `Result<T, E>` y `Option<T>` **fuerza al programador a manejar cada posible estado de falla en tiempo de compilación**. El compilador no permite ejecutar el programa hasta que hayas manejado explícitamente tanto el éxito (`Ok(...)`) como el fallo (`Err(...)`). Esto elimina clases enteras de errores en tiempo de ejecución y garantiza que los fallos sean manejados de forma controlada.

### ¿Cuál sería más adecuado para un sistema IoT en producción local?

Para un sistema en producción local (ej. un servicio corriendo 24/7 en un servidor o una Raspberry Pi), mi elección sería **Go** o **Rust**.

#### 🐹 Go (Golang)
Probablemente la opción más balanceada. Compila a un binario estático único que no requiere dependencias externas, lo que hace el despliegue trivial. Su manejo de concurrencia (goroutines) es de primera clase y muy ligero, permitiéndole manejar miles de conexiones simultáneamente con bajo uso de memoria.

#### 🦀 Rust
Sería la elección si la **seguridad y la fiabilidad son la prioridad absoluta**. Sus garantías de seguridad de memoria significan que el servicio es mucho menos propenso a crashes por corrupción de memoria o data races. Al igual que Go, compila a un binario nativo de alto rendimiento.

#### ¿Por qué no los otros?

- **Python/Node.js:** Fantásticos, pero gestionar sus entornos de ejecución y dependencias en producción puede ser más frágil.
- **C#:** Opción muy viable (especialmente con .NET en Linux), pero generalmente tiene un footprint más grande que Go o Rust.
- **C++:** El riesgo de errores de gestión de memoria y la complejidad del desarrollo lo hacen menos ideal a menos que se requiera control de hardware de nivel de microsegundos.

---

## 📝 Nota de Desarrollo

Este proyecto se desarrolló como una práctica para la materia de Sistemas Programables. El diseño, la implementación, la depuración y la estructuración de los seis scripts de software del lado del PC se realizaron con la asistencia y colaboración de **Gemini**, el asistente de Inteligencia Artificial de Google.

---

## 📄 Licencia

Este proyecto es de uso académico y educativo.

---

⭐ Si te resultó útil este proyecto, no olvides darle una estrella!
