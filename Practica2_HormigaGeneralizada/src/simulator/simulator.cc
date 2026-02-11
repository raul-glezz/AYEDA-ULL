/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   simulator.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   11/02/2026
 * @brief  Definición de la clase Simulator, que gestiona la simulación con múltiples hormigas.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

#include "simulator.h"
#include "../ant/DI/di.h"
#include "../ant/DDII/ddii.h"
#include "../ant/IDID/idid.h"
#include "../ant/IIII/iiii.h"
#include "../ant/DDDD/dddd.h"
#include "../ant/DIDI/didi.h"

/**
 * @brief Constructor de la simulación desde un fichero de configuración.
 * @param[in] filename: nombre del fichero de configuración.
 * @throws std::runtime_error si no se puede abrir el fichero.
 */
Simulator::Simulator(const std::string& filename) {
  steps_ = 0;
  std::ifstream file(filename);
  
  if (!file.is_open()) {
    throw std::runtime_error("Error: No se puede abrir el fichero: " + filename);
  }
  
  // Línea 1: Tamaño de la cinta y número de colores
  int size_X, size_Y, num_colors;
  file >> size_X >> size_Y >> num_colors;
  
  // Creamos la cinta
  tape_ = new Tape(size_X, size_Y, num_colors);
  
  // Consumimos el salto de línea después de la primera línea
  file.ignore();
  
  // Línea 2: Tipo, posición y orientación de cada hormiga
  std::string ants_line;
  std::getline(file, ants_line);
  
  // Parseamos a las hormigas
  std::stringstream ss(ants_line);
  std::string ant_spec;
  
  while (std::getline(ss, ant_spec, ';')) {
    // Eliminamos los espacios iniciales y finales
    ant_spec.erase(0, ant_spec.find_first_not_of(" \t\n\r"));
    ant_spec.erase(ant_spec.find_last_not_of(" \t\n\r") + 1);
    
    if (ant_spec.empty()) continue;
    
    // Parseamos: TIPO X Y DIRECCION
    std::stringstream ant_ss(ant_spec);
    std::string type;
    int x, y;
    std::string dir_symbol;
    
    ant_ss >> type >> x >> y >> dir_symbol;
    
    Direction direction = parseDirection(dir_symbol);
    
    // Creamos la hormiga del tipo especificado
    Ant* ant = createAnt(type, x, y, direction);
    if (ant) { ants_.push_back(ant); }
  }
  
  // Líneas 3..n: Posición y color de las celdas no blancas
  int x, y, color;
  while (file >> x >> y >> color) {
    if (tape_->isValidPosition(x, y)) {
      tape_->setCell(x, y, color);
    }
  }
  
  file.close();
}

/**
 * @brief Destructor de la simulación.
 */
Simulator::~Simulator() {
  // Eliminamos todas las hormigas
  for (Ant* ant : ants_) { delete ant; }
  ants_.clear();
  
  // Eliminamos la cinta
  delete tape_;
}

/**
 * @brief Crear una hormiga del tipo especificado usando polimorfismo.
 * @param[in] type: cadena que identifica el tipo de hormiga.
 * @param[in] x: posición X inicial.
 * @param[in] y: posición Y inicial.
 * @param[in] direction: dirección inicial.
 * @return Puntero a la hormiga creada o nullptr si el tipo no es reconocido.
 */
Ant* Simulator::createAnt(const std::string& type, int x, int y, Direction direction) {
  if (type == "DI") {
    return new AntDI(x, y, direction, tape_);
  } else if (type == "DDII") {
    return new AntDDII(x, y, direction, tape_);
  } else if (type == "IDID") {
    return new AntIDID(x, y, direction, tape_);
  } else if (type == "IIII") {
    return new AntIIII(x, y, direction, tape_);
  } else if (type == "DDDD") {
    return new AntDDDD(x, y, direction, tape_);
  } else if (type == "DIDI") {
    return new AntDIDI(x, y, direction, tape_);
  }
  
  std::cerr << "Error: El tipo de hormiga '" << type << "' no es reconocido. Se ignorará esta hormiga." << std::endl;
  return nullptr;
}

/**
 * @brief Parsea el símbolo de dirección.
 * @param[in] symbol: símbolo de dirección.
 * @return Dirección correspondiente.
 */
Direction Simulator::parseDirection(const std::string& symbol) const {
  if (symbol == "<") return LEFT;
  if (symbol == ">") return RIGHT;
  if (symbol == "^") return UP;
  if (symbol == "v") return DOWN;
  
  // Por defecto, se asume que la dirección es RIGHT si el símbolo no es reconocido
  std::cerr << "Advertencia: Símbolo de dirección '" << symbol << "' no reconocido. Se asumirá dirección RIGHT." << std::endl;
  return RIGHT;
}

/**
 * @brief Realizar un paso de la simulación.
 */
void Simulator::step() {
  if (!isFinished()) {
    // Movemos cada hormiga
    for (Ant* ant : ants_) {
      if (!ant->isOutOfBounds()) {
        ant->move();
      }
    }
    steps_++;
  }
}

/**
 * @brief Ejecutar la simulación hasta que todas las hormigas salgan de los límites.
 */
