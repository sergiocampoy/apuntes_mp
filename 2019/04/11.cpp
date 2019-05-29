// matriz2D.cpp
...
  // El objeto this va a ser idéntico a otra al final de la ejecución
  void Matriz2D::copiar(const Matriz2D &otra) {
    liberar();
    numeroFilas = otra.numeroFilas;
    numeroColumnas = otra.numeroColumnas;
    // Reservar espacio (muy buen candidato para ser un método auxiliar privado)
    matriz = new int *[numeroFilas];
    for (int i = 0; i < numeroFilas; i++) {
      matriz[i] = new int [numeroColumnas];
    }
    // Copiar los datos de otra (otro candidato a método auxiliar privado)
    for (int i = 0; i < numeroFilas; i++) {
      for (int j = 0; j < numeroColumnas; j++) {
        matriz[i][j] = otra.matriz[i][j];
      }
    }
  }

  Matriz2D* Matriz2D::extraerSubmatriz(int filIni, int colIni
                                       int filFin, int colFin) {
    Matriz2D *resultado = nullptr;
    // Comprobar la validez de los argumentos
    if (filIni < numeroFilas && colIni < numeroColumnas &&
        filFin < numeroFilas && colFin < numeroColumnas &&
        filIni >= 0 && colIni >= 0 && filFin >= 0 && colFin >= 0 &&
        filIni <= filFin && colIni <= colFin) {
      resultado = new Matriz2D(filFin - filIni + 1, colFin - colIni + 1);
      for (int i = 0; i < resultado->numeroFilas; i++) {
        for (int j = 0; j < resultado->numeroColumnas; j++) {
          resultado->matriz[i][j] = matriz[filIni + i][colIni + j];
        }
      }
    }
    return resultado;
  }

  // Este método se puede implementar de múltiples maneras
  void Matriz2D::eliminarFila(int fila)
  for (int i=0; i<numeroFilas; i++) {
    if (0 <= fila && fila < numeroFilas) {
      int **matrizNueva = new int *[numeroFilas - 1];
      for (int i = 0; i < numeroFilas - 1; i++) {
        matrizNueva[i] = new int[numeroColumnas];
      }
      // Copia de filas previas (hasta fila)
      for (int i = 0; i < fila; i++) {
        for (int i = 0; j < numeroColumnas; j++) {
          matrizNueva[i][j] = matriz[i][j];
        }
      }
      // Copia del resto de filas
      for (int i = fila + 1; fila < numeroFilas; i++) {
        for (int j = 0; j < numeroColumnas; j++) {
          matrizNueva[i - 1][j] = matriz[i][j];
        }
      }
      liberar();
      matriz = matrizNueva;
      numeroFilas--;
    }
  }

  void Matriz2D::eliminarColumna(int columna) {
    if (0 <= columna && columna <= numeroColumnas) {
      // int **matrizNueva = reservar(numeroFilas, numeroColumnas - 1);
      int **matrizNueva = new int *[numeroFilas];
      for (int i = 0; i < numeroFilas; i++) {
        matrizNueva[i] = new int[numeroColumnas - 1];
      }
      // Copia de las columnas previas (hasta columna)
      for (int i = 0; i < numeroFilas; i++) {
        for (int j = 0; j < columna; j++) {
          matrizNueva[i][j] = matriz[i][j];
        }
      }
      // Copia del resto de columnas
      for (int i = 0; i < numeroFilas; i++) {
        for (int j = columna + 1; j < numeroColumnas; j++) {
          matrizNueva[i][j - 1] = matriz[i][j];
        }
      }
      liberar();
      matriz = matrizNueva;
      numeroColumnas--;
    }
  }

  // Destructor
  Matriz2D::~Matriz2D() {
    if (matriz != nullptr) {
      liberar();
    }
  }

// Ejemplo
metodo(...) {
  ...
  Matriz2D obj1;
  Matriz2D *obj2 = new Matriz2D(...);
  ...
// obj1 se destruye automática (algo así como el return 0 del main)
// obj2 NO se destruye, y es necesario que sea destruido después por nosotros
}

/*
  El método reservar() se ha utilizado en el constructor, copiar, eliminarFila, eliminarColumna
  Quizás sea buena idea ipleentarlo como una función auxiliar privada
*/
  int** Matriz2D::reservar(int numFilas, int numColumnas) {
    int **espacio = new int *[numFilas];
    for (int i = 0; i < numFilas; i++) {
      espacio[i] = new int[numColumnas];
    }
    return espacio;
  }

//////////////////////////////////////////////////////////////
/////////////////////////// INCISO ///////////////////////////
//////////////////////////////////////////////////////////////

// En Matriz2D.h
void copiarDatos(int **origen, int **destino,
                 int numFilas, int numColumnas,
                 int fOriIni = 0, int cOriIni = 0,
                 int fDestIni = 0; int cDestIni = 0);
// Esto se llama: parámetros con valor por defecto

// Posibles llamadas en el main
copiarDatos(ori, dest, 4, 3); // Copia desde 0, 0 a 0, 0
copiarDatos(ori, dest, 4, 3, 1, 2); // Copia desde 1, 2
copiarDatos(ori, dest, 4, 3, 0, 0, 1, 2); // Copia a 1, 2
copiarDatos(ori, dest, 4, 3,  ,  , 1, 2); // May work

//////////////////////////////////////////////////////////////
/////////////////////// FIN DEL INCISO ///////////////////////
//////////////////////////////////////////////////////////////

// Mismo ejercicio pero con una matriz de punteros y una
// mega-matriz donde se almacenan todos los valores

// En matriz2D.cpp (otro)
...
  int** Matriz2D::reservar(int numFilas, int numColumnas) {
    int **espacio = new int *[numFilas];
    espacio[0] = new int[numFilas*numColumnas];

    // Enlazar los punteros al omianzo de las filas
    for (int i = 1; i < numColumnas; i++) {
      espacio[i] = espacio[n-1] + numColumnas;
    }
    return espacio;
  }

  void Matriz2D::liberar() {
    delete []matriz[0];
    delete []matriz;
  }

/*
  En este caso da igual cómo se reservan los datos, dado que
  se accede a los datos de la misma manera.
  Lo único que varía son los métodos reservar, liberar y
  quizás copiar.
  Lo mejor es que la capa de más alto nivel se lo más desligada
  a la capa de bajo nivel posible usando, por ejemlo, métodos get
*/
