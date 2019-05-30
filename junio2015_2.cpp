#include <iostream>
using namespace std;

//.h
struct Pareja {
  int dato;
  int nveces;
};

class Frecuencias {
  Pareja* parejas;
  int npares;

  void liberarEspacio();
  void copiarDatos(const Frecuencias&);
public:
  Frecuencias();
  ~Frecuencias();
}

//.cpp
Frecuencias::Frecuencias() {
  parejas = 0;
  npares = 0;
}

void Frecuencias::liberarEspacio() {
  delete[] parejas;
  npares = 0;
}

Frecuencias::~Frecuencias() {
  liberarEspacio();
}

void Frecuencias::reservarEspacio(int _npares) {
  npares = _npares;
  parejas = new Pareja[npares];
}

void Frecuencias::copiarDatos(const Frecuencias& otra) {
  for (int i = 0; i < otra.npares; i++) {
    parejas[i] = otra.parejas[i];
  }
}

Frecuencias::Frecuencias(const Frecuencias& otra) {
  reservarEspacio(otra.npares);
  copiarDatos(otra);
}

operator+() {
  liberarEspacio();
  reservarEspacio(otra.npares);
  copiarDatos(otra);
}


int main() {

}
