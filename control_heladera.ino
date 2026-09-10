#include "controlSiNo_sca.h"
#include "DHT.h"

// --- Configuración del Sensor DHT ---
#define DHTPIN 2          
#define DHTTYPE DHT22     // Asumimos sensor DTH22 en la heladera

// --- Configuración de la Heladera ---
const int PIN_COMPRESOR = 8; // Pin digital que acciona el relé del compresor

// Instanciamos objetos
DHT dht(DHTPIN, DHTTYPE);
controlSiNo heladera(PIN_COMPRESOR); // Configura el pin de salida por defecto

// --- Parámetros de Control de la heladera ---
// Revisar los parametros en funcion de la heladera
float tempObjetivo = 4.0;    // Temperatura deseada (ej. 4°C)
float histeresis = 1.5;      // Brecha para evitar encendidos constantes (+/- 1.5°C)

// --- Variables para el temporizador (millis) para evitar bloqueos---
unsigned long tiempoAnterior = 0;   // Guarda el último instante en que se leyó el sensor
const long intervalo = 2000;        // Intervalo de muestreo en milisegundos (2 segundos)

// -- Variable para la temperatura obtenida del sensor DHT ---
float temperaturaMedida = 0.0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  // Configura el valor OBJETIVO, su HISTERESIS y el modo de SALIDA
  // SALIDA_INVERTIDA = el motor prende si hace calor y apaga si hace frío
  heladera.Configurar(tempObjetivo, histeresis, SALIDA_INVERTIDA);
}

void loop() {

  unsigned long tiempoActual = millis();

  // -- Si pasaron 2 segundos vuelvo a obtener la temperatura del sensor sin bloquear perturbaciones ---
  
  if (tiempoActual - tiempoAnterior >= intervalo) {
    tiempoAnterior = tiempoActual;
    // 1. Leer la temperatura del sensor
    temperaturaMedida = dht.readTemperature();

    // Comprobar si la lectura falló (muy común en los DHT)
    if (isnan(temperaturaMedida)) {
      Serial.println("¡Error al leer el sensor DHT!");
      delay(2000);
      return; // Romper loop para volver a intentar
    }

    // 2. Ejecutar la lógica de control
    // Controlar() evalúa la medición, cambia el estado del pin si es necesario y devuelve el estado actual
    boolean estadoMotor = heladera.Controlar(temperaturaMedida);

    // 3. Escribimos en el monitor
    Serial.print("Temperatura: ");
    Serial.print(temperaturaMedida);
    Serial.print(" °C | Compresor: ");

    if (estadoMotor) {
      Serial.println("ENCENDIDO");
    } else {
      Serial.println("APAGADO");
    }
  }
}