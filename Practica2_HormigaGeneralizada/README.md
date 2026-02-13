# Hormiga de Langton Generalizada

[![C++](https://img.shields.io/badge/C++-23-blue.svg)](https://isocpp.org/)
[![License](https://img.shields.io/badge/License-Educational-green.svg)]()

## Descripción

Implementación de la **Hormiga de Langton Generalizada** basada en la propuesta de Gale et al. (1995). Este simulador extiende el concepto clásico de la Hormiga de Langton para soportar:

- **Múltiples colores** en las celdas (no solo blanco/negro)
- **Múltiples hormigas** coexistiendo en la misma cinta
- **Diferentes tipos de hormigas** con comportamientos específicos
- **Herencia y polimorfismo** en C++ para implementar los distintos tipos

## Características Principales

✅ **Soporte multicolor** - Celdas con 2-8 colores diferentes  
✅ **Múltiples hormigas** - Varias hormigas pueden coexistir en la misma cinta  
✅ **Tipos de hormigas variados** - DI, DDII, IDID, DIDI, IIII, DDDD  
✅ **Visualización con colores ANSI** - Cada tipo de hormiga y color se distingue visualmente  
✅ **Arquitectura orientada a objetos** - Uso de herencia y polimorfismo dinámico  
✅ **Persistencia de estado** - Guardar y cargar configuraciones  

## Estructura del Proyecto

```
p2_HormigaGeneralizada/
├── src/
│   ├── main.cc
│   ├── ant/
│   │   ├── ant.h           # Clase base abstracta Ant y clases derivadas
│   │   └── ant.cc
│   ├── tape/
│   │   ├── tape.h          # Cinta con soporte multicolor (enum class)
│   │   └── tape.cc
│   └── simulator/
│       ├── simulator.h     # Simulador para múltiples hormigas
│       └── simulator.cc
├── data/
│   ├── config1.txt         # Hormiga DI clásica
│   ├── config2.txt         # Ejemplo del enunciado (DDII + IDID)
│   ├── config3.txt         # Múltiples hormigas variadas
│   └── config4.txt         # Hormigas IIII y DDDD
├── obj/
├── Makefile
└── README.md
```

## Arquitectura del Sistema

### 🎨 Tape (Cinta)
Espacio bidimensional que soporta celdas con múltiples colores:
- Usa `enum class Color` con ámbito para los colores
- Soporta 2-8 colores diferentes por cinta
- Visualización con códigos ANSI para cada color

### 🐜 Ant (Clase Base Abstracta)
Clase base con método virtual puro `move()`:
- Cada tipo de hormiga implementa su propio comportamiento
- Uso de polimorfismo dinámico
- Cada hormiga tiene un color ANSI para visualización

### 📊 Tipos de Hormigas

| Tipo | Descripción | Colores | Patrón |
|------|-------------|---------|--------|
| **DI** | Hormiga clásica de Langton | 2 | D-I |
| **DDII** | Primera mitad derecha, segunda izquierda | 4 | D-D-I-I |
| **IDID** | Alternancia I-D-I-D | 4 | I-D-I-D |
| **DIDI** | Alternancia D-I-D-I | 4 | D-I-D-I |
| **IIII** | Siempre gira izquierda | 4 | I-I-I-I |
| **DDDD** | Siempre gira derecha | 4 | D-D-D-D |

### 🎯 Simulator
Gestiona múltiples hormigas simultáneamente:
- Crea hormigas usando factory pattern
- Mueve todas las hormigas en cada paso
- Detecta colisiones (múltiples hormigas pueden estar en la misma celda)

## Compilación

```bash
# Compilar el proyecto
make

# Limpiar archivos objeto
make clean

# Compilar y ejecutar
make run
```

El ejecutable generado se llamará `p2_HormigaGeneralizada`.

## Uso

### Ejecución

```bash
./p2_HormigaGeneralizada <archivo_configuracion>
```

**Ejemplos:**
```bash
./p2_HormigaGeneralizada data/config1.txt
./p2_HormigaGeneralizada data/config2.txt
./p2_HormigaGeneralizada data/config3.txt
```

### Formato del Archivo de Configuración

```
<tamaño_X> <tamaño_Y> <num_colores>
<TIPO> <X> <Y> <DIR> ; <TIPO> <X> <Y> <DIR> ; ...
[<X> <Y> <color>]
[<X> <Y> <color>]
...
```

**Línea 1:** Dimensiones de la cinta (ancho × alto) y número de colores  
**Línea 2:** Información de cada hormiga separada por `;`  
**Líneas 3+:** Coordenadas y colores de celdas no blancas (opcional)

### Símbolos de Dirección

| Símbolo | Dirección |
|---------|-----------|
| `<` | ← Izquierda (Oeste) |
| `>` | → Derecha (Este) |
| `^` | ↑ Arriba (Norte) |
| `v` | ↓ Abajo (Sur) |

### Ejemplo de Configuración

```
7 10 4
DDII 3 3 > ; IDID 5 7 v
3 4 1
3 5 2
5 5 3
```

Esto crea:
- Cinta de 7×10 con 4 colores
- Hormiga DDII en (3,3) mirando este
- Hormiga IDID en (5,7) mirando sur
- Tres celdas coloreadas inicialmente

## Controles Interactivos

| Tecla | Acción |
|-------|--------|
| **ENTER** | Avanzar un paso en la simulación |
| **s** | Guardar el estado actual |
| **q** | Salir de la simulación |

## Reglas de las Hormigas

### Nomenclatura de Gale et al.

Cada tipo de hormiga se define mediante una cadena de 'D' (Derecha) e 'I' (Izquierda):
- La i-ésima letra indica el giro cuando la hormiga está en una celda del i-ésimo color
- Después de girar, la hormiga cambia el color de la celda (comportamiento cíclico)
- La hormiga avanza una posición en su nueva dirección

### Ejemplo: Hormiga "DDII"

```
Color 0 (Blanco)  → Gira Derecha (D) → Celda cambia a Color 1
Color 1 (Negro)   → Gira Derecha (D) → Celda cambia a Color 2
Color 2 (Rojo)    → Gira Izquierda(I) → Celda cambia a Color 3
Color 3 (Verde)   → Gira Izquierda(I) → Celda cambia a Color 0
```

## Implementación de Conceptos OOP

### Herencia
```cpp
// Clase base abstracta
class Ant {
  virtual void move() = 0;  // Método virtual puro
};

// Clases derivadas
class AntDI : public Ant {
  void move() override { /* ... */ }
};

class AntDDII : public Ant {
  void move() override { /* ... */ }
};
```

### Polimorfismo Dinámico
```cpp
std::vector<Ant*> ants;
ants.push_back(new AntDI(x, y, dir, tape));
ants.push_back(new AntDDII(x, y, dir, tape));

// Cada hormiga ejecuta su propio move()
for (Ant* ant : ants) {
  ant->move();  // Llamada polimórfica
}
```

### Enum Class con Ámbito
```cpp
enum class Color : int {
  WHITE = 0,
  BLACK = 1,
  RED = 2,
  GREEN = 3,
  // ...
};

// Uso seguro de tipos
Color color = Color::RED;
```

## Visualización con ANSI

El simulador utiliza códigos de escape ANSI para visualización en color:

- **Celdas:** Números coloreados según su valor (0-7)
- **Hormigas:** Símbolos direccionales (^v<>) con color específico por tipo
  - DI: Rojo
  - DDII: Verde
  - IDID: Azul
  - DIDI: Cian
  - IIII: Amarillo
  - DDDD: Magenta

## Comportamiento Emergente

Al igual que la hormiga clásica, las hormigas generalizadas exhiben comportamientos fascinantes:

### Hormiga DDII
Tras un período inicial caótico, puede generar estructuras simétricas o "autopistas" diagonales.

### Hormiga IIII/DDDD
Generan patrones circulares o espirales al girar siempre en la misma dirección.

### Múltiples Hormigas
La interacción entre hormigas puede crear patrones emergentes complejos e impredecibles.

## Requisitos del Sistema

- **Compilador:** C++23 o superior (g++, clang++)
- **Sistema Operativo:** Linux, macOS, Windows (con WSL o MinGW)
- **Herramientas:** GNU Make
- **Terminal:** Compatible con códigos ANSI (la mayoría de terminales modernas)

## Características Técnicas

- Arquitectura modular con separación de responsabilidades
- Uso de smart pointers y gestión de memoria (RAII)
- Validación robusta de entradas
- Manejo de excepciones
- Sobrecarga de operadores para E/S
- Factory pattern para creación de hormigas
- Interfaz de usuario interactiva en consola

## Referencias

1. **Langton, C.** (1986). "Studying Artificial Life with Cellular Automata". *Physica D*
2. **Gale, D.; Propp, J.; Sutherland, S.; Troubetzkoy, S.** (1995). "Further Travels with my Ant". *Mathematical Intelligencer* 17: 48-56
3. [Secuencias de escape ANSI](https://gist.github.com/Alfonzzoj/db207b89d56f24d9d0b17ff93e091be8)
4. [Enum class - cppreference.com](https://en.cppreference.com/w/cpp/language/enum.html)

## Recursos Adicionales

- [Langton's Ant - Wikipedia (ES)](https://es.wikipedia.org/wiki/Hormiga_de_Langton)
- [Langton's Ant - Wikipedia (EN)](https://en.wikipedia.org/wiki/Langton%27s_ant)
- [Simulador Online](http://www.langtonant.com/)

## Sobre el Proyecto

Este proyecto fue desarrollado como parte del curso de **Algoritmos y Estructuras de Datos Avanzadas** de la **Universidad de La Laguna**, demostrando conceptos avanzados de:

- Diseño orientado a objetos
- Herencia y polimorfismo dinámico
- Patrones de diseño (Factory)
- Enums con ámbito (scoped enums)
- Gestión de múltiples agentes
- Sistemas complejos y emergencia computacional

---

**Universidad de La Laguna**  
Escuela Superior de Ingeniería y Tecnología  
Grado en Ingeniería Informática  
Práctica 2 - Curso 2025-2026
