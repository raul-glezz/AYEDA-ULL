/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 5: Ordenación

 * @file   bubble_sort.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   20/03/2024
 * @brief  Declaración de la clase BubbleSort
 */

#pragma once

#include "sort_method.h"
#include "sorting_algorithms.h"

/**
 * @brief Clase BubbleSort: tipo de dato para representar la ordenación por el mecanismo BubbleSort
 */
template <class Key>
class BubbleSort : public SortMethod<Key> {
 public:
  //--------------CONSTRUCTOR--------------
  BubbleSort(staticSequence<Key>, unsigned, bool);

  //-------------MÉTODO-------------
  /// Método para ordenar una secuencia de elementos mediante el algoritmo de ordenación BubbleSort.
  virtual void Sort() override;
};

/**
 * @brief Constructor de la clase BubbleSort.
 * @param[in] sequence: secuencia estática de elementos a ordenar.
 * @param[in] size: tamaño de la secuencia de elementos.
 * @param[in] trace: valor booleano para activar o desactivar el modo traza.
 */
template <class Key>
BubbleSort<Key>::BubbleSort(staticSequence<Key> sequence, unsigned size, bool trace) : SortMethod<Key>(sequence, size, trace) {}

/**
 * @brief Método para ordenar una secuencia de elementos mediante el algoritmo de ordenación BubbleSort.
 */
template <class Key>
void BubbleSort<Key>::Sort() { bubbleSort<Key>(this->sequence_, this->size_, this->trace_); }