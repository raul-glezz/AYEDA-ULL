/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   ant_carnivore.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   11/02/2026
 * @brief  Declaración de la clase AntCarnivore, que representa a las hormigas carnívoras.
 */

#pragma once

#include "../ant.h"

class AntCarnivore : public Ant {
 public:
  //------------------------------------------------------------------CONSTRUCTOR------------------------------------------------------------------
  AntCarnivore(int x, int y, Direction direction, Tape* tape, const std::string& type, const std::string& ansi_color, int lifetime, int voracity) : 
    Ant(x, y, direction, tape, type, ansi_color, lifetime), voracity_(voracity) {}

  //-------------------MÉTODO-------------------
   /// Método que devuelve la voracidad de la hormiga carnívora
  int getVoracity() const { return voracity_; }
  /// Método que incrementa el lifetime según el porcentaje de voracidad al coincidir con otra hormiga
  void interact(Ant&) override;

 protected:
  /// voracity_: porcentaje de lifetime que roba a otras hormigas al coincidir en una celda
  int voracity_;
};