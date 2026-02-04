# Hormiga de Langton

[![C++](https://img.shields.io/badge/C++-11-blue.svg)](https://isocpp.org/)
[![License](https://img.shields.io/badge/License-Educational-green.svg)]()

## Descripción

Simulador interactivo de la **Hormiga de Langton**, un autómata celular bidimensional creado por Christopher Langton en 1986. A pesar de sus reglas extremadamente simples, este autómata genera patrones complejos y comportamiento emergente, siendo considerado un ejemplo clásico de sistemas complejos y computación universal.

## Características Principales

✅ **Simulación paso a paso** con control interactivo  
✅ **Persistencia de estado** - Guardar y cargar configuraciones  
✅ **Visualización en tiempo real** mediante interfaz de texto  
✅ **Configuración flexible** desde archivos de entrada  
✅ **Detección automática** de límites de la cinta  
✅ **Manejo robusto de errores** y validación de entradas

## Estructura del Proyecto

```
p1_HormigaDeLangton/
├── src/
│   ├── main.cc
│   ├── ant/
│   │   ├── ant.h
│   │   └── ant.cc
│   ├── tape/
│   │   ├── tape.h
│   │   └── tape.cc
│   └── simulator/
│       ├── simulator.h
│       └── simulator.cc
├── data/
│   ├── config.txt
│   ├── config2.txt
│   └── config3.txt
├── obj/
├── Makefile
└── README.md
```

## Componentes del Sistema

### 🐜 Simulador
Motor principal que coordina la ejecución de la simulación, gestiona el ciclo de vida del programa y proporciona la interfaz de usuario para interactuar con el autómata.

### 🎯 Hormiga
Agente autónomo que navega sobre la cinta siguiendo las reglas de Langton. Mantiene su posición, orientación y ejecuta los movimientos según el estado de las celdas.

### 📊 Cinta
Espacio bidimensional de celdas binarias donde evoluciona el autómata. Gestiona el estado de cada celda y proporciona métodos para consultar y modificar la configuración

### Compilación

```bash
# Compilar el proyecto
make

# Limpiar archivos objeto
make clean

# Recompilar desde cero
make rebuild
```

El ejecutable generado se llamará `langton`.

## Inicio Rápido

### Ejecución

```bash
./langton <archivo_configuracion>
```

**Ejemplos:**
```bash
./langton data/config.txt
./langton data/config2.txt
./langton data/config3.txt
```

## Configuración

### Formato del Archivo de Configuración

El archivo de configuración define el estado inicial de la simulación mediante un formato de texto simple:

```
<tamaño_X> <tamaño_Y>
<pos_X> <pos_Y> <dirección>
[<celda_X> <celda_Y>]
[<celda_X> <celda_Y>]
...
```

**Línea 1:** Dimensiones de la cinta (ancho × alto)  
**Línea 2:** Posición inicial de la hormiga (X, Y) y su dirección  
**Líneas siguientes:** Coordenadas de celdas negras iniciales (opcional)

### Direcciones

| Valor | Dirección |
|-------|-----------|
| `0`   | ← Izquierda |
| `1`   | → Derecha   |
| `2`   | ↑ Arriba    |
| `3`   | ↓ Abajo     |

### Ejemplo de Configuración

```
40 30
20 15 2
10 10
10 11
15 15
```

Esto crea una cinta de 40×30, posiciona la hormiga en (20, 15) mirando hacia arriba, y establece tres celdas negras en las posiciones especificadas.

## Uso Interactivo

Durante la ejecución de la simulación, el programa muestra el estado actual y espera comandos del usuario:

### Controles

| Tecla | Acción |
|-------|--------|
| **ENTER** | Avanzar un paso en la simulación |
| **s** | Guardar el estado actual en un archivo |
| **q** | Salir de la simulación |

### Interfaz de Visualización

```
=== Hormiga de Langton ===
Paso: 42
Hormiga en posición (20, 15)

+----------------------------------------+
|                                        |
|                                        |
|          X X                           |
|            ^                           |
|                                        |
+----------------------------------------+
```

- `X` representa celdas negras
- Espacios representan celdas blancas  
- La hormiga se muestra con símbolos direccionales: `^` `v` `<` `>`

## Reglas del Autómata

La Hormiga de Langton opera bajo dos reglas simples que se aplican en cada paso:

### 📌 Regla 1: Celda Blanca
1. Invertir el color de la celda (blanco → negro)
2. Girar 90° a la **izquierda**
3. Avanzar una celda en la nueva dirección

### 📌 Regla 2: Celda Negra
1. Invertir el color de la celda (negro → blanco)
2. Girar 90° a la **derecha**
3. Avanzar una celda en la nueva dirección

## Comportamiento Emergente

A pesar de sus reglas extremadamente simples, la Hormiga de Langton exhibe un comportamiento fascinante dividido en tres fases distintas:

### 🔹 Fase 1: Simplicidad (~100 pasos)
Patrones simples, regulares y mayormente simétricos. La hormiga crea estructuras predecibles.

### 🔹 Fase 2: Caos (~100-10,000 pasos)
Comportamiento aparentemente aleatorio sin patrones claros. El camino parece impredecible y caótico.

### 🔹 Fase 3: Emergencia (~10,000+ pasos)
Sorprendentemente, surge un patrón repetitivo llamado "autopista" o "highway" que se extiende indefinidamente en diagonal, demostrando orden emergente desde el caos.

## Persistencia de Estado

### Guardar Estado

Durante la simulación, presiona `s` y proporciona un nombre de archivo. El estado se guardará en el mismo formato que los archivos de configuración, permitiendo:

- Continuar simulaciones interrumpidas
- Compartir configuraciones interesantes
- Crear puntos de control para análisis

### Cargar Estado

Simplemente ejecuta el programa con el archivo guardado como argumento:

```bash
./langton mi_estado_guardado.txt
```

## Requisitos del Sistema

- **Compilador:** C++11 o superior (g++, clang++)
- **Sistema Operativo:** Linux, macOS, Windows (con WSL o MinGW)
- **Herramientas:** GNU Make

## Características Técnicas

- Arquitectura modular orientada a objetos
- Gestión automática de memoria
- Validación robusta de entradas
- Manejo de excepciones
- Sobrecarga de operadores para E/S
- Interfaz de usuario interactiva en consola

## Recursos Adicionales

### Referencias

- [Langton's Ant - Wikipedia (ES)](https://es.wikipedia.org/wiki/Hormiga_de_Langton)
- [Langton's Ant - Wikipedia (EN)](https://en.wikipedia.org/wiki/Langton%27s_ant)
- [Christopher Langton - Vida Artificial](https://es.wikipedia.org/wiki/Christopher_Langton)
- [Simulador Online Interactivo](http://www.langtonant.com/)

### Sobre el Proyecto

Este proyecto fue desarrollado como parte del curso de **Algoritmos y Estructuras de Datos Avanzadas** de la **Universidad de La Laguna**, demostrando conceptos de:

- Diseño orientado a objetos
- Patrones de diseño
- Gestión de E/S en C++
- Simulación de sistemas complejos
- Emergencia computacional

---

**Universidad de La Laguna**  
Escuela Superior de Ingeniería y Tecnología  
Grado en Ingeniería Informática  
Curso 2025-2026
