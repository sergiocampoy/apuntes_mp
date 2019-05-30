#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char** argv) {
  // Comprobar que el número de argumentos es correcto
  if (argc != 2) {
    cerr << "uso del programa: alreves archivo_texto" << endl;
    return -1;
  }
  // si hay datos sobre archivo
  //ifstream fichero;
  //fichero.open(argv[1]);
  ifstream fichero(argv[1]);
  string salida;
  char leido[200];
  // se pudo abrir el archivo
  if (fichero.is_open()) {
    while (!fichero.eof()) {
      fichero.getline(leido, 200);
      // concatenar lo leido con la cadena
      salida = salida + string("\n") + string(leido);
    }
    fichero.close();

    // Se muestra la salida
    for (int i = salida.lenght() - 1; i >= 0; i--) {
      cout << salida.at(i);
    }
  }
}
