/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 3: Hormiga de Langton Evolucionada
 *
 * @file   sliding_vector.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Declaración de la plantilla SlidingVector<T>, 
 *         una estructura de datos unidimensional con índices enteros arbitrarios.
 */

#pragma once

#include <vector>

#include "./sv_exception/sv_exception.h"

template <typename T>
class SlidingVector {
 public:
  //──────────────-----------------CONSTRUCTOR──────────────-----------------
  SlidingVector(int min_index, int max_index, const T& default_value = T{}) :
    min_index_(min_index), data_(max_index - min_index + 1, default_value) {}

  //-----------------------------------MÉTODOS-----------------------------------
  /// Método para obtener el índice mínimo válido.
  int minIndex() const { return min_index_; }
  /// Método para obtener el índice máximo válido.
  int maxIndex() const { return min_index_ + static_cast<int>(data_.size()) - 1; }
  /// Método para obtener el número de elementos almacenados.
  int size() const { return static_cast<int>(data_.size()); }

  /// Sobrecargas del operador [] para acceso a elementos por índice.
  T& operator[](int);
  const T& operator[](int) const;

  /// Método para añadir un nuevo elemento al principio.
  void pushFront(const T& = T{});
  /// Método para añadir un nuevo elemento al final.
  void pushBack(const T& = T{});

 private:
  /// min_index_: índice mínimo válido.
  int min_index_;
  /// data_: vector que almacena los elementos, con índices ajustados a min_index_.
  std::vector<T> data_;
};
