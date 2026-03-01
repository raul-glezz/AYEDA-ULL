/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   h_di.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Declaración de la clase AntHDI, que representa a las hormigas herbívoras con movimiento DI.
 */

#pragma once

#include "../ant_herbivore.h"

class AntHDI : public AntHerbivore {
 public:
 //---------------------------CONSTRUCTOR---------------------------
  AntHDI(int x, int y, Direction direction, Tape* tape) :
    AntHerbivore(x, y, direction, tape, "H-DI", "\033[31m", 20) {}
  
  //------MÉTODO------
  /// Método que mueve la hormiga
  void move() override;
};
