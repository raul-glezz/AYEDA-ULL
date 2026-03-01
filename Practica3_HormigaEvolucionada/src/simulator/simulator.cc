/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 3: Hormiga de Langton Evolucionada
 *
 * @file   simulator.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Definición de la clase Simulator, que gestiona la simulación con múltiples hormigas.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <map>
#include <limits>

#include "simulator.h"

// Hormigas herbívoras
#include "../ant/herbivore/HDI/h_di.h"
#include "../ant/herbivore/HDDII/h_ddii.h"
#include "../ant/herbivore/HIDID/h_idid.h"
#include "../ant/herbivore/HDIDI/h_didi.h"
#include "../ant/herbivore/HIIII/h_iiii.h"
#include "../ant/herbivore/HDDDD/h_dddd.h"
// Hormigas carnívoras
#include "../ant/carnivore/CIDID/c_idid.h"
#include "../ant/carnivore/CDDII/c_ddii.h"
#include "../ant/carnivore/CDIDI/c_didi.h"
#include "../ant/carnivore/CIIII/c_iiii.h"
#include "../ant/carnivore/CDDDD/c_dddd.h"
// Cintas
#include "../tape/types/sliding/sliding.h"
#include "../tape/types/reflective/reflective.h"
#include "../tape/types/periodic/periodic.h"

/**
 * @brief Constructor de la simulación desde un fichero de configuración.
 * @param[in] filename: nombre del fichero de configuración.
 * @throws std::runtime_error si no se puede abrir el fichero.
 */
