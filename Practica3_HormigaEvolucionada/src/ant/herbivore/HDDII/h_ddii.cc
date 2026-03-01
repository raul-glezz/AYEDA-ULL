/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   h_ddii.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Definición de la clase AntHDDII, que representa a las hormigas herbívoras con movimiento DDII.
 */
#include "h_ddii.h"

/**
 * @brief Método que mueve la hormiga H-DDII según las reglas específicas de su tipo.
 */
void AntHDDII::move() {
  if (!tape_->isValidPosition(x_, y_)) { return; }
  eatCell();
  int color = (tape_->getCell(x_, y_) % 4);
  switch (color) {
    case 0: 
    case 1: 
      turnRight();
      break;
    case 2:
    case 3:
      turnLeft();
      break;
    default: 
      break;
  }
  changeColor();
  moveForward();
  lifetime_--;
}
