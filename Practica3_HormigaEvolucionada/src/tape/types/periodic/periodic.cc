/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 3: Hormiga de Langton Evolucionada
 *
 * @file   periodic.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Definición de la clase TapePeriodic, que implementa la frontera periódica (wrap-around) para la cinta de la Hormiga de Langton.
 */

#include "periodic.h"

/**
 * @brief Método para aplicar la condición de frontera periódica (wrap-around).
 * @param[in,out] new_x: coordenada X a ajustar.
 * @param[in,out] new_y: coordenada Y a ajustar.
 * @return True siempre, ya que la posición se ajusta para ser válida.
 */
bool TapePeriodic::applyBorder(int& new_x, int& new_y, int&) {
  new_x = ((new_x % size_X_) + size_X_) % size_X_;
  new_y = ((new_y % size_Y_) + size_Y_) % size_Y_;
  return true;
}