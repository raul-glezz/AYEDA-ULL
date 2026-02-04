/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 1: La Hormiga de Langton

 * @file   simulator.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   30/01/2026
 * @brief  Declaración de la clase Simulator, que gestiona la simulación de la Hormiga de Langton.
 */

#pragma once

#include <string>

#include "../tape/tape.h"
#include "../ant/ant.h"

class Simulator {
 public:
  //-------------CONSTRUCTORES-------------
  Simulator(int, int, int, int, Direction);
  Simulator(const std::string&);
  
  //-DESTRUCTOR-
  ~Simulator();

  //---------------MÉTODOS---------------
  /// Método para obtener el número de pasos realizados en la simulación
  int getSteps() const { return steps_; }
  /// Método para obtener la cinta de la simulación
  Tape* getTape() const { return tape_; }
  /// Método para obtener la hormiga de la simulación
  Ant* getAnt() const { return ant_; }
  
  /// Método para establecer la cinta de la simulación
  void setTape(Tape* tape) { tape_ = tape; }
  /// Método para establecer la hormiga de la simulación
  void setAnt(Ant* ant) { ant_ = ant; }
  
  /// Método que simula un paso de la hormiga
  void step();
  /// Método que ejecuta la simulación completa
  void run();
  /// Método que indica si la simulación ha terminado
  bool isFinished() const;
  /// Método que guarda el estado actual de la simulación en un fichero
  void saveState(const std::string&) const;

 private:
  //-ATRIBUTOS-
  /// tape_: puntero a la cinta de la simulación
  Tape* tape_;
  /// ant_: puntero a la hormiga de la simulación
  Ant* ant_;
  /// steps_: número de pasos realizados en la simulación
  int steps_;

  //--------MÉTODO--------
  /// Método que limpia la pantalla de la consola
  void clearScreen() const;
};

/// Sobrecarga del operador de inserción en flujo (<<) para la clase Simulator
std::ostream& operator<<(std::ostream&, const Simulator&);
/// Sobrecarga del operador de extracción en flujo (>>) para la clase Simulator
std::ifstream& operator>>(std::ifstream&, Simulator&);
