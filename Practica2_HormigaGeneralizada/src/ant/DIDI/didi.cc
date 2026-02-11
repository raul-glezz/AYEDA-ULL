/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   didi.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   11/02/2026
 * @brief  Definición de la clase AntDIDI, que representa la hormiga de Langton con la secuencia DIDI.
 */

#include "didi.h"

/**
 * @brief Mueve la hormiga tipo DIDI.
 * Color 0 -> Derecha, Color 1 -> Izquierda
 * Color 2 -> Derecha, Color 3 -> Izquierda
 */
void AntDIDI::move() {
  if (!tape_->isValidPosition(x_, y_)) { return; }

  int current_color = tape_->getCell(x_, y_);

  // Aplicar regla según la posición en la cadena "DIDI"
  switch (current_color) {
    case 0:  // 'D'
      turnRight();
      break;
    case 1:  // 'I'
      turnLeft();
      break;
    case 2:  // 'D'
      turnRight();
      break;
    case 3:  // 'I'
      turnLeft();
      break;
    default:
      break;
  }

  // Cambiamos el color de la celda y avanzamos
  changeColor();
  moveForward();
}