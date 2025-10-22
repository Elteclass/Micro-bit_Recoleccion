// Importamos las clases necesarias de la biblioteca 'serialport'
const { SerialPort } = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline');

// Reemplaza 'TU_PUERTO_COM' con tu puerto
const PUERTO = 'COM3';
const BAUD_RATE = 38400;

// 1. Creamos la instancia del puerto
const port = new SerialPort({
  path: PUERTO,
  baudRate: BAUD_RATE,
});

// 2. Creamos un "parser" (analizador)
// Esto es muy útil: toma el flujo de bytes y emite un evento "data"
// cada vez que detecta un salto de línea (el que envía el micro:bit)
const parser = port.pipe(new ReadlineParser({ delimiter: '\n' }));

// --- Manejadores de Eventos ---

// Evento 'open': Se dispara cuando la conexión es exitosa
port.on('open', () => {
  console.log(`Conectado a ${PUERTO} a ${BAUD_RATE} baudios.`);
});

// Evento 'data': Se dispara cada vez que el parser detecta una línea completa
parser.on('data', (jsonString) => {
  try {
    // 1. El 'jsonString' ya es un string, lo limpiamos
    const limpio = jsonString.trim();

    // 2. Parseamos el JSON a un objeto JavaScript
    const datos = JSON.parse(limpio);
    console.log("Datos recibidos:", datos);
    // console.log(`Luz: ${datos.luz}`);

  } catch (e) {
    console.warn(`Error al parsear JSON. Recibido: "${jsonString}"`, e.message);
  }
});

// Evento 'error': Manejo de errores
port.on('error', (err) => {
  console.error('Error:', err.message);
});