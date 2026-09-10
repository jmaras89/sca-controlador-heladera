#include "controlSiNo_sca.h"
#include "DHT.h"

// --- Macros de hardware y tiempo de muestreo ---
#define PIN_SENSOR 2
#define TIPO_SENSOR DHT22
#define PIN_COMPRESOR 8
#define PIN_BOTON_PARADA 3    // Pin para el botón de emergencia (usaremos la resistencia PULLUP interna)
#define PIN_LED_PARADA 13     // LED integrado en la placa para indicar la parada
#define TIEMPO_MUESTREO 2000  // Tiempo de muestreo en milisegundos

// --- Inicialización de objetos ---
DHT dht(PIN_SENSOR, TIPO_SENSOR);

// Para la acción de control se utiliza el módulo Control si-no
controlSiNo heladera(PIN_COMPRESOR);

// --- Parámetros y Variables Globales ---
float tempObjetivo = 4.0;
float histeresis = 1.5;

float temperaturaMedida = 0.0;
boolean estadoMotor = false;
unsigned long tiempoActual = 0;
unsigned long tiempoAnterior = 0;

// --- Funciones de Configuración ---
void configurar_hardware() {
  // Función de configuración para el botón de parada y pin de medición
  pinMode(PIN_BOTON_PARADA, INPUT_PULLUP); // Pulsador conectado entre el pin 3 y GND
  pinMode(PIN_LED_PARADA, OUTPUT);
  digitalWrite(PIN_LED_PARADA, LOW);
  
  dht.begin();
  
  // Configuración del controlador
  heladera.Configurar(tempObjetivo, histeresis, SALIDA_INVERTIDA); 
}

void imprimir_encabezado() {
  // Imprime información, parámetros (objetivo e histéresis) y columnas
  Serial.println("==================================================");
  Serial.println("TL N° 1: Sistema de Control On/Off para Heladera");
  Serial.print("Parametros configurados -> Objetivo: ");
  Serial.print(tempObjetivo);
  Serial.print(" C | Histeresis: +/- ");
  Serial.print(histeresis);
  Serial.println(" C");
  Serial.println("==================================================");
  
  // Identificación de cada columna que se imprimirá
  Serial.println("Tiempo(ms)\tMedicion(C)\tAccion_de_control");
}

void setup() {
  Serial.begin(9600);
  configurar_hardware();
  imprimir_encabezado(); 
}

// --- Funciones de Lógica de Control ---
bool boton_parada_presionado() {
  // Detecta el pulsador evitando la función bloqueante delay()
  return digitalRead(PIN_BOTON_PARADA) == LOW; 
}

void parada() {
  // Apaga el actuador
  heladera.Apagar(); 
  
  // Apaga toda interrupción
  noInterrupts(); 
  
  // Envía un mensaje a la PC
  Serial.println("\n*** PARADA DE EMERGENCIA ACTIVADA. SISTEMA DETENIDO. ***");
  
  // Queda en estado de ciclo infinito dejando un led encendido
  while (true) {
    digitalWrite(PIN_LED_PARADA, HIGH); 
  }
}

bool debo_muestrear() {
  // Utilizamos millis() para no bloquear con delay
  tiempoActual = millis();
  if (tiempoActual - tiempoAnterior >= TIEMPO_MUESTREO) {
    tiempoAnterior = tiempoActual;
    return true;
  }
  return false;
}

void medir() {
  // Obtiene la muestra de la variable controlada
  temperaturaMedida = dht.readTemperature();
}

void actuar() {
  // Utiliza el procedimiento de control del módulo
  if (!isnan(temperaturaMedida)) {
    estadoMotor = heladera.Controlar(temperaturaMedida);
  }
}

void mostrar_datos() {
  // Enviamos el monitor
  if (!isnan(temperaturaMedida)) {
    Serial.print(tiempoActual);
    Serial.print("\t\t");
    Serial.print(temperaturaMedida);
    Serial.print("\t\t");
    Serial.println(estadoMotor ? "ENCENDIDO" : "APAGADO");
  } else {
    Serial.println("Error\t\t---\t\t---");
  }
}

// --- Main Loop ---
void loop() {
  if (boton_parada_presionado()) {
    parada();
  }
  
  if (debo_muestrear()) {
    medir();
    actuar();
    mostrar_datos();
  }
}