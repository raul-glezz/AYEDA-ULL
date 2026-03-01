/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   c_didi.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Declaración de la clase AntCDIDI, que representa a las hormigas carnívoras con movimiento DIDI.
 */

#pragma once

#include "../ant_carnivore.h"

class AntCDIDI : public AntCarnivore {
 public:
  //-----------------------------CONSTRUCTOR-----------------------------
  AntCDIDI(int x, int y, Direction direction, Tape* tape) :
    AntCarnivore(x, y, direction, tape, "C-DIDI", "\033[1;36m", 15, 35) {}
  
  //------MÉTODO------
  /// Método que mueve la hormiga
  void move() override;
};
