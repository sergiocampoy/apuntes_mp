#include "punto.h"
#include <stdexcept> // Para las excepciones

int main() {
  // Para usar métodos/funciones que pueden lanzar excepciones es necesario:
  try {
    Punto punto = objeto.obtenerVertice(15);
    punto.mostrar();
  } catch (invalid_argument &excepcion) { // Obj de la clase invalid_argument
    cerr << "Problema ejecución: " << excepcion.what() << endl;
  } // Solo se ejecuta en caso de error
}
