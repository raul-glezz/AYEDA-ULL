/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Práctica 5: Ordenación

 * @file   merge_sort.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   20/03/2024
 * @brief  Declaración de la clase MergeSort
 */

#pragma once

#include "sort_method.h"
#include "sorting_algorithms.h"

/**
 * @brief Clase MergeSort: tipo de dato para representar la ordenación por el mecanismo MergeSort
 */
template <class Key>
class MergeSort : public SortMethod<Key> {
 public:
  //--------------CONSTRUCTOR--------------
  MergeSort(staticSequence<Key>, unsigned, bool);

  //-------------MÉTODO-------------
  /// Método para ordenar una secuencia de elementos mediante el algoritmo de ordenación MergeSort.
  virtual void Sort() override;
};

/**
 * @brief Constructor de la clase MergeSort.
 * @param[in] sequence: secuencia estática de elementos a ordenar.
 * @param[in] size: tamaño de la secuencia de elementos.
 * @param[in] trace: valor booleano para activar o desactivar el modo traza.
 */
template <class Key>
MergeSort<Key>::MergeSort(staticSequence<Key> sequence, unsigned size, bool trace) : SortMethod<Key>(sequence, size, trace) {}

/**
 * @brief Método para ordenar una secuencia de elementos mediante el algoritmo de ordenación MergeSort.
 */
template <class Key>
void MergeSort<Key>::Sort() { mergeSort<Key>(this->sequence_, this->size_, this->trace_); }