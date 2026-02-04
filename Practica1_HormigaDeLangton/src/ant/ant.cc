/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 1: La Hormiga de Langton

 * @file   ant.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   30/01/2026
 * @brief  Definición de la clase Ant, que representa la hormiga en la simulación de Langton.
 */

#include "ant.h"

/**
 * @brief Mueve la hormiga según las reglas de Langton.
 */
void Ant::move() {
  // Verificamos si la posición actual es válida
  if (!tape_->isValidPosition(x_, y_)) { return; }
  
  // Obtener el color de la celda actual y aplicar las reglas correspondientes
  switch (tape_->getCell(x_, y_)) {
    // Si la celda es blanca (0), cambiar a negra (1) y girar a la izquierda
    case 0:
      tape_->setCell(x_, y_, 1);
      turnLeft();
      break;
    // Si la celda es negra (1), cambiar a blanca (0) y girar a la derecha
    case 1:
      tape_->setCell(x_, y_, 0);
      turnRight();
      break;
    // Caso por defecto, no hacer nada
    default:
      break;
  }
  moveForward();
}

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
 * @brief Verifica si la hormiga está fuera de los límites de la cinta.
 * @return True si la hormiga está fuera de los límites, false en caso contrario.
 */
bool Ant::isOutOfBounds() const { return !tape_->isValidPosition(x_, y_); }

/**
 * @brief Sobrecarga del operador de inserción en flujo (<<) para la clase Ant.
 * @param os Referencia al flujo de salida estándar (std::cout).
 * @param ant Referencia constante a la instancia de la clase Ant.
 * @return Referencia al flujo de salida estándar (std::cout).
 */
std::ostream& operator<<(std::ostream& os, const Ant& ant) {
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
  
  return os;
}
