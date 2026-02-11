/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   dddd.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   11/02/2026
 * @brief  Declaración de la clase AntDDDD, que representa la hormiga de Langton con 4 colores (DDDD).
 */

#pragma once

#include "../ant.h"

class AntDDDD : public Ant {
 public:
  //---------------------CONSTRUCTOR---------------------
  AntDDDD(int x, int y, Direction direction, Tape* tape) : 
    Ant(x, y, direction, tape, "DDDD", "\033[35m") {}
  
  //------MÉTODO------
  /// Método que mueve la hormiga según las reglas del tipo DI
  void move() override;
};