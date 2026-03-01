/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 3: Hormiga de Langton Evolucionada
 *
 * @file   ant_herbivore.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Definición de la clase AntHerbivore, que representa una hormiga herbívora.
 */

#include "ant_herbivore.h"

/**
 * @brief Gana lifetime proporcional al color de la celda actual.
 */
void AntHerbivore::eatCell() {
  if (!tape_->isValidPosition(x_, y_)) { return; }
  int color_value = tape_->getCell(x_, y_);
  lifetime_ += color_value;
}