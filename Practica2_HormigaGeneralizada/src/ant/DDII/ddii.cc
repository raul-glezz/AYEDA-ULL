/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   ddii.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   11/02/2026
 * @brief  Definición de la clase AntDDII, que representa la hormiga de Langton con la secuencia DDII.
 */

#include "ddii.h"

/**
 * @brief Mueve la hormiga tipo DDII.
 * Color 0 -> Derecha, Color 1 -> Derecha
 * Color 2 -> Izquierda, Color 3 -> Izquierda
 */
void AntDDII::move() {
  if (!tape_->isValidPosition(x_, y_)) { return; }

  int current_color = tape_->getCell(x_, y_);

  // Aplicar regla según la posición en la cadena "DDII"
  switch (current_color) {
    case 0:  // Primera 'D'
    case 1:  // Segunda 'D'
      turnRight();
      break;
    case 2:  // Primera 'I'
    case 3:  // Segunda 'I'
      turnLeft();
      break;
    default:
      break;
  }

  // Cambiamos el color de la celda y avanzamos
  changeColor();
  moveForward();
}
