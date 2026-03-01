/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 3: Hormiga de Langton Evolucionada
 *
 * @file   tape.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Declaración de la clase base abstracta Tape, que representa la cinta de la Hormiga de Langton con soporte para múltiples colores.
 */

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <tuple>

// Tipos de condición de frontera
enum class BorderType { PERIODIC, REFLECTIVE, SLIDING };

// Representación de los colores posibles para las celdas
enum class Color : int {
  WHITE   = 0,
  BLACK   = 1,
  RED     = 2,
  GREEN   = 3,
  BLUE    = 4,
  YELLOW  = 5,
  MAGENTA = 6,
  CYAN    = 7
};

// Definición de una matriz genérica 2D
template <typename T>
using Matrix = std::vector<std::vector<T>>;

class Tape {
 public:
  //------------CONSTRUCTORES------------
  Tape(int, int, int);
  Tape(int, int, int, const std::string&);

  // ------DESTRUCTOR------
  virtual ~Tape() = default;

  //------------------------MÉTODOS------------------------
  /// Método virtual para obtener el tamaño en X de la cinta
  virtual int getSizeX() const { return size_X_; }
  /// Método virtual para obtener el tamaño en Y de la cinta
  virtual int getSizeY() const { return size_Y_; }
  /// Método virtual para obtener el número de colores
  virtual int getNumberColors() const { return number_colors_; }
  
  /// Método virtual para obtener el valor de una celda
  virtual int getCell(int, int) const;

  /// Método virtual para establecer el valor de una celda
  virtual void setCell(int, int, int);
  /// Método virtual para aplicar la condición de frontera al intentar salir de los límites
  virtual bool applyBorder(int&, int&, int&) = 0;

  /// Método virtual para comprobar si una posición es válida en la cinta
  virtual bool isValidPosition(int, int) const;
  /// Método virtual para imprimir una celda específica con color ANSI
  virtual void printCell(std::ostream&, int, int) const;

  /// Método virtual para guardar el estado de la cinta en un archivo
  virtual void saveToFile(const std::string&, const std::vector<std::tuple<std::string, int, int, int, int>>&) const;

 protected:
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
/// Sobrecarga del operador de extracción en flujo (>>) para la clase Tape
std::istream& operator>>(std::istream&, Tape&);
