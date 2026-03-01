/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   c_dddd.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Declaración de la clase AntCDDDD, que representa a las hormigas carnívoras con movimiento DDDD.
 */

#pragma once

#include "../ant_carnivore.h"

class AntCDDDD : public AntCarnivore {
 public:
  //-----------------------------CONSTRUCTOR-----------------------------
  AntCDDDD(int x, int y, Direction direction, Tape* tape) : 
    AntCarnivore(x, y, direction, tape, "C-DDDD", "\033[1;35m", 15, 50) {}
  
  //------MÉTODO------
  /// Método que mueve la hormiga
  void move() override;
};
