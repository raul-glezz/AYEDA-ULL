/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   di.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   11/02/2026
 * @brief  Declaración de la clase AntDI, que representa la hormiga de Langton clásica con 2 colores (DI).
 */

#pragma once

#include "../ant.h"

class AntDI : public Ant {
 public:
  //---------------------CONSTRUCTOR---------------------
  AntDI(int x, int y, Direction direction, Tape* tape) : 
    Ant(x, y, direction, tape, "DI", "\033[31m") {}
  
  //------MÉTODO------
  /// Método que mueve la hormiga según las reglas del tipo DI
  void move() override;
};