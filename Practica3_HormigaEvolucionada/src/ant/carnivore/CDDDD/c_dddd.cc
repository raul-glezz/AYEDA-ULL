/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   c_dddd.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Definición de la clase AntCDDDD, que representa a las hormigas carnívoras con movimiento DDDD.
 */

#include "c_dddd.h"

/**
 * @brief Método que mueve la hormiga C-DDDD según las reglas específicas de su tipo.
 */
void AntCDDDD::move() {
  if (!tape_->isValidPosition(x_, y_)) { return; }
  turnRight();
  changeColor();
  moveDiagonal();
  lifetime_--;
}
