/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   dddd.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   11/02/2026
 * @brief  Definición de la clase AntDDDD, que representa la hormiga de Langton con la secuencia DDDD.
 */

#include "dddd.h"

/**
 * @brief Mueve la hormiga tipo DDDD.
 * Todos los colores -> Gira Derecha
 */
void AntDDDD::move() {
  if (!tape_->isValidPosition(x_, y_)) { return; }
  
  // Siempre gira a la derecha
  turnRight();
  
  // Cambiamos el color de la celda y avanzamos
  changeColor();
  moveForward();
}