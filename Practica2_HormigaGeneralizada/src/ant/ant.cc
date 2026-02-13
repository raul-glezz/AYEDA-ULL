/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   ant.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   11/02/2026
 * @brief  Definición de la clase base Ant, que representa la hormiga en la simulación de Langton.
 */

#include "ant.h"

#define ANSI_RESET "\033[0m"

/**
 * @brief Gira la hormiga 90 grados a la izquierda.
 */
void Ant::turnLeft() {
  switch (direction_) {
    case LEFT:
      direction_ = DOWN;
      break;
    case RIGHT:
      direction_ = UP;
      break;
    case UP:
      direction_ = LEFT;
      break;
    case DOWN:
      direction_ = RIGHT;
      break;
  }
}

/**
 * @brief Gira la hormiga 90 grados a la derecha.
 */
void Ant::turnRight() {
  switch (direction_) {
    case LEFT:
      direction_ = UP;
      break;
    case RIGHT:
      direction_ = DOWN;
      break;
    case UP:
      direction_ = RIGHT;
      break;
    case DOWN:
      direction_ = LEFT;
      break;
  }
}

/**
 * @brief Mueve la hormiga una celda hacia adelante en la dirección actual.
 */
void Ant::moveForward() {
  switch (direction_) {
    case LEFT:
      x_--;
      break;
    case RIGHT:
      x_++;
      break;
    case UP:
      y_--;
      break;
    case DOWN:
      y_++;
      break;
  }
}

/**
 * @brief Cambia el color de la celda actual con comportamiento cíclico.
 */
void Ant::changeColor() {
  if (!tape_->isValidPosition(x_, y_)) return;
  
  int current_color = tape_->getCell(x_, y_);
  int number_colors = tape_->getNumberColors();
  int next_color = (current_color + 1) % number_colors;
  
  tape_->setCell(x_, y_, next_color);
}

/**
 * @brief Verifica si la hormiga está fuera de los límites de la cinta.
 * @return True si la hormiga está fuera de los límites, false en caso contrario.
 */
bool Ant::isOutOfBounds() const { return !tape_->isValidPosition(x_, y_); }

/**
 * @brief Sobrecarga del operador de inserción en flujo (<<) para la clase Ant.
 * @param[in] os: Referencia al flujo de salida estándar (std::cout).
 * @param[in] ant: Referencia constante a la instancia de la clase Ant.
 * @return Referencia al flujo de salida estándar (std::cout).
 */
std::ostream& operator<<(std::ostream& os, const Ant& ant) {
  // Imprimimos el color de la hormiga usando su código ANSI
  os << ant.getColor();
  
  switch (ant.getDirection()) {
    case LEFT:
      os << "<";
      break;
    case RIGHT:
      os << ">";
      break;
    case UP:
      os << "^";
      break;
    case DOWN:
      os << "v";
      break;
  }
  
  // Reseteamos el color para no afectar a la impresión de otros elementos
  os << ANSI_RESET;
  
  return os;
}