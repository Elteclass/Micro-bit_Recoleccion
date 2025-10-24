// Al iniciar, muestra un ícono para saber que está listo
basic.showIcon(IconNames.Heart);
// Configura la comunicación serial
serial.redirect(
    SerialPin.USB_TX,
    SerialPin.USB_RX,
    BaudRate.BaudRate38400
);

// Bucle principal
basic.forever(function () {
    // 1. Obtener los datos de los sensores
    let temperatura = input.temperature();
    let nivelLuz = input.lightLevel();
    let accelX = input.acceleration(Dimension.X);

    // 2. Crear un objeto (diccionario) con los datos
    let datosSensores = {
        "temp_c": temperatura,
        "luz": nivelLuz,
        "accel_x": accelX
    };

    // 3. Convertir el objeto a una cadena de texto JSON
    let jsonString = JSON.stringify(datosSensores);

    // 4. Enviar la cadena JSON por el puerto serie, seguida de un salto de línea
    serial.writeLine(jsonString);

    // 5. Pausa de 1 segundo (1000 ms) antes de la siguiente lectura
    basic.pause(1000);
});