void Simulator::run() {
  std::string input;
  
  // Continuamos mientras que al menos una hormiga esté dentro de los límites
  while (!isFinished()) {
    clearScreen();
    std::cout << *this;
    
    std::cout << "\nPresiona ENTER para continuar, 's' para guardar, 'q' para salir: ";
    std::getline(std::cin, input);
    
    if (input == "q" || input == "Q") {
      break;
    } else if (input == "s" || input == "S") {
      std::string filename;
      std::cout << "Introduzca el nombre del fichero para guardar: ";
      std::getline(std::cin, filename);
      try {
        saveState(filename);
        std::cout << "Estado guardado correctamente en " << filename << std::endl;
        std::cout << "Presiona ENTER para continuar...";
        std::getline(std::cin, input);
      } catch (const std::exception& exception) {
        std::cerr << "Error al guardar: " << exception.what() << std::endl;
        std::cout << "Presiona ENTER para continuar...";
        std::getline(std::cin, input);
      }
      continue;
    }
    
    step();
  }
  
  // Si todas las hormigas han salido, mostramos el estado final
  if (isFinished()) {
    clearScreen();
    std::cout << *this;
    std::cout << "\n¡Todas las hormigas han salido de los límites de la cinta!" << std::endl;
  }
  
  // Preguntamos si desea guardar el estado final
  std::cout << "\n¿Desea guardar el estado final? (s/n): ";
  std::getline(std::cin, input);
  
  if (input == "s" || input == "S") {
    std::string filename;
    std::cout << "Introduzca el nombre del fichero para guardar: ";
    std::getline(std::cin, filename);
    try {
      saveState(filename);
      std::cout << "Estado guardado correctamente en " << filename << std::endl;
    } catch (const std::exception& exception) {
      std::cerr << "Error al guardar: " << exception.what() << std::endl;
    }
  }
}

/**
 * @brief Verificar si la simulación ha terminado.
 * @return true si todas las hormigas han salido de los límites, false en caso contrario.
 */
bool Simulator::isFinished() const {
  for (const Ant* ant : ants_) {
    if (!ant->isOutOfBounds()) {
      return false;
    }
  }
  return true;
}

/**
 * @brief Guarda el estado actual de la simulación en un fichero.
 * @param[in] filename: nombre del fichero donde se guardará el estado.
 */
void Simulator::saveState(const std::string& filename) const {
  // Vector de información de hormigas
  std::vector<std::tuple<std::string, int, int, int>> ants_info;
  
  for (const Ant* ant : ants_) {
    ants_info.emplace_back(
      ant->getType(),
      ant->getX(),
      ant->getY(),
      static_cast<int>(ant->getDirection())
    );
  }
  
  tape_->saveToFile(filename, ants_info);
}

/**
 * @brief Limpia la pantalla de la consola.
 */
void Simulator::clearScreen() const { 
  system("clear"); 
}

/**
 * @brief Sobrecarga del operador de inserción en flujo (<<) para la clase Simulator.
 * @param[in,out] os: referencia al flujo de salida (std::cout).
 * @param[in] simulator: referencia al objeto Simulator cuyo estado se mostrará.
 * @return Referencia al flujo de salida (std::cout).
 */
std::ostream& operator<<(std::ostream& os, const Simulator& simulator) {
  os << "=== Hormiga de Langton Generalizada ===" << std::endl;
  os << "Paso: " << simulator.getSteps() << std::endl;
  os << "Número de hormigas: " << simulator.getAnts().size() << std::endl;
  
  // Mostrar información de cada hormiga
  for (size_t i = 0; i < simulator.getAnts().size(); i++) {
    const Ant* ant = simulator.getAnts()[i];
    os << "  Hormiga " << (i + 1) << " (tipo " << ant->getType() << "): "
       << "posición (" << ant->getX() << ", " << ant->getY() << ")";
    
    if (ant->isOutOfBounds()) {
      os << " [FUERA DE LÍMITES]";
    }
    os << std::endl;
  }
  os << std::endl;
  
  // Obtenemos las posiciones de todas las hormigas para mostrarlas
  std::vector<std::pair<int, int>> ant_positions;
  for (const Ant* ant : simulator.getAnts()) {
    ant_positions.emplace_back(ant->getX(), ant->getY());
  }
  
  // Borde superior
  os << "  +";
  for (int x = 0; x < simulator.getTape()->getSizeX(); x++) {
    os << "-";
  }
  os << "+" << std::endl;
  
  // Celdas con las hormigas
  for (int y = 0; y < simulator.getTape()->getSizeY(); y++) {
    os << "  |";
    
    for (int x = 0; x < simulator.getTape()->getSizeX(); x++) {
      // Verificar si hay alguna hormiga en esta posición
      bool ant_found = false;
      for (size_t i = 0; i < simulator.getAnts().size(); i++) {
        const Ant* ant = simulator.getAnts()[i];
        if (ant->getX() == x && ant->getY() == y && !ant->isOutOfBounds()) {
          os << *ant;
          ant_found = true;
          break;
        }
      }
      
      if (!ant_found) {
        // Mostramos la celda
        simulator.getTape()->printCell(os, x, y);
      }
    }
    
    os << "|" << std::endl;
  }
  
  // Borde inferior
  os << "  +";
  for (int x = 0; x < simulator.getTape()->getSizeX(); x++) {
    os << "-";
  }
  os << "+" << std::endl;

  return os;
}