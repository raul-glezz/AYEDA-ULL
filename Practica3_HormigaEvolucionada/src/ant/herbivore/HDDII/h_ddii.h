/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   h_ddii.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Declaración de la clase AntHDDII, que representa a las hormigas herbívoras con movimiento DDII.
 */

#pragma once

#include "../ant_herbivore.h"

class AntHDDII : public AntHerbivore {
 public:
 //---------------------------CONSTRUCTOR---------------------------
  AntHDDII(int x, int y, Direction direction, Tape* tape) :
    AntHerbivore(x, y, direction, tape, "H-DDII", "\033[32m", 20) {}
  
  //------MÉTODO------
  /// Método que mueve la hormiga
  void move() override;
};
