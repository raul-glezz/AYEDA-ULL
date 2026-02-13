/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   simulator.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   11/02/2026
 * @brief  Declaración de la clase Simulator, que gestiona la simulación con múltiples hormigas.
 */

#pragma once

#include <string>
#include <vector>
#include <memory>

#include "../tape/tape.h"
#include "../ant/ant.h"

class Simulator {
 public:
  //--------CONSTRUCTOR--------
  Simulator(const std::string&);
  
  //-DESTRUCTOR-
  ~Simulator();

  //-------------------------MÉTODOS-------------------------
  /// Método para obtener el número de pasos realizados en la simulación
  int getSteps() const { return steps_; }
  /// Método para obtener la cinta de la simulación
  Tape* getTape() const { return tape_; }
  /// Método para obtener el vector de hormigas
  const std::vector<Ant*>& getAnts() const { return ants_; }

  /// Método para establecer la cinta de la simulación
  void setTape(Tape* tape) { tape_ = tape; }
  /// Método para agregar una hormiga a la simulación
  void addAnt(Ant* ant) { ants_.push_back(ant); }
  
  /// Método que simula un paso de todas las hormigas
  void step();
  /// Método que ejecuta la simulación completa
  void run();
  /// Método que indica si la simulación ha terminado
  bool isFinished() const;
  /// Método que guarda el estado actual de la simulación en un fichero
  void saveState(const std::string&) const;

  /// Método que crea una hormiga del tipo especificado
  Ant* createAnt(const std::string&, int, int, Direction);
  /// Método auxiliar para parsear la dirección desde un símbolo
  Direction parseDirection(const std::string&) const;

 private:
  //-------ATRIBUTOS-------
  /// tape_: puntero a la cinta de la simulación
  Tape* tape_;
  /// ants_: vector de punteros a las hormigas de la simulación
  std::vector<Ant*> ants_;
  /// steps_: número de pasos realizados en la simulación
  int steps_;

  //----MÉTODO PRIVADOS----
  /// Método que limpia la pantalla de la consola
  void clearScreen() const;
};
/// Sobrecarga del operador de inserción en flujo (<<) para la clase Simulator
std::ostream& operator<<(std::ostream&, const Simulator&);
/// Sobrecarga del operador de extracción en flujo (>>) para la clase Simulator
std::istream& operator>>(std::istream&, Simulator&);