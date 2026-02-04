/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 1: La Hormiga de Langton

 * @file   tape.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   30/01/2026
 * @brief  Definición de la clase Tape, que representa la cinta de la Hormiga de Langton.
 */

#include <fstream>
#include <stdexcept>

#include "tape.h"

/**
 * @brief Constructor con tamaño especificado.
 * @param[in] sizeX: tamaño en X de la cinta.
 * @param[in] sizeY: tamaño en Y de la cinta.
 * @throws std::invalid_argument si los tamaños son no positivos.
 */
Tape::Tape(int sizeX, int sizeY) : size_X_(sizeX), size_Y_(sizeY) {
  if (sizeX <= 0 || sizeY <= 0) {
    throw std::invalid_argument("Error: El tamaño de la cinta debe ser positivo");
  }
  grid_.resize(size_Y_, std::vector<int>(size_X_, 0));
}

/**
 * @brief Constructor con tamaño y fichero de configuración.
 * @param[in] sizeX: tamaño en X de la cinta.
 * @param[in] sizeY: tamaño en Y de la cinta.
 * @param[in] filename: nombre del fichero de configuración.
 * @throws std::invalid_argument si los tamaños son no positivos.
 * @throws std::runtime_error si no se puede abrir el fichero.
 */
Tape::Tape(int sizeX, int sizeY, const std::string& filename) : size_X_(sizeX), size_Y_(sizeY) {
  if (sizeX <= 0 || sizeY <= 0) {
    throw std::invalid_argument("Error: El tamaño de la cinta debe ser positivo");
  }
  grid_.resize(size_Y_, std::vector<int>(size_X_, 0));
  
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Error: No se pudo abrir el fichero: " + filename);
  }
  file >> (*this);
  file.close();
}

/**
 * @brief Método para obtener el valor de una celda.
 * @param[in] x: coordenada X de la celda.
 * @param[in] y: coordenada Y de la celda.
 * @return Valor de la celda (0 o 1).
 * @throws std::out_of_range si la posición está fuera de los límites.
 */
int Tape::getCell(int x, int y) const {
  if (!isValidPosition(x, y)) {
    throw std::out_of_range("Error: Posición fuera de los límites de la cinta");
  }
  return grid_[y][x];
}

/**
 * @brief Método para establecer el valor de una celda.
 * @param[in] x: coordenada X de la celda.
 * @param[in] y: coordenada Y de la celda.
 * @param[in] value: valor a establecer (0 o 1).
 * @throws std::out_of_range si la posición está fuera de los límites.
 */
void Tape::setCell(int x, int y, int value) {
  if (!isValidPosition(x, y)) {
    throw std::out_of_range("Error: Posición fuera de los límites de la cinta");
  }
  grid_[y][x] = value;
}

/**
 * @brief Método para comprobar si una posición es válida en la cinta.
 * @param[in] x: coordenada X a comprobar.
 * @param[in] y: coordenada Y a comprobar.
 * @return True si la posición es válida, false en caso contrario.
 */
bool Tape::isValidPosition(int x, int y) const {
  return ((x >= 0) && (x < size_X_) && (y >= 0) && (y < size_Y_));
}

/**
 * @brief Método para imprimir una celda específica.
 * @param[in,out] os: referencia al flujo de salida.
 * @param[in] x: coordenada X de la celda.
 * @param[in] y: coordenada Y de la celda.
 * @throws std::out_of_range si la posición está fuera de los límites.
 */
void Tape::printCell(std::ostream& os, int x, int y) const {
  if (!isValidPosition(x, y)) {
    throw std::out_of_range("Error: Posición fuera de los límites de la cinta");
  }
  os << (grid_[y][x] == 1 ? "X" : " ");
}

/**
 * @brief Método para guardar el estado de la cinta en un archivo.
 * @param[in] filename: nombre del fichero donde se guardará el estado.
 * @param[in] ant_X: posición X de la hormiga.
 * @param[in] ant_Y: posición Y de la hormiga.
 * @param[in] ant_direction: dirección de la hormiga.
 */
void Tape::saveToFile(const std::string& filename, int ant_X, int ant_Y, int ant_direction) const {
  std::ofstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Error: No se pudo crear el fichero: " + filename);
  }
  
  // Línea 1: Tamaño de la cinta
  file << size_X_ << " " << size_Y_ << std::endl;
  
  // Línea 2: Posición y orientación de la hormiga
  file << ant_X << " " << ant_Y << " " << ant_direction << std::endl;
  
  // Líneas 3..n: Posiciones de las celdas negras
  for (int y = 0; y < size_Y_; y++) {
    for (int x = 0; x < size_X_; x++) {
      if (grid_[y][x] == 1) {
        file << x << " " << y << std::endl;
      }
    }
  }
  
  file.close();
}

/**
 * @brief Sobrecarga del operador de extracción en flujo (>>).
 * @param[in,out] is: referencia al flujo de entrada (std::cin).
 * @param[out] tape: referencia al objeto Tape donde se cargará el estado.
 * @return Referencia al flujo de entrada (std::cin).
 */
std::istream& operator>>(std::istream& is, Tape& tape) {
  int x, y;
  // Leemos las coordenadas de las celdas negras
  while (is >> x >> y) {
    if (tape.isValidPosition(x, y)) {
      tape.setCell(x, y, 1);
    }
  }
  return is;
}