/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   h_idid.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Definición de la clase AntHIDID, que representa a las hormigas herbívoras con movimiento IDID.
 */

#include "h_idid.h"

/**
 * @brief Método que mueve la hormiga H-IDID según las reglas específicas de su tipo.
 */
void AntHIDID::move() {
  if (!tape_->isValidPosition(x_, y_)) { return; }
  eatCell();
  int color = (tape_->getCell(x_, y_) % 4);
  switch (color) {
    case 0:
    case 2:
      turnLeft();
      break;
    case 1: 
    case 3:
      turnRight();
      break;
    default: 
      break;
  }
  changeColor();
  moveForward();
  lifetime_--;
}
