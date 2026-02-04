/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 1: La Hormiga de Langton

 * @file   simulator.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   30/01/2026
 * @brief  Definición de la clase Simulator, que gestiona la simulación de la Hormiga de Langton.
 */

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <thread>
#include <chrono>

#include "simulator.h"

/**
 * @brief Constructor parametrizado de la simulación.
 * @param[in] size_X: tamaño en X de la cinta.
 * @param[in] size_Y: tamaño en Y de la cinta.
 * @param[in] ant_X: posición inicial X de la hormiga.
 * @param[in] ant_Y: posición inicial Y de la hormiga.
 * @param[in] ant_direction: dirección inicial de la hormiga.
 */
Simulator::Simulator(int size_X, int size_Y, int ant_X, int ant_Y, Direction ant_direction) {
  steps_ = 0;
  tape_ = new Tape(size_X, size_Y);
  ant_ = new Ant(ant_X, ant_Y, ant_direction, tape_);
}

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
  file >> (*this);
  file.close();
}

/**
 * @brief Destructor de la simulación.
 */
Simulator::~Simulator() {
  delete ant_;
  delete tape_;
}

/**
 * @brief Realizar un paso de la simulación.
 */
void Simulator::step() {
  if (!isFinished()) {
    ant_->move();
    steps_++;
  }
}

/**
 * @brief Ejecutar la simulación hasta que la hormiga salga de los límites de la cinta.
 */
void Simulator::run() {
  std::string input;
  
  // Si no ha salido de los límites, continuamos la simulación
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
  
  // Si la hormiga ha salido de los límites, mostramos el estado final
  if (isFinished()) {
    clearScreen();
    std::cout << *this;
    std::cout << "\n¡La hormiga ha salido de los límites de la cinta!" << std::endl;
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
 * @return true si la hormiga ha salido de los límites de la cinta, false en caso contrario.
 */
bool Simulator::isFinished() const {
  return ant_->isOutOfBounds();
}

/**
 * @brief Guarda el estado actual de la simulación en un fichero.
 * @param[in] filename: nombre del fichero donde se guardará el estado.
 */
void Simulator::saveState(const std::string& filename) const {
  tape_->saveToFile(filename, ant_->getX(), ant_->getY(), static_cast<int>(ant_->getDirection()));
}

/**
 * @brief Limpia la pantalla de la consola.
 */
void Simulator::clearScreen() const { system("clear"); }

/**
 * @brief Sobrecarga del operador de extracción en flujo (>>) para la clase Simulator.
 * @param[in,out] is: referencia al flujo de entrada (std::cin).
 * @param[out] simulator: referencia al objeto Simulator donde se cargará el estado.
 * @return Referencia al flujo de entrada (std::cin).
 */
std::ifstream& operator>>(std::ifstream& is, Simulator& simulator) {
  int size_X, size_Y, ant_X, ant_Y, ant_direction;
  
  // Leemos la primera línea: Tamaño de la cinta
  is >> size_X >> size_Y;
  
  // Leemos la segunda línea: Posición y orientación de la hormiga
  is >> ant_X >> ant_Y >> ant_direction;
  
  // Creamos la cinta
  Tape* tape = new Tape(size_X, size_Y);
  
  // Leemos las líneas 3..n: Posiciones de celdas negras
  int x, y;
  while (is >> x >> y) {
    if (tape->isValidPosition(x, y)) {
      tape->setCell(x, y, 1);
    }
  }
  
  // Creamos la hormiga
  Ant ant(ant_X, ant_Y, static_cast<Direction>(ant_direction), tape);

  // Asignamos la cinta y la hormiga al simulador
  simulator.setTape(tape);
  simulator.setAnt(new Ant(ant));
  
  return is;
}

/**
 * @brief Sobrecarga del operador de inserción en flujo (<<) para la clase Simulator.
 * @param[in,out] os: referencia al flujo de salida (std::cout).
 * @param[in] simulator: referencia al objeto Simulator cuyo estado se mostrará.
 * @return Referencia al flujo de salida (std::cout).
 */
std::ostream& operator<<(std::ostream& os, const Simulator& simulator) {
  // Crear una copia visual de la cinta con la hormiga
  os << "=== Hormiga de Langton ===" << std::endl;
  os << "Paso: " << simulator.getSteps() << std::endl;
  os << "Hormiga en posición (" << simulator.getAnt()->getX() << ", " << 
                                   simulator.getAnt()->getY() << ")" << std::endl << std::endl;
  
  // Mostrar la cinta
  int antX = simulator.getAnt()->getX();
  int antY = simulator.getAnt()->getY();
  
  // Borde superior
  os << "+";
  for (int x = 0; x < simulator.getTape()->getSizeX(); x++) {
    os << "-";
  }
  os << "+" << std::endl;
  
  // Celdas con la hormiga
  for (int y = 0; y < simulator.getTape()->getSizeY(); y++) {
    os << "|";
    for (int x = 0; x < simulator.getTape()->getSizeX(); x++) {
      if (x == antX && y == antY) {
        // Mostrar la hormiga
        os << *simulator.getAnt();
      } else {
        // Mostrar la celda
        simulator.getTape()->printCell(os, x, y);
      }
    }
    os << "|" << std::endl;
  }
  
  // Borde inferior
  os << "+";
  for (int x = 0; x < simulator.getTape()->getSizeX(); x++) {
    os << "-";
  }
  os << "+" << std::endl;

  return os;
}
