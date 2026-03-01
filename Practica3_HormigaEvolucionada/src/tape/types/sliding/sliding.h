/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 3: Hormiga de Langton Evolucionada
 *
 * @file   sliding.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Declaración de la clase TapeSliding, que implementa la frontera deslizante para la cinta de la Hormiga de Langton.
 */

#pragma once

#include "../../tape.h"

class TapeSliding : public Tape {
 public:
  //---------------------CONSTRUCTOR---------------------
  TapeSliding(int size_X, int size_Y, int number_colors);

  //------------------------MÉTODOS------------------------
  /// Método para obtener el tamaño en X de la cinta
  int getSizeX() const override { return size_X_; }
  /// Método para obtener el tamaño en Y de la cinta
  int getSizeY() const override { return size_Y_; }
  /// Método para obtener el indice de X en la cinta deslizante
  int getMinX() const { return min_x_; }
  /// Método para obtener el indice de Y en la cinta deslizante
  int getMinY() const { return min_y_; }
  /// Método para obtener el valor de una celda
  int getCell(int, int) const override;

  /// Método para establecer el valor de una celda
  void setCell(int, int, int) override;
  /// Método para aplicar la condición de frontera deslizante
  bool applyBorder(int&, int&, int&) override;

  /// Método para comprobar si una posición es válida en la cinta
  bool isValidPosition(int, int) const override;
  /// Método para imprimir una celda específica con color ANSI
  void printCell(std::ostream&, int, int) const override;

  /// Método para guardar el estado de la cinta en un archivo
  void saveToFile(const std::string&, const std::vector<std::tuple<std::string, int, int, int, int>>&) const override;

 private:
  //----ATRIBUTOS----
  /// min_x: tamaño en X de la cinta
  int min_x_;
  /// min_y: tamaño en Y de la cinta
  int min_y_;

  //----MÉTODOS----
  /// Método para expandir la cinta hacia la izquierda
  void growLeft();
  /// Método para expandir la cinta hacia la derecha
  void growRight();
  /// Método para expandir la cinta hacia arriba
  void growUp();
  /// Método para expandir la cinta hacia abajo
  void growDown();
};