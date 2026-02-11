/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   iiii.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   11/02/2026
 * @brief  Declaración de la clase AntIIII, que representa la hormiga de Langton con 4 colores (IIII).
 */

#pragma once

#include "../ant.h"

class AntIIII : public Ant {
 public:
  //---------------------CONSTRUCTOR---------------------
  AntIIII(int x, int y, Direction direction, Tape* tape) : 
    Ant(x, y, direction, tape, "IIII", "\033[33m") {}
  
  //------MÉTODO------
  /// Método que mueve la hormiga según las reglas del tipo DI
  void move() override;
};