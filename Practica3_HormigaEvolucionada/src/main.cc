/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Algoritmos y Estructuras de Datos Avanzadas
 * Practica 3: Hormiga de Langton Evolucionada
 *
 * @file   main.cc
 * @author Raúl Gonzalez Acosta (alu0101543529@ull.edu.es)
 * @date   02/03/2026
 * @brief  Programa principal que gestiona la simulación de la Hormiga de Langton Evolucionada.
 */

#include <iostream>
#include <string>
#include "../src/simulator/simulator.h"

void showUsage(const std::string& program_name) {
  std::cout <<
    "=== Hormiga de Langton Evolucionada ===\n\n"
    "Uso: " << program_name << " [-h|--help] <fichero_config>\n\n"
    "Formato del fichero de configuración:\n"
    "  Línea 1 : <tamX> <tamY> <numColores> [P|R|S]\n"
    "            P=Periódica (defecto), R=Reflectora, S=Deslizante\n"
    "  Línea 2 : <TIPO> <X> <Y> <DIR> ; <TIPO> <X> <Y> <DIR> ; ...\n"
    "  Líneas 3+: <X> <Y> <color>   (celdas no blancas)\n\n"
    "Tipos de hormiga herbívora (movimiento cardinal):\n"
    "  H-DI  H-DDII  H-IDID  H-DIDI  H-IIII  H-DDDD\n\n"
    "Tipos de hormiga carnívora (movimiento diagonal):\n"
    "  C-IDID  C-DDII  C-DIDI  C-IIII  C-DDDD\n\n"
    "Controles:\n"
    "  ENTER → siguiente paso\n"
    "  s     → guardar estado\n"
    "  q     → salir\n";
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
