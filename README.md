# 🧊 Sistema de Control Automático (On/Off) - Trabajo de Laboratorio Nº1

Este repositorio contiene el código fuente para implementar un sistema de control de temperatura de lazo cerrado (encendido/apagado) para un sistema térmico basado en una célula Peltier, utilizando la plataforma Arduino[cite: 2]. 

El proyecto fue desarrollado para cumplir con los lineamientos de la materia **Sistemas de Control Automático** de la Universidad Nacional de Avellaneda (UNDAV)[cite: 5, 6].

## 🎯 Objetivos del Laboratorio
El sistema fue diseñado cumpliendo con los siguientes propósitos establecidos en la guía oficial[cite: 6]:
* Controlar un sistema físico con una acción de control encendido-apagado[cite: 6].
* Buscar la máxima precisión posible con este modo de acción de control ajustando la configuración[cite: 6].
* Registrar y evaluar la reacción del sistema ante alguna perturbación para analizar si el controlador logra compensarla[cite: 6].
* Utilizar o reconfigurar la experiencia para medir los parámetros del sistema físico a partir de la respuesta medida[cite: 6].

## 📖 Descripción de la Lógica de Control
El control sí-no (on-off) es uno de los modos de acción de control más utilizados por su simpleza[cite: 5]. 

Para proteger el actuador y evitar una conmutación excesiva, el sistema aplica una **ventana de histéresis** o brecha diferencial[cite: 5]. El actuador se enciende cuando se supera el límite superior, y permanece encendido hasta que la variable controlada cruza el límite inferior determinado por esta histéresis[cite: 3, 5].

## 💻 Librería de Control
La lógica de control principal delega la decisión a la librería personalizada **`controlSiNo_sca`**:
* **Autor:** Guillermo Caporaletti (gfcaporaletti@undav.edu.ar)[cite: 3].
* **Institución:** UNDAV, Ingeniería en Informática, Sistemas de Control Automático[cite: 4].
* **Versión:** 2 (Año 2025)[cite: 3, 4].
* **Funcionamiento:** Mediante el método `Controlar()`, procesa la entrada medida y cambia automáticamente el estado del pin de salida configurado[cite: 3, 4].

## ⚙️ Requisitos de Hardware y Software
* **Placa microcontroladora:** Arduino (Uno, Nano, Mega, etc.).
* **Sensor de temperatura:** DS18B20 (comunicación OneWire)[cite: 2].
* **Actuador:** Célula Peltier (manejada a través de un módulo de potencia o relé compatible)[cite: 2].
* **Seguridad:** Pulsador físico para la parada de emergencia y LED indicador[cite: 2, 6].
* **Librerías de Arduino:** `OneWire.h` y `DallasTemperature.h`[cite: 2].
* Archivos locales de la clase de control incluidos: `controlSiNo_sca.h` y `controlSiNo_sca.cpp`[cite: 3, 4].

## 🚀 Instalación y Uso
1. **Conexiones físicas:** 
   * Conecta el pin de datos del sensor DS18B20 al **Pin Digital 4** (recuerda la resistencia pull-up de 4.7kΩ)[cite: 2].
   * Conecta el accionamiento de la célula Peltier al **Pin Digital 8**[cite: 2].
   * Conecta el botón de parada de emergencia al **Pin Digital 3** (hacia GND, usa la resistencia PULLUP interna) y el LED indicador al **Pin 13**[cite: 2].
2. **Ajustar parámetros:** El sistema viene preconfigurado con un tiempo de muestreo de 2000 ms, una **temperatura objetivo de 17 °C** y una **histéresis de +/- 2 °C**[cite: 2].
3. **Cargar:** Conecta el Arduino vía USB y sube el código.
4. **Monitorización:** El sistema enviará por el Monitor Serie los datos tabulados de tiempo, medición de la temperatura y estado de la acción de control[cite: 2, 6]. Si se presiona el botón de parada, se apagará la Peltier, se detendrán las interrupciones y el sistema entrará en un bucle seguro[cite: 2, 6].

## ✍️ Bibliografía y Referencias
* Caporaletti, G. & Castellano, J. M. (2026). *Introducción a sistemas de control automático* (Capítulo 4: Acción de control sí-no)[cite: 5].
* Guía para el Trabajo de Laboratorio Nº1: Control encendido-apagado (UNDAV)[cite: 6].