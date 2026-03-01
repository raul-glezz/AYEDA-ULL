/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   h_iiii.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Definición de la clase AntHIIII, que representa a las hormigas herbívoras con movimiento IIII.
 */

#include "h_iiii.h"

/**
 * @brief Método que mueve la hormiga H-IIII según las reglas específicas de su tipo.
 */
void AntHIIII::move() {
  if (!tape_->isValidPosition(x_, y_)) { return; }
  eatCell();
  turnLeft();
  changeColor();
  moveForward();
  lifetime_--;
}
