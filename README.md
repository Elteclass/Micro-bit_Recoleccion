# Práctica: Adquisición de Datos Serial con micro:bit

Este repositorio contiene el código para una práctica de la materia de Sistemas Programables. El objetivo es demostrar la adquisición de datos de sensores desde un dispositivo embebido (micro:bit) a través de la comunicación serial, y su procesamiento en un PC utilizando tres lenguajes de programación distintos: Python, JavaScript (Node.js) y Go.

---

## Información del Autor

* **Nombre:** Jaime Antonio Alvarez Crisostomo
* **Materia:** Sistemas Programables
* **Carrera:** Ingeniería en Sistemas Computacionales
* **Institución:** Instituto Tecnológico de Tijuana

---

## 1. Funcionamiento

El proyecto se divide en dos componentes principales:

### 1.1. Hardware (micro:bit)

El código `microbit/makecode.js` está programado en MakeCode (JavaScript) y realiza las siguientes tareas:

* En un bucle infinito (cada 1 segundo):
    1.  Lee los sensores integrados de **temperatura** (`°C`).
    2.  Lee el sensor de **nivel de luz** (un valor de 0 a 255).
    3.  Lee el **acelerómetro** en el eje X.
* Empaqueta estos tres valores en un objeto **JSON**.
* Envía el *string* JSON completo a través de la comunicación serial (USB), seguido de un salto de línea (`\n`).

### 1.2. Software (PC)

Los *scripts* en la carpeta `pc-scripts/` se conectan al puerto serie donde está el micro:bit. Cada *script* espera recibir datos, lee una línea completa (hasta el `\n`), y luego "parsea" (decodifica) el *string* JSON para convertirlo en un objeto o estructura nativa del lenguaje, imprimiéndolo finalmente en la consola.

---

## 2. Guía de Instalación y Uso

Sigue estos pasos para ejecutar el proyecto.

### Paso 1: Programar el micro:bit

1.  Conecta tu micro:bit V2 a la computadora.
2.  Aparecerá una nueva unidad llamada `MICROBIT`.
3.  Arrastra y suelta el archivo `microbit/microbit-practica.hex` dentro de esa unidad.
4.  El micro:bit se reiniciará y mostrará un ícono de corazón (❤️). Ya está enviando datos.

### Paso 2: Identificar el Puerto COM

Antes de ejecutar los *scripts*, necesitas saber el nombre del puerto serie de tu micro:bit.

* **En Windows:** Abre el **Administrador de dispositivos** y busca en **Puertos (COM y LPT)**. El nombre será algo como `mbed Serial Port (COM3)`.
* **En macOS:** Abre la terminal y ejecuta `ls /dev/tty.usbmodem*`. El nombre será `/dev/tty.usbmodem14202` o similar.
* **En Linux:** Abre la terminal y ejecuta `ls /dev/ttyACM*`. El nombre será `/dev/ttyACM0` o similar.

**Importante:** En cada uno de los siguientes *scripts*, recuerda abrir el archivo y cambiar la variable `TU_PUERTO_COM` por el puerto que identificaste.

### Paso 3: Ejecutar los Scripts de PC

Puedes ejecutar cualquiera de los tres *scripts*. Asegúrate de estar en la carpeta raíz del proyecto.

#### A. Python 🐍

1.  Navega a la carpeta de Python:
    ```bash
    cd pc-scripts/python
    ```
2.  Instala las dependencias (se recomienda usar un entorno virtual):
    ```bash
    pip install -r requirements.txt
    ```
3.  Ejecuta el script:
    ```bash
    python leer_serial.py
    ```

#### B. JavaScript (Node.js) ⚡

1.  Navega a la carpeta de JavaScript:
    ```bash
    cd pc-scripts/javascript-node
    ```
2.  Instala las dependencias:
    ```bash
    npm install
    ```
3.  Ejecuta el script:
    ```bash
    node leer_serial.js
    ```

#### C. Go 🐿️

1.  Navega a la carpeta de Go:
    ```bash
    cd pc-scripts/go
    ```
2.  Descarga las dependencias registradas en `go.mod`:
    ```bash
    go mod tidy
    ```
3.  Ejecuta el script:
    ```bash
    go run leer_serial.go
    ```

**Resultado esperado:** Verás los datos JSON llegand_o_ a tu terminal cada segundo, impresos por el lenguaje que hayas elegido.
