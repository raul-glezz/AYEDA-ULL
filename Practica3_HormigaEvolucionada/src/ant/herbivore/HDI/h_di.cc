/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   h_di.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Definición de la clase AntHDI, que representa a las hormigas herbívoras con movimiento DI.
 */
#include "h_di.h"

/**
 * @brief Método que mueve la hormiga H-DI según las reglas específicas de su tipo.
 */
void AntHDI::move() {
  if (!tape_->isValidPosition(x_, y_)) { return; }
  eatCell();
  int color = tape_->getCell(x_, y_);
  (color == 0) ? turnRight() : turnLeft(); 
  changeColor();
  moveForward();
  lifetime_--;
}
