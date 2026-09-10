# 🧊 Sistema de Control Automático (On/Off) - Trabajo de Laboratorio Nº1

Este repositorio contiene el código fuente para implementar un sistema de control de temperatura de lazo cerrado (encendido/apagado) para una heladera o sistema térmico, basado en la plataforma Arduino. 

El proyecto fue desarrollado para cumplir con los lineamientos de la materia **Sistemas de Control Automático** de la Universidad Nacional de Avellaneda (UNDAV)

## 🎯 Objetivos del Laboratorio
El sistema fue diseñado cumpliendo con los siguientes propósitos establecidos en la guía oficial
* Controlar un sistema físico con una acción de control encendido-apagado
* Buscar la máxima precisión posible con este modo de acción de control ajustando la configuración.
* Registrar y evaluar la reacción del sistema ante alguna perturbación (como la apertura de la puerta) para analizar si el controlador logra compensarla.
* Utilizar o reconfigurar la experiencia para medir los parámetros del sistema físico a partir de la respuesta medida.

## 📖 Descripción de la Lógica de Control
El control sí-no (on-off) es uno de los modos de acción de control más utilizados en la industria y en los equipos domésticos por su simpleza

Para proteger la vida útil del actuador (el motor del compresor) y evitar que se encienda y apague constantemente ante la mínima variación, el sistema aplica una **ventana de histéresis** o brecha diferencial. El actuador recibe la señal de encendido cuando se supera el límite superior, y permanece encendido hasta que la variable controlada cruza el límite inferior determinado por esta histéresis.

## 💻 Librería de Control
La lógica de control principal delega la decisión a la librería personalizada **`controlSiNo_sca`**:
* **Autor:** Guillermo Caporaletti (gfcaporaletti@undav.edu.ar).
* **Institución:** UNDAV, Ingeniería en Informática, Sistemas de Control Automático.
* **Versión:** 2 (Año 2025).
* **Funcionamiento:** La librería es instanciada a través de programación orientada a objetos (POO) y restringe el constructor a la configuración inicial de hardware. Mediante el método `Controlar()`, procesa la entrada medida y cambia automáticamente el estado del pin de salida configurado.

## ⚙️ Requisitos de Hardware y Software
* **Placa microcontroladora:** Arduino (Uno, Nano, Mega, etc.).
* **Sensor de temperatura:** DS18B20 (mediante librerías `OneWire` y `DallasTemperature`) o familia DHT.
* **Actuador:** Módulo Relé de 1 canal.
* **Seguridad:** Pulsador físico para la parada de emergencia.
* Archivos locales de la clase de control incluidos: `controlSiNo_sca.h` y `controlSiNo_sca.cpp`

## 🚀 Instalación y Uso
1. **Conexiones físicas:** Conecta el sensor de temperatura, el módulo relé al pin de salida del compresor y el pulsador de parada de emergencia a un pin con soporte de interrupción o lectura no bloqueante.
2. **Ajustar parámetros:** Abre el archivo `.ino` con el Arduino IDE. Modifica la variable global de temperatura objetivo y la histéresis para buscar un equilibrio entre la máxima precisión posible y una frecuencia de conmutación segura para el relé.
3. **Cargar:** Conecta el Arduino vía USB y sube el código.
4. **Monitorización:** El sistema enviará por puerto serie los datos tabulados de tiempo, medición de la variable controlada y estado de la acción de control para su posterior graficación y análisis de parámetros.

## ✍️ Bibliografía y Referencias
* Caporaletti, G. & Castellano, J. M. (2026). *Introducción a sistemas de control automático* (Capítulo 4: Acción de control sí-no)
* Guía para el Trabajo de Laboratorio Nº1: Control encendido-apagado (UNDAV).