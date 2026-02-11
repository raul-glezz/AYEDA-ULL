/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   ant.h
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   11/02/2026
 * @brief  Declaración de la clase base abstracta Ant y sus clases derivadas.
 */

#pragma once

#include <iostream>
#include <string>

#include "../tape/tape.h"

// Definición de las direcciones posibles para la hormiga
enum Direction {
  LEFT = 0,
  RIGHT = 1,
  UP = 2,
  DOWN = 3
};

/**
 * @brief Clase base abstracta que representa una hormiga genérica.
 */
class Ant {
 public:
  //-----------------------------------------------CONSTRUCTOR-----------------------------------------------
  Ant(int x, int y, Direction direction, Tape* tape, const std::string& type, const std::string& ansi_color) : 
    x_(x), y_(y), direction_(direction), tape_(tape), type_(type), ansi_color_(ansi_color) {}
  
  //------DESTRUCTOR------
  virtual ~Ant() = default;

  //----------------------MÉTODOS----------------------
  /// Método que devuelve la posición X de la hormiga
  int getX() const { return x_; }
  /// Método que devuelve la posición Y de la hormiga
  int getY() const { return y_; }
  /// Método que devuelve la dirección de la hormiga
  Direction getDirection() const { return direction_; }
  /// Método que devuelve el tipo de hormiga
  std::string getType() const { return type_; }
  /// Método que devuelve el código ANSI de color
  std::string getColor() const { return ansi_color_; }
  
  /// Método polimórfico que mueve la hormiga según las reglas específicas del tipo
  virtual void move() = 0;
  
  /// Método que verifica si la hormiga está fuera de los límites de la cinta
  bool isOutOfBounds() const;
  
 protected:
  //-------ATRIBUTOS-------
  /// x_: posición X de la hormiga
  int x_;
  /// y_: posición Y de la hormiga
  int y_;
  /// direction_: dirección actual de la hormiga
  Direction direction_;
  /// tape_: puntero a la cinta sobre la que se mueve la hormiga
  Tape* tape_;
  /// type_: cadena que identifica el tipo de hormiga
  std::string type_;
  /// ansi_color_: código ANSI para el color de visualización
  std::string ansi_color_;
  
  //---------MÉTODOS---------
  /// Método que gira la hormiga 90 grados a la izquierda
  void turnLeft();
  /// Método que gira la hormiga 90 grados a la derecha
  void turnRight();
  /// Método que mueve la hormiga una celda hacia adelante en la dirección actual
  void moveForward();
  /// Método que cambia el color de la celda actual
  virtual void changeColor();
};
/// Sobrecarga del operador de inserción en flujo (<<) para la clase Ant
std::ostream& operator<<(std::ostream&, const Ant&);