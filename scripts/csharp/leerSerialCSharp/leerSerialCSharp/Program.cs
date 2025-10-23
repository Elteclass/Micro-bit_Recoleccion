using System;
using System.IO.Ports;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.Threading;

namespace LectorSerialCSharp
{
    // 1. Definimos una clase que coincida con la estructura del JSON
    // Usamos [JsonPropertyName] para mapear el snake_case (JSON)
    // al PascalCase (C#).
    public class DatosMicrobit
    {
        [JsonPropertyName("temp_c")]
        public int TempC { get; set; }

        [JsonPropertyName("luz")]
        public int Luz { get; set; }

        [JsonPropertyName("accel_x")]
        public int AccelX { get; set; }
    }

    class Program
    {
        // Bandera para detener el bucle de forma segura con Ctrl+C
        private static bool _continuar = true;

        static void Main(string[] args)
        {
            // ----- Configuración -----
            // !!! CAMBIA "COM3" por tu puerto !!!
            string puertoCOM = "COM3";

            // !!! Asegúrate que sea 9600 (o el que uses en tu micro:bit) !!!
            int baudRate = 38400;
            // -------------------------

            SerialPort puerto = new SerialPort(puertoCOM, baudRate);

            // Asignamos un manejador para el evento Ctrl+C
            Console.CancelKeyPress += new ConsoleCancelEventHandler(ManejadorCtrlC);

            try
            {
                // Configuramos un timeout de lectura.
                // Si no recibe nada en 2 seg, lanza una excepción (que manejamos)
                puerto.ReadTimeout = 2000;
                puerto.Open();
                Console.WriteLine($"Conectado a {puertoCOM} a {baudRate} baudios.");
                Console.WriteLine("Presiona Ctrl+C para detener.");

                // 2. Bucle principal de lectura
                while (_continuar)
                {
                    // Se declara el jsonstring
                    string jsonString = string.Empty;

                    try
                    {
                        // Leemos una línea completa (hasta el '\n')
                        jsonString = puerto.ReadLine();

                        // Si la línea no está vacía...
                        if (!string.IsNullOrEmpty(jsonString))
                        {
                            // 3. Parseamos el JSON
                            DatosMicrobit? datos = JsonSerializer.Deserialize<DatosMicrobit>(jsonString.Trim());

                            if (datos != null)
                            {
                                // 4. Mostramos los datos
                                Console.WriteLine($"Datos: Temp={datos.TempC}°C, Luz={datos.Luz}, AccelX={datos.AccelX}");
                            }
                        }
                    }
                    catch (TimeoutException)
                    {
                        // Es normal que esto ocurra si el micro:bit pausa
                        // y no envía datos por un momento. Simplemente ignoramos
                        // y el bucle vuelve a intentarlo.
                    }
                    catch (JsonException jsonEx)
                    {
                        // Esto captura los errores de JSON corrupto
                        Console.WriteLine($"Error JSON: {jsonEx.Message}. (Recibido: {jsonString.Trim()})");
                    }
                }
            }
            catch (Exception ex)
            {
                // Captura errores al abrir el puerto (ej. puerto no existe o está ocupado)
                Console.WriteLine($"Error: {ex.Message}");
            }
            finally
            {
                // 5. Cerramos el puerto al salir
                if (puerto.IsOpen)
                {
                    puerto.Close();
                    Console.WriteLine("\nConexión serial cerrada.");
                }
            }
        }

        // Manejador para el evento Ctrl+C
        protected static void ManejadorCtrlC(object sender, ConsoleCancelEventArgs args)
        {
            // Le dice al bucle principal que se detenga
            _continuar = false;

            // Previene que el programa termine bruscamente (le da tiempo a 'finally')
            args.Cancel = true;
        }
    }
}