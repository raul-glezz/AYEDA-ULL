/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   tape.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   11/02/2026
 * @brief  Definición de la clase Tape, que representa la cinta de la Hormiga de Langton con soporte para múltiples colores.
 */

#include <fstream>
#include <stdexcept>
#include <tuple>

#include "tape.h"

/**
 * @brief Constructor con tamaño y número de colores especificados.
 * @param[in] size_X: tamaño en X de la cinta.
 * @param[in] size_Y: tamaño en Y de la cinta.
 * @param[in] number_colors: número de colores para las celdas.
 * @throws std::invalid_argument si los tamaños son no positivos o num_colors < 2.
 */
Tape::Tape(int size_X, int size_Y, int number_colors) : size_X_(size_X), size_Y_(size_Y), number_colors_(number_colors) {
  if (size_X <= 0 || size_Y <= 0) {
    throw std::invalid_argument("Error: El tamaño de la cinta debe ser positivo");
  }
  if (number_colors < 2) {
    throw std::invalid_argument("Error: El número de colores debe ser al menos 2");
  }
  grid_.resize(size_Y_, std::vector<Color>(size_X_, Color::WHITE));
}

/**
 * @brief Constructor con tamaño, número de colores y fichero de configuración.
 * @param[in] size_X: tamaño en X de la cinta.
 * @param[in] size_Y: tamaño en Y de la cinta.
 * @param[in] number_colors: número de colores para las celdas.
 * @param[in] filename: nombre del fichero de configuración.
 * @throws std::invalid_argument si los tamaños son no positivos.
 * @throws std::runtime_error si no se puede abrir el fichero.
 */
Tape::Tape(int size_X, int size_Y, int number_colors, const std::string& filename) : size_X_(size_X), size_Y_(size_Y), number_colors_(number_colors) {
  if (size_X <= 0 || size_Y <= 0) {
    throw std::invalid_argument("Error: El tamaño de la cinta debe ser positivo");
  }
  if (number_colors < 2) {
    throw std::invalid_argument("Error: El número de colores debe ser al menos 2");
  }
  grid_.resize(size_Y_, std::vector<Color>(size_X_, Color::WHITE));
  
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
 * @return Valor entero del color de la celda.
 * @throws std::out_of_range si la posición está fuera de los límites.
 */
int Tape::getCell(int x, int y) const {
  if (!isValidPosition(x, y)) {
    throw std::out_of_range("Error: Posición fuera de los límites de la cinta");
  }
  return static_cast<int>(grid_[y][x]);
}

/**
 * @brief Método para establecer el valor de una celda.
 * @param[in] x: coordenada X de la celda.
 * @param[in] y: coordenada Y de la celda.
 * @param[in] value: valor entero del color (se hace módulo num_colors_).
 * @throws std::out_of_range si la posición está fuera de los límites.
 */
void Tape::setCell(int x, int y, int value) {
  if (!isValidPosition(x, y)) {
    throw std::out_of_range("Error: Posición fuera de los límites de la cinta");
  }
  // Asegurar que el valor esté en el rango válido
  value = value % number_colors_;
  if (value < 0) value += number_colors_;
  grid_[y][x] = static_cast<Color>(value);
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
 * @brief Obtiene el código de color ANSI para un color dado.
 * @param[in] color: color a convertir.
 * @return String con el código ANSI del color.
 */
std::string Tape::getColor(Color color) const {
  switch (color) {
    case Color::WHITE:   return "\033[47m";
    case Color::BLACK:   return "\033[40m";
    case Color::RED:     return "\033[41m";
    case Color::GREEN:   return "\033[42m";
    case Color::BLUE:    return "\033[44m";
    case Color::YELLOW:  return "\033[43m";
    case Color::MAGENTA: return "\033[45m";
    case Color::CYAN:    return "\033[46m";
    default:             return "\033[47m";
  }
}

/**
 * @brief Método para imprimir una celda específica con color ANSI.
 * @param[in,out] os: referencia al flujo de salida.
 * @param[in] x: coordenada X de la celda.
 * @param[in] y: coordenada Y de la celda.
 * @throws std::out_of_range si la posición está fuera de los límites.
 */
void Tape::printCell(std::ostream& os, int x, int y) const {
  if (!isValidPosition(x, y)) {
    throw std::out_of_range("Error: Posición fuera de los límites de la cinta");
  }
  
  Color cell_color = grid_[y][x];
  
  // Si es blanco, solo imprimimos un espacio sin color
  if (cell_color == Color::WHITE) { os << " "; } 
  // Para otros colores, mostramos el número del color con fondo de color
  else { os << getColor(cell_color) << static_cast<int>(cell_color) << "\033[0m"; }
}

/**
 * @brief Método para guardar el estado de la cinta en un archivo.
 * @param[in] filename: nombre del fichero donde se guardará el estado.
 * @param[in] ants: vector de tuplas con información de las hormigas (tipo, x, y, dirección).
 */
void Tape::saveToFile(const std::string& filename,  const std::vector<std::tuple<std::string, int, int, int>>& ants) const {
  std::ofstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Error: No se pudo crear el fichero: " + filename);
  }
  
  // Línea 1: Tamaño de la cinta y número de colores
  file << size_X_ << " " << size_Y_ << " " << number_colors_ << std::endl;
  
  // Línea 2: Tipo, posición y orientación de cada hormiga
  for (size_t i = 0; i < ants.size(); i++) {
    const auto& [type, x, y, dir] = ants[i];
    file << type << " " << x << " " << y << " ";
    
    // Convertimos la dirección numérica a símbolo
    switch (dir) {
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
      if (grid_[y][x] != Color::WHITE) {
        file << x << " " << y << " " << static_cast<int>(grid_[y][x]) << std::endl;
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
  int x, y, color;
  // Leemos las coordenadas y colores de las celdas no blancas
  while (is >> x >> y >> color) {
    if (tape.isValidPosition(x, y)) {
      tape.setCell(x, y, color);
    }
  }
  return is;
}