use std::io::{BufRead, BufReader}; // Para leer líneas de forma eficiente
use std::time::Duration; // Para definir el timeout
use serialport::SerialPort; // El trait principal de serialport
use serde::Deserialize; // Para poder deserializar JSON

// 1. Definimos una "struct" que coincida con el JSON que envía el micro:bit.
// #[derive(Deserialize)] le dice a 'serde' que genere automáticamente
// el código para convertir un JSON en esta struct.
#[derive(Deserialize, Debug)]
struct DatosMicrobit {
    // #[serde(rename = "...")] le dice a serde cómo mapear el nombre
    // del campo en JSON (snake_case) a nuestro campo en Rust.
    #[serde(rename = "temp_c")]
    temp_c: i32,
    
    #[serde(rename = "luz")]
    luz: i32,
    
    #[serde(rename = "accel_x")]
    accel_x: i32,
}

fn main() {
    // ----- Configuración -----
    // !!! CAMBIA "COM3" por tu puerto !!!
    let puerto_nombre = "COM3";
    
    // !!! Asegúrate que sea 9600 (o el que uses en tu micro:bit) !!!
    let baud_rate = 38400;
    // -------------------------

    println!("Intentando conectar a {} a {} baudios.", puerto_nombre, baud_rate);

    // 2. Configurar y abrir el puerto.
    // 'serialport::new' crea la configuración.
    // '.timeout' es importante para que no se bloquee si no hay datos.
    let puerto = serialport::new(puerto_nombre, baud_rate)
        .timeout(Duration::from_millis(2000)) // Timeout de 2 segundos
        .open();

    // 3. Manejar la apertura del puerto.
    // En Rust, 'open()' devuelve un tipo 'Result', que puede ser
    // 'Ok(puerto_abierto)' si tuvo éxito, o 'Err(error)' si falló.
    match puerto {
        Ok(mut puerto_abierto) => {
            println!("Conectado con éxito a {}. Presiona Ctrl+C para detener.", puerto_nombre);
            
            // 4. Creamos un 'BufReader' (Lector con Búfer).
            // Esto nos permite usar .read_line(), que es mucho más fácil
            // que leer byte por byte.
            let mut lector_serial = BufReader::new(puerto_abierto);
            let mut json_string = String::new(); // Un string vacío para guardar la línea leída

            // 5. Bucle principal de lectura
            loop {
                // Limpiamos el string antes de cada nueva lectura
                json_string.clear();

                // 6. Intentamos leer una línea (hasta el '\n')
                match lector_serial.read_line(&mut json_string) {
                    Ok(_) => {
                        // Si se leyó algo...
                        if !json_string.trim().is_empty() {
                            
                            // 7. Parsear el JSON
                            // 'serde_json::from_str' también devuelve un 'Result'
                            let resultado_json: Result<DatosMicrobit, _> = serde_json::from_str(&json_string);
                            
                            match resultado_json {
                                Ok(datos) => {
                                    // ¡Éxito! Imprimimos con formato de depuración
                                    // El ':?' en 'println!' le dice que lo imprima bonito.
                                    println!("Datos recibidos: {:?}", datos);
                                }
                                Err(e) => {
                                    // Esto captura JSON corrupto
                                    println!("Error al parsear JSON: {}. (Recibido: {})", e, json_string.trim());
                                }
                            }
                        }
                    }
                    Err(e) => {
                        // Esto captura errores de lectura del puerto (ej. timeout o desconexión)
                        // Si es un Timeout, simplemente volverá a intentar en el loop.
                        println!("Error de lectura serial: {}", e);
                    }
                }
            }
        }
        Err(e) => {
            // Esto captura errores al ABRIR el puerto (ej. "COM3" no existe)
            eprintln!("Error al abrir el puerto {}: {}", puerto_nombre, e);
            eprintln!("Asegúrate de cambiar 'puerto_nombre' en el código y que el puerto no esté en uso.");
        }
    }
}