/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 1: La Hormiga de Langton

 * @file   ant.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   30/01/2026
 * @brief  Declaración de la clase Ant, que representa la hormiga en la simulación de Langton.
 */

#pragma once

#include <iostream>

#include "../tape/tape.h"

enum Direction {
  LEFT = 0,
  RIGHT = 1,
  UP = 2,
  DOWN = 3
};

class Ant {
 public:
  //---------------------------------------------CONSTRUCTOR---------------------------------------------
  Ant(int x, int y, Direction direction, Tape* tape) : x_(x), y_(y), direction_(direction), tape_(tape) {}

  //----------------------MÉTODOS----------------------
  /// Método que devuelve la posición X de la hormiga
  int getX() const { return x_; }
  /// Método que devuelve la posición Y de la hormiga
  int getY() const { return y_; }
  /// Método que devuelve la dirección de la hormiga
  Direction getDirection() const { return direction_; }
  
  /// Método que mueve la hormiga según las reglas de Langton
  void move();
  /// Método que verifica si la hormiga está fuera de los límites de la cinta
  bool isOutOfBounds() const;
  
 private:
  //-----ATRIBUTOS-----
  /// x_: posición X de la hormiga
  int x_;
  /// y_: posición Y de la hormiga
  int y_;
  /// direction_: dirección actual de la hormiga
  Direction direction_;
  /// tape_: puntero a la cinta sobre la que se mueve la hormiga
  Tape* tape_;
  
  //-----MÉTODOS-----
  /// Método que gira la hormiga 90 grados a la izquierda
  void turnLeft();
  /// Método que gira la hormiga 90 grados a la derecha
  void turnRight();
  /// Método que mueve la hormiga una celda hacia adelante en la dirección actual
  void moveForward();
};

/// Sobrecarga del operador de inserción en flujo (<<) para la clase Ant
std::ostream& operator<<(std::ostream&, const Ant&);
