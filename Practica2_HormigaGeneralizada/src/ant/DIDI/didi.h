/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   didi.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   11/02/2026
 * @brief  Declaración de la clase AntDIDI, que representa la hormiga de Langton con 4 colores (DIDI).
 */

#pragma once

#include "../ant.h"

class AntDIDI : public Ant {
 public:
  //---------------------CONSTRUCTOR---------------------
  AntDIDI(int x, int y, Direction direction, Tape* tape) : 
    Ant(x, y, direction, tape, "DIDI", "\033[36m") {}
  
  //------MÉTODO------
  /// Método que mueve la hormiga según las reglas del tipo DI
  void move() override;
};