/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   idid.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   11/02/2026
 * @brief  Definición de la clase AntIDID, que representa la hormiga de Langton con la secuencia IDID.
 */

#include "idid.h"

/**
 * @brief Mueve la hormiga tipo IDID.
 * Color 0 -> Izquierda, Color 1 -> Derecha
 * Color 2 -> Izquierda, Color 3 -> Derecha
 */
void AntIDID::move() {
  if (!tape_->isValidPosition(x_, y_)) { return; }

  int current_color = tape_->getCell(x_, y_);

  // Aplicar regla según la posición en la cadena "IDID"
  switch (current_color) {
    case 0:  // 'I'
      turnLeft();
      break;
    case 1:  // 'D'
      turnRight();
      break;
    case 2:  // 'I'
      turnLeft();
      break;
    case 3:  // 'D'
      turnRight();
      break;
    default:
      break;
  }

  // Cambiamos el color de la celda y avanzamos
  changeColor();
  moveForward();
}