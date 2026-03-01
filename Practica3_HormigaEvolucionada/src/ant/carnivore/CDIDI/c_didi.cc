/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   c_didi.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Definición de la clase AntCDIDI, que representa a las hormigas carnívoras con movimiento DIDI.
 */

#include "c_didi.h"

/**
 * @brief Método que mueve la hormiga C-DIDI según las reglas específicas de su tipo.
 */
void AntCDIDI::move() {
  if (!tape_->isValidPosition(x_, y_)) { return; }
  int color = (tape_->getCell(x_, y_) % 4);
  switch (color) {
    case 0: 
    case 2: 
      turnRight();
      break;
    case 1: 
    case 3: 
      turnLeft();
      break;
    default: 
      break;
  }
  changeColor();
  moveDiagonal();
  lifetime_--;
}
