/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   ant_herbivore.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   11/02/2026
 * @brief  Declaración de la clase AntHerbivore, que representa a las hormigas herbívoras.
 */

#pragma once

#include "../ant.h"

class AntHerbivore : public Ant {
 public:
 //-----------------------------------------------------------CONSTRUCTOR-----------------------------------------------------------
  AntHerbivore(int x, int y, Direction direction, Tape* tape, const std::string& type, const std::string& ansi_color, int lifetime) : 
    Ant(x, y, direction, tape, type, ansi_color, lifetime) {}
 
 protected:
 //----MÉTODO----
  /// Método que incrementa el lifetime según el color de la celda actual.
  void eatCell();
};