/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   h_dddd.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Definición de la clase AntHDDDD, que representa a las hormigas herbívoras con movimiento DDDD.
 */

#include "h_dddd.h"

/**
 * @brief Método que mueve la hormiga H-DDDD según las reglas específicas de su tipo.
 */
void AntHDDDD::move() {
  if (!tape_->isValidPosition(x_, y_)) { return; }
  eatCell();
  turnRight();
  changeColor();
  moveForward();
  lifetime_--;
}
