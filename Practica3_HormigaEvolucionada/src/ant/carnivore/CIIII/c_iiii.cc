/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   c_iiii.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Definición de la clase AntCIIII, que representa a las hormigas carnívoras con movimiento IIII.
 */

#include "c_iiii.h"

/**
 * @brief Método que mueve la hormiga C-IIII según las reglas específicas de su tipo.
 */
void AntCIIII::move() {
  if (!tape_->isValidPosition(x_, y_)) { return; }
  turnLeft();
  changeColor();
  moveDiagonal();
  lifetime_--;
}
