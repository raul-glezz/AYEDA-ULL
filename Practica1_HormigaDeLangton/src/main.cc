/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 1: La Hormiga de Langton

 * @file   main.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   30/01/2026
 * @brief  Programa principal que gestiona la simulación de la Hormiga de Langton.
 */

#include <iostream>
#include <string>

#include "./simulator/simulator.h"

void showUsage(const std::string& program_name) {
  std::cout << "Modo de uso: " << program_name << " [-h | --help ] <fichero_configuracion.txt>" << std::endl << std::endl;
  std::cout << "-h | --help: Muestra las instrucciones para el correcto funcionamiento del programa." << std::endl << std::endl;
  std::cout << "<fichero_configuracion.txt>: Fichero de texto que contiene la configuración inicial de la simulación con el siguiente formato:" << std::endl << std::endl;
  std::cout << "\tLínea 1: Tamaño de la cinta (<tamañoX> <tamañoY>)" << std::endl;
  std::cout << "\tLínea 2: Posición y orientación inicial de la hormiga (<coordenadaX> <coordenadaY> <dirección>)" << std::endl;
  std::cout << "\tDonde <dirección> es un entero que representa la dirección:" << std::endl;
  std::cout << "\t\t0: Oeste\n \t\t1: Este\n \t\t2: Norte\n \t\t3: Sur" << std::endl;
  std::cout << "\tLíneas 3..n: Posiciones de las celdas negras (<coordenadaX> <coordenadaY>)" << std::endl;
}

int main(int argc, char* argv[]) {
  // Si no se han introducido argumentos por línea de comandos, se muestra un mensaje de error y la función que muestra el uso correcto del programa
  if (argc <= 1) {
    std::cerr << "Error: No se han introducido argumentos por línea de comandos." << std::endl << std::endl;
    showUsage(argv[0]);
    exit(EXIT_FAILURE);
  }

  if (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h") {
    showUsage(argv[0]);
    return 0;
  }
  
  std::string filename = argv[1];
  
  try {
    std::cout << "Inicializando simulación desde el fichero: " << filename << std::endl;
    Simulator simulator(filename);
    std::cout << "Presiona ENTER para comenzar...";
    std::cin.get();
    simulator.run();
    std::cout << "Total de pasos ejecutados: " << simulator.getSteps() << std::endl;
      
  } catch (const std::exception& exception) {
    std::cerr << "Error: " << exception.what() << std::endl;
    return 1;
  }
  
  return 0;
}
