/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 3: Hormiga de Langton Evolucionada
 *
 * @file   sv_exception.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Definición de la clase SVException, que representa una excepción lanzada por SlidingVector.
 */

#include "sv_exception.h"

SVException::SVException(int index) : 
  std::out_of_range("SVException: El índice " + std::to_string(index) +" está fuera de rango"),
  index_(index) {}