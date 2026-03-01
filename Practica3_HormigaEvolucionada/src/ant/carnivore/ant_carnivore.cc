/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 3: Hormiga de Langton Evolucionada
 *
 * @file   ant_carnivore.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Definición de la clase AntCarnivore, que representa una hormiga carnívora.
 */

#include "ant_carnivore.h"

/**
 * @brief Incrementa el lifetime según el porcentaje de voracidad al coincidir con otra hormiga.
 * @param[in] other: Referencia a la otra hormiga con la que se interactúa.
 */
void AntCarnivore::interact(Ant& other) {
  int stolen_percentage = ((other.getLifeTime() * voracity_) / 100);
  if ((stolen_percentage < 1) && (other.getLifeTime() > 0)) { stolen_percentage = 1; }
  // Quita vida a la otra hormiga proporcional a la voracidad
  lifetime_ += stolen_percentage;
  other.setLifeTime(other.getLifeTime() - stolen_percentage);
}