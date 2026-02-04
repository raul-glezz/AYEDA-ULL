/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 1: La Hormiga de Langton

 * @file   tape.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   30/01/2026
 * @brief  Declaración de la clase Tape, que representa la cinta de la Hormiga de Langton.
 */

#pragma once

#include <iostream>
#include <vector>
#include <string>

// Definición de una matriz 2D
template <typename T>
using Matrix = std::vector<std::vector<T>>;

class Tape {
 public:
  //----------CONSTRUCTORES----------
  Tape(int, int);
  Tape(int, int, const std::string&);

  //------------------------MÉTODOS------------------------
  /// Método para obtener el tamaño en X de la cinta
  int getSizeX() const { return size_X_; }
  /// Método para obtener el tamaño en Y de la cinta
  int getSizeY() const { return size_Y_; }
  /// Método para obtener el valor de una celda
  int getCell(int, int) const;

  /// Método para establecer el valor de una celda
  void setCell(int, int, int);

  /// Método para comprobar si una posición es válida en la cinta
  bool isValidPosition(int, int) const;
  /// Método para imprimir una celda específica
  void printCell(std::ostream&, int, int) const;

  /// Método para guardar el estado de la cinta en un archivo
  void saveToFile(const std::string&, int, int, int) const;

 private:
  //----ATRIBUTOS----
  /// size_X_: tamaño en X de la cinta
  int size_X_;
  /// size_Y_: tamaño en Y de la cinta
  int size_Y_;
  /// grid_: matriz que representa la cinta
  Matrix<int> grid_;
};

std::istream& operator>>(std::istream& is, Tape& tape);