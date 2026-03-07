/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 3: Hormiga de Langton Evolucionada
 *
 * @file   sliding.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Definición de la clase TapeSliding, que implementa la frontera deslizante para la cinta de la Hormiga de Langton.
 */

#include <fstream>
#include <stdexcept>

#include "sliding.h"

#define RESET_ANSI "\033[0m"

/**
 * @brief Constructor de la clase TapeSliding
 * @param[in] size_X Tamaño inicial en X de la cinta
 * @param[in] size_Y Tamaño inicial en Y de la cinta
 * @param[in] number_colors Número de colores posibles para las celdas
 */
TapeSliding::TapeSliding(int size_X, int size_Y, int number_colors) : 
  Tape(size_X, size_Y, number_colors), min_x_(0), min_y_(0),
  sliding_grid_(0, size_Y - 1, SlidingVector<Color>(0, size_X - 1, Color::WHITE)) {}

/**
 * @brief Método para obtener el valor de una celda.
 * @param[in] x: coordenada X de la celda.
 * @param[in] y: coordenada Y de la celda.
 * @return Valor entero del color de la celda.
 * @throws std::out_of_range si la posición está fuera de los límites.
 */
int TapeSliding::getCell(int x, int y) const {
  if (!isValidPosition(x, y)) {
    throw std::out_of_range("Error: Posición fuera de los límites de la cinta deslizante");
  }
  return static_cast<int>(sliding_grid_[y][x]);
}

/**
 * @brief Método para establecer el valor de una celda.
 * @param[in] x: coordenada X de la celda.
 * @param[in] y: coordenada Y de la celda.
 * @param[in] value: valor entero del color (se hace módulo num_colors_).
 * @throws std::out_of_range si la posición está fuera de los límites.
 */
void TapeSliding::setCell(int x, int y, int value) {
  if (!isValidPosition(x, y)) {
    throw std::out_of_range("Error: Posición fuera de los límites de la cinta deslizante");
  }
  // Asegurar que el valor esté en el rango válido
  value = value % number_colors_;
  if (value < 0) value += number_colors_;
  sliding_grid_[y][x] = static_cast<Color>(value);
}

/**
 * @brief Método para aplicar la condición de frontera deslizante.
 * @param[in,out] new_x: referencia a la coordenada X a comprobar y modificar si es necesario.
 * @param[in,out] new_y: referencia a la coordenada Y a comprobar y modificar si es necesario.
 * @return True si la posición es válida o se ha ajustado correctamente, false en caso contrario.
 */
bool TapeSliding::applyBorder(int& new_x, int& new_y, int&) {
  // Si la posición es válida, no hay que hacer nada
  if (isValidPosition(new_x, new_y)) { return true; }

  // Calculamos columna y fila lógicas
  int col = new_x - min_x_;
  int row = new_y - min_y_;

  if (col < 0)        growLeft();
  if (col >= size_X_) growRight();
  if (row < 0)        growUp();
  if (row >= size_Y_) growDown();

  return true;
}

/**
 * @brief Método para comprobar si una posición es válida en la cinta.
 * @param[in] x: coordenada X a comprobar.
 * @param[in] y: coordenada Y a comprobar.
 * @return True si la posición es válida, false en caso contrario.
 */
bool TapeSliding::isValidPosition(int x, int y) const {
  return (x >= min_x_ && x <= sliding_grid_[min_y_].maxIndex() &&
          y >= min_y_ && y <= sliding_grid_.maxIndex());
}

/**
 * @brief Método para imprimir una celda específica con color ANSI.
 * @param[in,out] os: referencia al flujo de salida.
 * @param[in] x: coordenada X de la celda.
 * @param[in] y: coordenada Y de la celda.
 * @throws std::out_of_range si la posición está fuera de los límites.
 */
void TapeSliding::printCell(std::ostream& os, int x, int y) const {
  if (!isValidPosition(x, y)) {
    throw std::out_of_range("Error: Posición fuera de los límites de la cinta deslizante");
  }
  
  Color cell_color = sliding_grid_[y][x];
  
  // Si es blanco, solo imprimimos un espacio sin color
  if (cell_color == Color::WHITE) { os << " "; } 
  // Para otros colores, mostramos el número del color con fondo de color
  else { os << getColor(cell_color) << " " << RESET_ANSI; }
}

/**
 * @brief Método para guardar el estado de la cinta en un archivo.
 * @param[in] filename: nombre del fichero donde se guardará el estado.
 * @param[in] ants: vector de tuplas con información de las hormigas (tipo, x, y, dirección, lifetime).
 */
void TapeSliding::saveToFile(const std::string& filename, const std::vector<std::tuple<std::string, int, int, int, int>>& ants) const {
  std::ofstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Error: No se pudo crear el fichero: " + filename);
  }
  
  // Línea 1: Tamaño de la cinta y número de colores
  file << size_X_ << " " << size_Y_ << " " << number_colors_ << std::endl;
  
  // Línea 2: Tipo, posición y orientación de cada hormiga
  for (size_t i = 0; i < ants.size(); i++) {
    const auto& [type, x, y, direction, lifetime] = ants[i];
    file << type << " " << x << " " << y << " ";
    
    // Convertimos la dirección numérica a símbolo
    switch (direction) {
      case 0: file << "<"; break;
      case 1: file << ">"; break;
      case 2: file << "^"; break;
      case 3: file << "v"; break;
      default: file << ">"; break;
    }
    
    if (i < ants.size() - 1) {
      file << " ; ";
    }
  }
  file << std::endl;

  // Líneas 3..n: Posiciones y colores de las celdas no blancas
  for (int y = 0; y < size_Y_; y++) {
    for (int x = 0; x < size_X_; x++) {
      const int logical_x = x + min_x_;
      const int logical_y = y + min_y_;
      if (sliding_grid_[logical_y][logical_x] != Color::WHITE) {
        file << logical_x << " " << logical_y << " " << static_cast<int>(sliding_grid_[logical_y][logical_x]) << std::endl;
      }
    }
  }
  
  file.close();
}

/**
 * @brief Método para expandir la cinta hacia la izquierda.
 */
void TapeSliding::growLeft() {
  for (int y = sliding_grid_.minIndex(); y <= sliding_grid_.maxIndex(); ++y) {
    sliding_grid_[y].pushFront(Color::WHITE);
  }
  min_x_--;
  size_X_++;
}

/**
 * @brief Método para expandir la cinta hacia la derecha.
 */
void TapeSliding::growRight() {
  for (int y = sliding_grid_.minIndex(); y <= sliding_grid_.maxIndex(); ++y) {
    sliding_grid_[y].pushBack(Color::WHITE);
  }
  size_X_++;
}

/**
 * @brief Método para expandir la cinta hacia arriba.
 */
void TapeSliding::growUp() {
  sliding_grid_.pushFront(SlidingVector<Color>(min_x_, min_x_ + size_X_ - 1, Color::WHITE));
  min_y_--;
  size_Y_++;
}

/**
 * @brief Método para expandir la cinta hacia abajo.
 */
void TapeSliding::growDown() {
  sliding_grid_.pushBack(SlidingVector<Color>(min_x_, min_x_ + size_X_ - 1, Color::WHITE));
  size_Y_++;
}
