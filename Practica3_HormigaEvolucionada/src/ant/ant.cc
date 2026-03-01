/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 3: Hormiga de Langton Evolucionada
 *
 * @file   ant.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Definición de la clase base Ant, que representa una hormiga genérica.
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
 * @brief Mueve la hormiga una celda hacia adelante en la dirección actual aplicando la condición de frontera.
 */
void Ant::moveForward() {
  int new_x = x_, new_y = y_;
  switch (direction_) {
    case LEFT: 
      new_x--;
      break;
    case RIGHT:
      new_x++;
      break;
    case UP:
      new_y--;
      break;
    case DOWN:
      new_y++;
      break;
  }

  int direction = static_cast<int>(direction_);
  tape_->applyBorder(new_x, new_y, direction);
  direction_ = static_cast<Direction>(direction);
  x_ = new_x;
  y_ = new_y;
}

/**
 * @brief Mueve la hormiga una celda en diagonal (sentido horario).
 */
void Ant::moveDiagonal() {
  int new_x = x_, new_y = y_;
  switch (direction_) {
    // LEFT -> NW
    case LEFT:
      new_x--;
      new_y--;
      break;
    // RIGHT -> SE
    case RIGHT:
      new_x++;
      new_y++;
      break;
    // UP -> NE
    case UP:
      new_x++; 
      new_y--; 
      break;
    // DOWN -> SW
    case DOWN:
      new_x--;
      new_y++;
      break;
  }

  int direction = static_cast<int>(direction_);
  tape_->applyBorder(new_x, new_y, direction);
  direction_ = static_cast<Direction>(direction);
  x_ = new_x;
  y_ = new_y;
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
 * @brief Establece el tiempo de vida restante de la hormiga.
 * @param[in] lifetime: Nuevo tiempo de vida.
 */
void Ant::setLifeTime(int lifetime) {
  lifetime_ = lifetime;
  if (lifetime_ < 0) { lifetime_ = 0; }
}

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
