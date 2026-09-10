# 🧊 Sistema de Control Automático para Heladera (On/Off)

Este repositorio contiene el código fuente para implementar un sistema de control de temperatura de lazo cerrado (encendido/apagado) para una heladera o refrigerador, basado en Arduino.

## 📖 Descripción General
El proyecto utiliza un sensor de temperatura y humedad (familia DHT) para monitorear el interior del refrigerador. Cuando la temperatura supera un umbral superior establecido, el sistema activa un relé que enciende el motor del compresor. Una vez que se alcanza la temperatura objetivo inferior, el compresor se apaga. 

La lógica de control principal delega la decisión a la librería personalizada `controlSiNo_sca`, aplicando una ventana de **histéresis** para evitar el encendido/apagado constante y proteger la vida útil del actuador.

## ⚙️ Requisitos de Hardware
* **Placa microcontroladora:** Arduino (Uno, Nano, Mega, etc.)
* **Sensor de temperatura:** DHT22 (recomendado por su precisión y rango) o DHT11.
* **Actuador:** Módulo Relé de 1 canal (para manejar la potencia de 220V/110V del compresor).
* Cables jumper y protoboard.

## 💻 Requisitos de Software y Librerías
* [Arduino IDE](https://www.arduino.cc/en/software)
* Librería **DHT sensor library** por Adafruit (instalable desde el gestor de librerías del IDE).
* Librería **Adafruit Unified Sensor**.
* Archivos locales de la clase de control: `controlSiNo_sca.h` y `controlSiNo_sca.cpp` (incluidos en este repositorio).

## 🚀 Instalación y Uso

1. **Conexiones físicas:**
   * Conecta el pin de señal del sensor DHT al **Pin Digital 2** del Arduino.
   * Conecta el pin de señal del módulo relé al **Pin Digital 8**.
2. **Configurar el entorno:**
   * Clona o descarga este repositorio en tu PC.
   * Asegúrate de que los archivos `controlSiNo_sca.h` y `controlSiNo_sca.cpp` estén ubicados en la misma carpeta que el archivo principal `.ino`.
3. **Ajustar parámetros:**
   * Abre el archivo `.ino` con el IDE de Arduino.
   * Puedes modificar las variables globales `tempObjetivo` (ej. 4.0 °C) e `histeresis` (ej. 1.5 °C) según los requerimientos de tu refrigerador.
4. **Cargar:**
   * Conecta el Arduino por USB, verifica el puerto COM y presiona **Subir**.

## 📐 Principio de Control
El sistema se fundamenta en la teoría de sistemas de control automático en tiempo discreto. Se configura la librería en modo **`SALIDA_INVERTIDA`**:
* **Límite Superior:** `Objetivo + Histéresis` (Enciende el compresor)
* **Límite Inferior:** `Objetivo - Histéresis` (Apaga el compresor)

El retardo de muestreo se implementa de forma no bloqueante utilizando la función `millis()`, consultando al sensor cada 2 segundos sin congelar el flujo de ejecución del procesador.

## ✍️ Referencias
* Lógica de control basada en el libro *"Sistemas de control automatico"*.
* Proyecto desarrollado para la materia de Sistemas de Control Automático.