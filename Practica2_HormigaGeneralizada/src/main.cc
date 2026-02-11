/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 2: Hormiga de Langton Generalizada

 * @file   main.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   11/02/2026
 * @brief  Programa principal que gestiona la simulación de la Hormiga de Langton Generalizada.
 */

#include <iostream>
#include <string>

#include "./simulator/simulator.h"

void showUsage(const std::string& program_name) {
  std::cout << "=== Hormiga de Langton Generalizada ===" << std::endl << std::endl;
  std::cout << "Modo de uso: " << program_name << " [-h | --help ] <fichero_configuracion.txt>" << std::endl << std::endl;
  std::cout << "-h | --help: Muestra las instrucciones para el correcto funcionamiento del programa." << std::endl << std::endl;
  std::cout << "<fichero_configuracion.txt>: Fichero de texto que contiene la configuración inicial de la simulación con el siguiente formato:" << std::endl << std::endl;
  std::cout << "\tLínea 1: Tamaño de la cinta y número de colores (<tamañoX> <tamañoY> <numColores>)" << std::endl;
  std::cout << "\tLínea 2: Tipo, posición y orientación de cada hormiga (separadas por ';')" << std::endl;
  std::cout << "\t         Formato: <TIPO> <X> <Y> <DIRECCION> ; <TIPO> <X> <Y> <DIRECCION> ; ..." << std::endl;
  std::cout << "\tDonde <TIPO> es una cadena como 'DI', 'DDII', 'IDID', etc." << std::endl;
  std::cout << "\tDonde <DIRECCION> es un símbolo:" << std::endl;
  std::cout << "\t\t<: Oeste (izquierda)" << std::endl;
  std::cout << "\t\t>: Este (derecha)" << std::endl;
  std::cout << "\t\t^: Norte (arriba)" << std::endl;
  std::cout << "\t\tv: Sur (abajo)" << std::endl;
  std::cout << "\tLíneas 3..n: Posiciones y colores de las celdas no blancas (<X> <Y> <color>)" << std::endl << std::endl;
  std::cout << "Tipos de hormigas disponibles:" << std::endl;
  std::cout << "\t- DI: Hormiga clásica (2 colores)" << std::endl;
  std::cout << "\t- DDII: 4 colores, primeros 2 giran derecha, últimos 2 izquierda" << std::endl;
  std::cout << "\t- IDID: 4 colores alternados (I-D-I-D)" << std::endl;
  std::cout << "\t- DIDI: 4 colores alternados (D-I-D-I)" << std::endl;
  std::cout << "\t- IIII: 4 colores, siempre gira izquierda" << std::endl;
  std::cout << "\t- DDDD: 4 colores, siempre gira derecha" << std::endl;
}

int main(int argc, char* argv[]) {
  // Si no se han introducido argumentos por línea de comandos
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