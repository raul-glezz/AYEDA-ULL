/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   di.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   11/02/2026
 * @brief  Definición de la clase AntDI, que representa la hormiga de Langton clásica con 2 colores (DI).
 */

#include "di.h"

/**
 * @brief Mueve la hormiga tipo DI según las reglas clásicas.
 * Color 0 (Blanco) -> Gira Derecha
 * Color 1 (Negro) -> Gira Izquierda
 */
void AntDI::move() {
  if (!tape_->isValidPosition(x_, y_)) { return; }
  
  int current_color = tape_->getCell(x_, y_);
  
  // Giramos según el color actual
  if (current_color == 0) { turnRight(); } 
  else { turnLeft(); }

  // Cambiamos el color de la celda y avanzamos
  changeColor();
  moveForward();
}