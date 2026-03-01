/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 3: Hormiga de Langton Evolucionada
 *
 * @file   sv_exception.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Declaración de la clase SVException, que representa una excepción lanzada por SlidingVector.
 */

#pragma once

#include <stdexcept>

class SVException : public std::out_of_range {
 public:
  //------CONSTRUCTOR------
  explicit SVException(int);
  
  //---------------MÉTODO---------------
  /// Método para obtener el índice que causó la excepción
  int getIndex() const { return index_; }

 private:
  /// index_: índice que causó la excepción
  int index_;
};