/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 3: Hormiga de Langton Evolucionada
 *
 * @file   reflective.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Declaración de la clase TapeReflective, que implementa la frontera reflectora para la cinta de la Hormiga de Langton.
 */

#pragma once

#include "../../tape.h"

class TapeReflective : public Tape {
 public:
  //-----------------------CONSTRUCTOR-----------------------
  TapeReflective(int size_X, int size_Y, int number_colors) : 
    Tape(size_X, size_Y, number_colors) {}

  //------------------MÉTODO------------------
  /// Método para aplicar la condición de frontera reflectora
  bool applyBorder(int&, int&, int&) override;
};