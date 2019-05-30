#include <iostream>
using namespace std;

//.h
class Celda {
public:
  double valor;
  Celda* siguiente;
};

class Lista {
private:
  Celda* primero;
public:
  void agregarElemento(double);
  void imprimir();
  void imprimirInverso();
};

// .cpp
void Lista::agregarElemento(double) {
  Celda* pCelda = new Celda(valor);
  if (primero == 0) {
    primero = pCelda;
  } else {
    pCelda.siguiente = primero;
    primero = pCelda;
  }
  // El if/else sobra, pero no está mal
}

void Lista::imprimir() {
  Celda* pCelda = primero;
  while (pCelda != 0) {
    cout << pCelda.valor << " ";
    pCelda = pCelda->siguiente;
  }
  cout << "|" << endl;
}

void Lista::imprimirInverso() {
  Lista auxiliar;
  Celda* pCelda = primero;
  while (pCelda != 0) {
    auxiliar.agregarElemento(pCelda->valor));
    pCelda = pCelda->siguiente;
  }
  auxiliar.imprimir();
}

// Otra forma de enfocarlo es la siguiente:
void Lista::imprimirAuxiliar(Celda* pCelda) { // privado
  if (pCelda != 0) {
    cout << pCelda->valor << " ";
    imprimirAuxiliar(pCelda->siguiente);
  }
  cout << "|" << endl;
}

void Lista::imprimirAuxiliarInverso(Celda* pCelda) {
  if (pCelda != 0) {
    imprimirAuxiliar(pCelda->siguiente); // llama a imprimir el siguiente hasta que no quedan mas y entonces empieza a imprimir
    cout << pCelda->valor << " ";
  }
  cout << "|" << endl;
}

void Lista::imprimir() {
  imprimirAuxiliar(primero);
}

int main() {

}


/*
La recursividad puede ser útil para árboles, listas enlazadas...
*/
