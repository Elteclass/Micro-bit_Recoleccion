import serial
import json # Importamos la biblioteca JSON

# Reemplaza 'TU_PUERTO_COM' con tu puerto (ej. 'COM3' o '/dev/tty.usbmodem14202')
PUERTO_SERIAL = 'COM3'
BAUD_RATE = 38400

try:
    # Configura y abre la conexión serial
    ser = serial.Serial(PUERTO_SERIAL, BAUD_RATE, timeout=1)
    print(f"Conectado a {PUERTO_SERIAL} a {BAUD_RATE} baudios.")
    print("Presiona Ctrl+C para detener.")

    while True:
        # Lee una línea completa (hasta el salto de línea '\n')
        linea_leida = ser.readline()

        # Si la línea no está vacía...
        if linea_leida:
            # 1. Decodifica de bytes a string (utf-8) y quita espacios en blanco
            json_string = linea_leida.decode('utf-8').strip()

            # 2. Intenta parsear (convertir) el string JSON a un objeto Python
            try:
                datos = json.loads(json_string)
                print(f"Datos recibidos: {datos}")
                # Puedes acceder a los datos individualmente:
                # print(f"Temperatura: {datos['temp_c']} °C")

            except json.JSONDecodeError:
                # Esto pasa si el string no es un JSON válido (ej. un mensaje a medias)
                print(f"Error: No se pudo decodificar JSON. Recibido: {json_string}")

except serial.SerialException as e:
    print(f"Error al abrir el puerto serial: {e}")
except KeyboardInterrupt:
    print("\nLectura detenida por el usuario.")
finally:
    if 'ser' in locals() and ser.is_open:
        ser.close()
        print("Conexión serial cerrada.")