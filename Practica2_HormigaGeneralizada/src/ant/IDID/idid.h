/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   idid.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   11/02/2026
 * @brief  Declaración de la clase AntIDID, que representa la hormiga de Langton con 4 colores (IDID).
 */

#pragma once

#include "../ant.h"

class AntIDID : public Ant {
 public:
  //---------------------CONSTRUCTOR---------------------
  AntIDID(int x, int y, Direction direction, Tape* tape) : 
    Ant(x, y, direction, tape, "IDID", "\033[34m") {}
  
  //------MÉTODO------
  /// Método que mueve la hormiga según las reglas del tipo DI
  void move() override;
};