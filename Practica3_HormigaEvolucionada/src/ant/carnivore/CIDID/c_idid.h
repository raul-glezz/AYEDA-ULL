/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   c_idid.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Declaración de la clase AntCIDID, que representa a las hormigas carnívoras con movimiento IDID.
 */

#pragma once

#include "../ant_carnivore.h"

class AntCIDID : public AntCarnivore {
 public:
  //-----------------------------CONSTRUCTOR-----------------------------
  AntCIDID(int x, int y, Direction direction, Tape* tape) :
    AntCarnivore(x, y, direction, tape, "C-IDID", "\033[1;34m", 15, 30) {}
  
  //------MÉTODO------
  /// Método que mueve la hormiga
  void move() override;
};
