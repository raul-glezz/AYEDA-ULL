/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   iiii.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   11/02/2026
 * @brief  Definición de la clase AntIIII, que representa la hormiga de Langton con la secuencia IIII.
 */

#include "iiii.h"

/**
 * @brief Mueve la hormiga tipo IIII.
 * Todos los colores -> Gira Izquierda
 */
void AntIIII::move() {
  if (!tape_->isValidPosition(x_, y_)) { return; }

  // Siempre gira a la izquierda
  turnLeft();

  // Cambiamos el color de la celda y avanzamos
  changeColor();
  moveForward();
}