/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 3: Hormiga de Langton Evolucionada
 *
 * @file   sliding_vector.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Definición de la plantilla SlidingVector<T>, 
 *         una estructura de datos unidimensional con índices enteros arbitrarios.
 */

#include "sliding_vector.h"

/**
 * @brief Sobrecarga del operador [] para acceso a elementos por índice.
 * @param[in] index Índice del elemento a acceder.
 * @return Referencia al elemento en el índice dado.
 * @throws SVException Si el índice está fuera del rango válido.
 */
template <typename T>
T& SlidingVector<T>::operator[](int index) {
  if (index < min_index_ || index > maxIndex()) {
    throw SVException(index);
  }
  return data_[index - min_index_];
}

template <typename T>
const T& SlidingVector<T>::operator[](int index) const {
  if (index < min_index_ || index > maxIndex()) {
    throw SVException(index);
  }
  return data_[index - min_index_];
}

/**
 * @brief Método para añadir un nuevo elemento al principio.
 * @param[in] value Valor del nuevo elemento a añadir.
 */
template <typename T>
void SlidingVector<T>::pushFront(const T& value) {
  data_.insert(data_.begin(), value);
  min_index_--;
}

/**
 * @brief Método para añadir un nuevo elemento al final.
 * @param[in] value Valor del nuevo elemento a añadir.
 */
template <typename T>
void SlidingVector<T>::pushBack(const T& value) {
  data_.push_back(value);
}