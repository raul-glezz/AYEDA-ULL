/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   c_di.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Declaración de la clase AntCDI, que representa a las hormigas carnívoras con movimiento DI.
 */

#pragma once

#include "../ant_carnivore.h"

class AntCDI : public AntCarnivore {
 public:
  //-----------------------------CONSTRUCTOR-----------------------------
  AntCDI(int x, int y, Direction direction, Tape* tape) :
    AntCarnivore(x, y, direction, tape, "C-DI", "\033[1;35m", 15, 45) {}
  
  //------MÉTODO------
  /// Método que mueve la hormiga
  void move() override;
};
