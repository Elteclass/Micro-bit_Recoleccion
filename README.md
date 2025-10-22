# 🎯 Práctica: Adquisición de Datos Serial con micro:bit

<div align="center">

![micro:bit](https://img.shields.io/badge/micro:bit-V2-00ED00?style=for-the-badge&logo=micro:bit&logoColor=white)
![Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white)
![Node.js](https://img.shields.io/badge/Node.js-339933?style=for-the-badge&logo=node.js&logoColor=white)
![Go](https://img.shields.io/badge/Go-00ADD8?style=for-the-badge&logo=go&logoColor=white)

**Sistemas Programables** | *Instituto Tecnológico de Tijuana*

</div>

---

## 📋 Descripción del Proyecto

Este repositorio contiene una práctica completa de **adquisición de datos de sensores** desde un dispositivo embebido (micro:bit V2) hacia una PC mediante comunicación serial. Los datos se procesan utilizando **tres lenguajes de programación diferentes**: Python, JavaScript (Node.js) y Go.

> 💡 **Objetivo:** Demostrar la integración de hardware embebido con software de procesamiento en múltiples plataformas y lenguajes.

---

## 👨‍💻 Información del Autor

| Campo | Información |
|-------|-------------|
| **Nombre** | Jaime Antonio Alvarez Crisostomo |
| **Materia** | Sistemas Programables |
| **Carrera** | Ingeniería en Sistemas Computacionales |
| **Institución** | Instituto Tecnológico de Tijuana |

---

## 🔧 Funcionamiento

### 🎛️ Componente Hardware (micro:bit)

El código `microbit/makecode.js` programado en **MakeCode (JavaScript)** realiza las siguientes operaciones:

**Ciclo de adquisición (cada 1 segundo):**

1. 🌡️ **Temperatura:** Lee el sensor integrado en grados Celsius
2. 💡 **Nivel de luz:** Captura valores entre 0-255
3. 📊 **Acelerómetro:** Mide la aceleración en el eje X

**Transmisión de datos:**
- Empaqueta los valores en formato **JSON**
- Envía el string completo vía **comunicación serial (USB)**
- Finaliza cada transmisión con salto de línea (`\n`)

### 💻 Componente Software (PC)

Los scripts en `pc-scripts/` se conectan al puerto serial del micro:bit y realizan:

1. ✅ Conexión al puerto COM especificado
2. 📥 Lectura de líneas completas (delimitadas por `\n`)
3. 🔄 Parseo del JSON a estructuras nativas del lenguaje
4. 🖨️ Impresión formateada de los datos en consola

---

## 🚀 Guía de Instalación y Uso

### 📌 Paso 1: Programar el micro:bit

1. Conecta tu **micro:bit V2** a la computadora vía USB
2. Aparecerá una unidad de almacenamiento llamada `MICROBIT`
3. Arrastra el archivo `microbit/microbit-practica.hex` a la unidad
4. El micro:bit se reiniciará automáticamente
5. ✅ Verás un ícono de corazón (❤️) indicando que está transmitiendo datos

### 🔍 Paso 2: Identificar el Puerto COM

Antes de ejecutar los scripts, necesitas identificar el puerto serial:

<table>
<tr>
<td><b>🪟 Windows</b></td>
<td>
Abre el <b>Administrador de dispositivos</b> → <b>Puertos (COM y LPT)</b><br>
Busca: <code>mbed Serial Port (COM3)</code> o similar
</td>
</tr>
<tr>
<td><b>🍎 macOS</b></td>
<td>
Terminal: <code>ls /dev/tty.usbmodem*</code><br>
Ejemplo: <code>/dev/tty.usbmodem14202</code>
</td>
</tr>
<tr>
<td><b>🐧 Linux</b></td>
<td>
Terminal: <code>ls /dev/ttyACM*</code><br>
Ejemplo: <code>/dev/ttyACM0</code>
</td>
</tr>
</table>

> ⚠️ **Importante:** Actualiza la variable `TU_PUERTO_COM` en cada script con el puerto identificado.

### 🎮 Paso 3: Ejecutar los Scripts

Selecciona tu lenguaje de preferencia y sigue las instrucciones:

<details>
<summary><b>🐍 Python</b></summary>
```bash
