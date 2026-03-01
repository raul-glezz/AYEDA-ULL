/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 3: Hormiga de Langton Evolucionada
 *
 * @file   reflective.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Definición de la clase TapeReflective, que implementa la frontera reflectora para la cinta de la Hormiga de Langton.
 */

#include "reflective.h"

static constexpr int DIRECTION_LEFT  = 0;
static constexpr int DIRECTION_RIGHT = 1;
static constexpr int DIRECTION_UP    = 2;
static constexpr int DIRECTION_DOWN  = 3;

/**
 * @brief Método para aplicar la condición de frontera reflectora.
 * @param[in,out] new_x: coordenada X a ajustar.
 * @param[in,out] new_y: coordenada Y a ajustar.
 * @param[in,out] direction: dirección actual de la hormiga, que se ajustará para reflejar el movimiento.
 * @return True siempre, ya que la posición se ajusta para ser válida.
 */
bool TapeReflective::applyBorder(int& new_x, int& new_y, int& direction) {
  // Si aún está dentro, no hacemos nada
  if (isValidPosition(new_x, new_y)) { return true; }

  // Revertimos el movimiento si la hormiga queda en la celda del borde
  if (new_x < 0) {
    new_x = 0;
    direction = DIRECTION_RIGHT;
  } else if (new_x >= size_X_) {
    new_x = size_X_ - 1;
    direction = DIRECTION_LEFT;
  }
  if (new_y < 0) {
    new_y = 0;
    direction = DIRECTION_DOWN; 
    new_x = 0;
    direction = DIRECTION_RIGHT;
  } else if (new_y >= size_Y_) {
    new_y = size_Y_ - 1;
    direction = DIRECTION_UP;
  }

  return true;
}