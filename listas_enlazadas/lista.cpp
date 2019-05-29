#include "lista.h"

int Lista::longitud()const {
  int longitud = 0;
  Zelda* pZelda = primero;
  while (pZelda != nullptr) {
    longitud++;
    pZelda = pZelda->siguiente;
  }
  return longitud;
}

void Lista::agregarInicio(double valor) {
  Zelda* pZelda = nullptr;
  pZelda = new Zelda(valor);
  if (primero == nullptr) {
    primero = pZelda;
  } else {
    pZelda->siguiente = primero;
    primero = pZelda;
  }
}

Zelda* Lista::obtenerUltimo()const {
  Zelda* pUltimo = primero;
  if (pUltimo != nullptr) {
    while (pUltimo->siguiente != nullptr) {
      pUltimo = pUltimo->siguiente;
    }
  }
  return pUltimo;
}

void Lista::agregarFinal(double valor) {
  // Creamos zelda nueva
  Zelda *pZelda = new Zelda(valor);

  // Si la lista está vacía, enlazar con primero
  if (primero == nullptr) {
    // Esto no sería necesario con la implementación de obtenerUltimo()
    primero = pZelda;
  } else {
    // Enlazamos ultimo con nuevo elemento
    Zelda* previa = obtenerUltimo();
    previa.siguiente = pZelda;
  }
}

// Recomendable que esté en utils.cpp
std::ostream& operator<<(std::ostream& fsalida, const Lista& lista) {
  Zelda* pZelda = lista.primero;
  while (pZelda != nullptr) {
    fsalida << pZelda->valor << " ";
    pZelda = pZelda->siguiente;
  }
  fsalida << "|" << std::endl;
  return fsalida;
}

void lista::liberarEspacio() {
  Zelda* pZelda = primero, *pSiguiente;
  while (pZelda != nullptr) {
    pSiguiente = pZelda->siguiente;
    delete pZelda;
    pZelda = pSiguiente;
  }
  primero = nullptr;
}

void Lista::copiarDatos(const Lista& otra) {
  int longitudOtra = otra.longitud();
  Zelda *pActual, *pPrevia = nullptr, *pOtra = otra.primero;
  for (int i = 0; i < longitudOtra; i++) {
    pActual = new Zelda(pOtra.valor);
    // Si es la primera, enlazar con el dato miembro primero
    if (i == 0) {
      primero = pActual;
    }
    if (pPrevia != 0) {
      pPrevia.siguiente = pActual;
    }
    // Preparar la siguiente iteración
    pOtra = pOtra.siguiente;
    previa = pActual;
  }
}

const Lista& lista::operator=(const Lista& otra) {
  if (this != &otra) {
    liberarEspacio();
    copiarDatos(otra);
  }
  return  *this;
}

// Hacer otra implementación
Lista Lista::operator+(const Lista& otra)const {
  lista copiaThis(*this);
  lista copiaOtra(otra);
  Zelda* pUltima = copiaThis.obtenerUltimo();

  pUltima->siguiente = copiaOtra.primero;
  copiaOtra.primero = nullptr; // Evita que se borre copiaotra

  return copiaThis;
}

const Lista Lista::operator+=(const Lista& otra) {
  // Si la lista está vacía
  if (primero == nullptr) {
    copiarDatos(otra);
  } else {
    Lista copiaOtra(otra);
    Zelda *pUltimo = obtenerUltimo();
    pUltimo.siguiente = copiaOtra.primero;
    // Hacemos que copia otra sea una lista vacía
    copiaOtra.primero = nullptr; // Evita que se borren los datos
  }
  return *this;
}

// Ejercicio 1 (2014)
Lista* particionar(int tam) {
  // Calculamos el numero de fragmentos
  int longitudThis = longitud();
  int trozos = longitudThis/tam;
  if (longitudThis % tam != 0) {
    trozos++;
  }
  // Reservar el array de objetos a devolver
  Lista* resultado = new Lista[trozos];
  Zelda* pZelda = primero;
  Zelda* pAuxiliar;
  for (int i = 0; i < trozos; i++) {
    // pZelda será el puntero inicial del trozo
    resultado[i].primero = pZelda;
    // Avanzar hasta la ultima Zelda del trozo
    for (int j = 0; j < tam-1 && pZelda->siguiente != 0; j++) {
      pZelda = pZelda->siguiente;
    }
    // Salvamos el puntero a la primera Zelda del siguiente trozo
    pAuxiliar = pZelda->siguiente;
    pZelda->siguiente = nullptr;
    pZelda = pAuxiliar;
  }
  primero = 0;
  return resultado;
}
