/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   tape.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   11/02/2026
 * @brief  Declaración de la clase Tape, que representa la cinta de la Hormiga de Langton con soporte para múltiples colores.
 */

#pragma once

#include <iostream>
#include <vector>
#include <string>

// Definición de una matriz 2D
template <typename T>
using Matrix = std::vector<std::vector<T>>;

// Representación de los colores posibles para las celdas de la cinta
enum class Color : int {
  WHITE = 0,
  BLACK = 1,
  RED = 2,
  GREEN = 3,
  BLUE = 4,
  YELLOW = 5,
  MAGENTA = 6,
  CYAN = 7
};

class Tape {
 public:
  //----------CONSTRUCTORES----------
  Tape(int, int, int);
  Tape(int, int, int, const std::string&);

  //------------------------MÉTODOS------------------------
  /// Método para obtener el tamaño en X de la cinta
  int getSizeX() const { return size_X_; }
  /// Método para obtener el tamaño en Y de la cinta
  int getSizeY() const { return size_Y_; }
  /// Método para obtener el número de colores
  int getNumberColors() const { return number_colors_; }
  
  /// Método para obtener el valor de una celda
  int getCell(int, int) const;

  /// Método para establecer el valor de una celda
  void setCell(int, int, int);

  /// Método para comprobar si una posición es válida en la cinta
  bool isValidPosition(int, int) const;
  /// Método para imprimir una celda específica con color ANSI
  void printCell(std::ostream&, int, int) const;

  /// Método para guardar el estado de la cinta en un archivo
  void saveToFile(const std::string&, const std::vector<std::tuple<std::string, int, int, int>>&) const;

 private:
  //----ATRIBUTOS----
  /// size_X_: tamaño en X de la cinta
  int size_X_;
  /// size_Y_: tamaño en Y de la cinta
  int size_Y_;
  /// number_colors_: número de colores posibles para las celdas
  int number_colors_;
  /// grid_: matriz que representa la cinta
  Matrix<Color> grid_;
  
  /// Método auxiliar para obtener el código ANSI de color
  std::string getColor(Color) const;
};

std::istream& operator>>(std::istream&, Tape&);