/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   c_ddii.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Declaración de la clase AntCDDII, que representa a las hormigas carnívoras con movimiento DDII.
 */

#pragma once

#include "../ant_carnivore.h"

class AntCDDII : public AntCarnivore {
 public:
  //-----------------------------CONSTRUCTOR-----------------------------
  AntCDDII(int x, int y, Direction direction, Tape* tape) :
    AntCarnivore(x, y, direction, tape, "C-DDII", "\033[1;32m", 15, 40) {}
  
  //------MÉTODO------
  /// Método que mueve la hormiga
  void move() override;
};