Simulator::Simulator(const std::string& filename) : tape_(nullptr), steps_(0) {
  std::ifstream file(filename);
  
  if (!file.is_open()) {
    throw std::runtime_error("Error: No se puede abrir el fichero: " + filename);
  }
  
  file >> (*this);
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
  // Herbívoras
  if (type == "H-DI")   return new AntHDI(x, y, direction, tape_);
  if (type == "H-DDII") return new AntHDDII(x, y, direction, tape_);
  if (type == "H-IDID") return new AntHIDID(x, y, direction, tape_);
  if (type == "H-DIDI") return new AntHDIDI(x, y, direction, tape_);
  if (type == "H-IIII") return new AntHIIII(x, y, direction, tape_);
  if (type == "H-DDDD") return new AntHDDDD(x, y, direction, tape_);
  // Carnívoras
  if (type == "C-IDID") return new AntCIDID(x, y, direction, tape_);
  if (type == "C-DDII") return new AntCDDII(x, y, direction, tape_);
  if (type == "C-DIDI") return new AntCDIDI(x, y, direction, tape_);
  if (type == "C-IIII") return new AntCIIII(x, y, direction, tape_);
  if (type == "C-DDDD") return new AntCDDDD(x, y, direction, tape_);

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
 * @brief Establece la cinta de la simulación según el tipo especificado.
 * @param[in] type: cadena que identifica el tipo de cinta.
 * @param[in] size_x: tamaño en el eje X de la cinta.
 * @param[in] size_y: tamaño en el eje Y de la cinta.
 * @param[in] number_colors: número de colores de la cinta.
 */
void Simulator::setTape(const std::string& type, int size_x, int size_y, int number_colors) {
  // Elimina la cinta actual si existe
  if (tape_) { 
    delete tape_; 
    tape_ = nullptr; 
  }
  
  if (type == "S" || type == "sliding") {
    tape_ = new TapeSliding(size_x, size_y, number_colors);
  } else if (type == "R" || type == "reflective") {
    tape_ = new TapeReflective(size_x, size_y, number_colors);
  } else if (type == "P" || type == "periodic") {
    tape_ = new TapePeriodic(size_x, size_y, number_colors);
  } else {
    throw std::runtime_error("Error: Tipo de cinta '" + type + "' no reconocido.");
  }
}

/**
 * @brief Realizar un paso de la simulación.
 */
void Simulator::step() {
  for (Ant* ant : ants_) {
    if (ant->isAlive()) { 
      ant->move();
    }
  }
  applyInteractions();
  steps_++;
}

/**
 * @brief Detecta hormigas que comparten celda y aplica las reglas de interacción.
 */
void Simulator::applyInteractions() {
  std::map<std::pair<int,int>, std::vector<Ant*>> cell_map;
  for (Ant* ant : ants_) {
    if (ant->isAlive()) {
      cell_map[{ant->getX(), ant->getY()}].push_back(ant);
    }
  }

  for (auto& [position, group] : cell_map) {
    if (group.size() < 2) { continue; }
    // Cada hormiga interactúa con las demás
    for (size_t i = 0; i < group.size(); i++) {
      for (size_t j = 0; j < group.size(); j++) {
        if (i == j) { continue; }
        group[i]->interact(*group[j]);
      }
    }
  }
}

/**
 * @brief Verifica si la simulación ha terminado (todas las hormigas han muerto o abandonado).
 * @return True si la simulación ha terminado, false en caso contrario.
 */
bool Simulator::isFinished() const { 
  return std::all_of(ants_.begin(), ants_.end(), [](Ant* ant) {
    return !ant->isAlive() || ant->isOutOfBounds();
  });
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
  
  // Si todas las hormigas han salido o muerto, mostramos el estado final
  if (isFinished()) {
    clearScreen();
    std::cout << *this;
    std::cout << "\n¡Todas las hormigas han muerto o salido de los límites de la cinta!" << std::endl;
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
 * @brief Guarda el estado actual de la simulación en un fichero.
 * @param[in] filename: nombre del fichero donde se guardará el estado.
 */
void Simulator::saveState(const std::string& filename) const {
  // Vector de información de hormigas
  std::vector<std::tuple<std::string, int, int, int, int>> ants_info;
  
  for (const Ant* ant : ants_) {
    ants_info.emplace_back(
      ant->getType(),
      ant->getX(),
      ant->getY(),
      static_cast<int>(ant->getDirection()),
      ant->getLifeTime()
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
  const std::vector<Ant*>& ants = simulator.getAnts();
  const size_t active_ants = std::count_if(ants.begin(), ants.end(), [](const Ant* ant) {
    return ant->isAlive() && !ant->isOutOfBounds();
  });

  os << "=== Hormiga de Langton Evolucionada ===" << std::endl;
  os << "Paso: " << simulator.getSteps() << std::endl;
  os << "Número de hormigas: " << active_ants << std::endl;

  // Mostrar información de cada hormiga
  for (size_t i = 0; i < ants.size(); i++) {
    const Ant* ant = ants[i];
    os << "  Hormiga " << (i + 1) << " (tipo " << ant->getType() << "): "
       << "posición (" << ant->getX() << ", " << ant->getY() << ")" 
       << ", vida " << ant->getLifeTime();
    
    if (ant->isOutOfBounds()) {
      os << " [FUERA DE LÍMITES]";
    } else if (!ant->isAlive()) {
      os << " [MUERTA]";
    }
    os << std::endl;
  }
  os << std::endl;

  const Tape* tape = simulator.getTape();
  int min_x = 0, min_y = 0;

  // Si es TapeSliding, los índices pueden ser negativos
  const TapeSliding* tape_sliding = dynamic_cast<const TapeSliding*>(tape);
  if (tape_sliding) { 
    min_x = tape_sliding->getMinX();
    min_y = tape_sliding->getMinY();
  }

  // Borde superior
  os << "  +";
  for (int x = 0; x < tape->getSizeX(); x++) {
    os << "-";
  }
  os << "+" << std::endl;

  // Celdas con las hormigas
  for (int y = 0; y < tape->getSizeY(); y++) {
    int log_y = y + min_y;
    os << "  |";
    
    for (int x = 0; x < tape->getSizeX(); x++) {
      int log_x = x + min_x;
      // Verificar si hay alguna hormiga en esta posición
      bool ant_found = false;
      for (size_t i = 0; i < ants.size(); i++) {
        const Ant* ant = ants[i];
        if (ant->isAlive() && !ant->isOutOfBounds() && ant->getX() == log_x && ant->getY() == log_y) {
          os << *ant;
          ant_found = true;
          break;
        }
      }
      
      if (!ant_found) {
        // Mostramos la celda
        tape->printCell(os, log_x, log_y);
      }
    }
    
    os << "|" << std::endl;
  }

  // Borde inferior
  os << "  +";
  for (int x = 0; x < tape->getSizeX(); x++) {
    os << "-";
  }
  os << "+" << std::endl;

  return os;
}

/**
 * @brief Sobrecarga del operador de extracción en flujo (>>) para la clase Simulator.
 * @param[in,out] is: referencia al flujo de entrada (std::cin).
 * @param[in] simulator: referencia al objeto Simulator que se actualizará con el estado leído.
 * @return Referencia al flujo de entrada (std::cin).
 */
std::istream& operator>>(std::istream& is, Simulator& simulator) {
  // Línea 1: tamaño, colores y tipo de cinta
  int size_X, size_Y, num_colors;
  std::string type;
  is >> size_X >> size_Y >> num_colors >> type;

  // Elimina cualquier carácter de nueva línea restante
  is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  simulator.setTape(type, size_X, size_Y, num_colors);

  // Línea 2: Tipo, posición y orientación de cada hormiga
  std::string ants_line;
  std::getline(is, ants_line);
  
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
    
    Direction direction = simulator.parseDirection(dir_symbol);
    
    // Creamos la hormiga del tipo especificado
    Ant* ant = simulator.createAnt(type, x, y, direction);
    if (ant) { simulator.addAnt(ant); }
  }

  // Líneas 3..n: Posición y color de las celdas no blancas
  int x, y, color;
  while (is >> x >> y >> color) {
    if (simulator.getTape()->isValidPosition(x, y)) {
      simulator.getTape()->setCell(x, y, color);
    }
  }

  return is;
}
