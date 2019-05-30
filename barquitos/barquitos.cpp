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

void Barquito::leer(const char* nombreArchivo) {
  // crear archivo
  ifstream archivo(nombreArchivo, ios::binary);
  // se comprueba apertura
  if (!archivo.is_open()) {
    cerr << "Error de apertura archivo" << endl;
  } else {
    // lectura cadena mágica
    char cadena[100];
    archivo.getline(cadena, 100);
    // comprobar si es un archivo con el formato
    if (IDENTIFICADOR.compare(cadena) != 0) {
      cerr << "Archivo con formato incorrecto" << endl;
    } else {
      // formato OK
      int nFilas, nColumnas;
      archivo >> nFilas >> nColumnas; // Modo texto
      // Queda un '\n' sin procesar, no podemos comenzar a leer en binario tal cual. Tenemos que descartarlo
      // Se ignoran n caracteres
      archivo.ignore(1); // Necesario siempre
      // se libera espacio
      liberarEspacio();
      // asignar el numero de filas y de columnas
      numeroFilas = nFilas;
      numeroColumnas = nColumnas;
      // reservar espacio
      reservarEspacio();
      // lectura del archivo binario
      int valor;
      for (int i = 0; i < numeroFilas; i++) {
        for (int j = 0; j < numeroColumnas; j++) {
          archivo.read((char*)(&valor), sizeof(int));
          tablero[i][j] = valor;
          // archivo.read((char*)(&tablero[i][j]), sizeof(int));
        }
      }
    }
  }
  archivo.close();
}

//// Extra
// Para hacer un peek del siguiente caracter sin consumirlo
char caracter = archivo.peek(1);
if (caracter == '#') {
  ...
} else {
  ...
}

// ARCHIVOS
// Métodos
ignore(int) // para saltar '\n'
peek(int) // para tratamiento de comentarios/lineas opcionales
is_open() // comprobar si está abierto
close() // cerrar el fichero
getline(char, int))
>>, <<
eof // end of file (como el centinela de los arrays)

// Para binario
flag ios::binary // en la apertura del archivo
read((char*)(&type), sizeof(type))
write((char*)(&type), sizeof(type))



////////// main

const string Barquito::IDENTIFICADOR = "MP-BARQ-V1.0";
