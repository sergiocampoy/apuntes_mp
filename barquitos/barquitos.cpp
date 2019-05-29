#include "barquitos.h"

// primer apartado

Barquito::Barquito(int _numeroFilas, int _numeroColumnas) {
  numeroFilas = _numeroFilas;
  numeroColumnas = _numeroColumnas;
  // reservar espacio
  reservarEspacio();
  inicializarAgua();
}

void Barquito::reservarEspacio() {
  tablero = new int*[numeroFilas];
  for (int i = 0; i < numeroFilas; i++) {
    tablero[i] = new int[numeroColumnas];
  }
}

void inicializarAgua() {
  for (int i = 0; i < numeroFilas; i++)
    for (int j = 0; j < numeroColumnas; j++)
      tablero[i][j] = AGUA;
}

Barquito::~Barquito() {
  liberarEspacio();
}

void Barquito::liberarEspacio() {
  if (tablero != nullptr) { // No es 100% necesaria
    for (int i = 0; i < numeroFilas; i++) {
      // Borramos las columnas
      delete[] tablero[i];
    }
    delete[] tablero;
  }
  tablero = nullptr;
}

// Fin del primer apartado
// segundo apartado
Barquito::Barquito(const Barquito& otro) {
  numeroFilas = otro.numeroFilas;
  numeroColumnas = otro.numeroColumnas;
  reservarEspacio();
  copiarTablero(otro.tablero);
}

void Barquito::copiarTablero(const int** otro) {
  for (int i = 0; i < numeroFilas; i++)
    for (int j = 0; j < numeroColumnas; j++)
      tablero[i][j] = otro[i][j];
}

const Barquito& operator=(const Barquito& otro) {
  if (*this != otro) {
    liberarEspacio();
    numeroFilas = otro.numeroFilas;
    numeroColumnas = otro.numeroColumnas;
    reservarEspacio();
    copiarTablero(otro.tablero);
  }
  return *this;
}
// Fin del segundo apartado
// tercer apartado
bool Barquito::chequearPosicionado(char fila, int columna, int tam, char direccion) {
  bool resultado = true;
  int numeroFila = fila - 'A';
  int numeroColumna = columna - 1;

  // determinamos si la posición es válida
  if (numeroFila < 0 || numeroFila >= numeroFilas ||
      numeroColumna < 0 || numeroColumna >= numeroColumnas) {
    resultado = false;
  } else { // estamos dentro del tablero
    int columnaFinal = 0, int filaFinal = 0;
    if (direccion == HORIZONTAL) {
      columnaFinal = numeroColumna + tam;
    } else {
      filaFinal = numeroFila + tam;
    }
    if (columnaFinal >= numeroColumnas || filaFinal >= numeroFilas) {
      resultado = false;
    }
    ...
    // Falta comprobar que no se choque con otros barcos
  }
  return resultado;
}

// Fin del tercer apartado
// cuarto apartado
void Barquito::posicionarBarco(int tam) {
  bool insertado = false;
  while (!insertado) {
    int numeroFila = generarAleatorio(0, numeroFilas - 1);
    char fila = 'A' + numeroFila;
    int numeroColumna = generarAleatorio(1, numeroColumnas);
    int valorDireccion = generarAleatorio(0, 1);
    char direccion = valorDireccion ? HORIZONTAL : VERTICAL;
    if (chequearPosicionado(fila, numeroColumna, tam, direccion)) {
      insertado = true;
    }
    if (insertado) {
      insertarBarco(numeroFila, numeroColumna - 1, tam, direccion);
    }
  }
}
// fin del cuarto apartado
// ejercicio 3
bool Barquito::escribir(const char* nombreArchivo) {
  bool resultado = true;
  ofstream archivo(nombreArchivo, ios::binary);
  if (!archivo.is_open()) {
    resultado = false;
  } else {
    archivo << IDENTIFICADOR << endl;
    archivo << numeroFilas << " " << numeroColumnas << endl;

    for (int i = 0; i < numeroFilas; i++) {
      for (int j = 0; j < numeroColumnas; j++) {
        archivo.write((char*)(&tablero[i][j]), sizeof(int));
        // archivo.read(char*, "sizeof()") para leer binario
      }
    }
    archivo.close();
  }
}

////////// main

const string Barquito::IDENTIFICADOR = "MP-BARQ-V1.0";
