package main

import (
	"bufio"    // Para leer líneas fácilmente
	"encoding/json" // Para parsear JSON
	"fmt"
	"log"
	"time"

	"github.com/tarm/serial"
)

// Definimos una struct que coincida con nuestro JSON
// Las etiquetas `json:"..."` le dicen a Go cómo mapear los campos
type DatosMicrobit struct {
	Temperatura float64 `json:"temp_c"`
	Luz         int     `json:"luz"`
	AccelX      int     `json:"accel_x"`
}

func main() {
	// Reemplaza 'TU_PUERTO_COM' con tu puerto
	PUERTO := "COM3"
	BAUD_RATE := 38400

	// 1. Configurar el puerto serie
	config := &serial.Config{
		Name:        PUERTO,
		Baud:        BAUD_RATE,
		ReadTimeout: time.Second * 1, // Timeout de lectura
	}

	// 2. Abrir el puerto
	stream, err := serial.OpenPort(config)
	if err != nil {
		log.Fatalf("Error al abrir puerto serial: %v", err)
	}
	// Aseguramos que el puerto se cierre al final
	defer stream.Close()

	log.Printf("Conectado a %s a %d baudios.\n", PUERTO, BAUD_RATE)

	// 3. Crear un "reader" de buffer para leer línea por línea
	reader := bufio.NewReader(stream)

	for {
		// 4. Leer hasta el próximo salto de línea '\n'
		jsonString, err := reader.ReadString('\n')
		if err != nil {
			log.Printf("Error leyendo del serial: %v", err)
			continue // Intenta de nuevo
		}

		if jsonString == "" {
			continue // Línea vacía
		}

		// 5. Parsear el JSON.
		// Creamos una variable del tipo de nuestra struct
		var datos DatosMicrobit

		// Usamos Unmarshal para convertir el string (en bytes) a la struct
		err = json.Unmarshal([]byte(jsonString), &datos)
		if err != nil {
			log.Printf("Error al parsear JSON: %v. Recibido: %s", err, jsonString)
			continue
		}

		// 6. ¡Éxito! Imprimir los datos
		fmt.Printf("Datos recibidos: %+v\n", datos)
		// fmt.Printf("Temperatura: %.2f °C\n", datos.Temperatura)
	}
}