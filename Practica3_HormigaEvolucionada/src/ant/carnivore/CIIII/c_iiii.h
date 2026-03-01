/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   c_iiii.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Declaración de la clase AntCIIII, que representa a las hormigas carnívoras con movimiento IIII.
 */

#pragma once

#include "../ant_carnivore.h"

class AntCIIII : public AntCarnivore {
 public:
  //-----------------------------CONSTRUCTOR-----------------------------
  AntCIIII(int x, int y, Direction direction, Tape* tape) :
    AntCarnivore(x, y, direction, tape, "C-IIII", "\033[1;33m", 15, 50) {}
  
  //------MÉTODO------
  /// Método que mueve la hormiga
  void move() override;
};
