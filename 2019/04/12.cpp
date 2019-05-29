// Viernes 12 de abril de 2019
// Ejercicio 17 parte 2
// Hay una librería que es stl

// En Matriz2D.cpp
void copiarDatos(int **origen, int **destino,
                 int numFilas, int numColumnas,
                 int fOriIni = 0, int cOriIni = 0,
                 int fDestIni = 0, int cDestIni = 0) {
  // Habría que hacer comprobaciones, pero al ser un método privado, no need
  for (int i=0; i<numFilas; i++) {
    for (int j=0; j<numColumnas; j++) {
      destino[fDestIni+i][cDestIni+j] = origen[fOriIni+i][cOriIni+j];
    }
  }
}

// Ejemplos de ejercicios de examen
/*
  Tenemos un puntero Imagen que apunta a una lista de celdas enlazadas, que
  contienen un array de longitud c y un puntero a la siguiente celda
  ¿Constructor por defecto?
*/
class Zelda {
private:
  int *datos;
  Zelda *siguiente;
public:
  // Constructor por defecto
  Zelda() {
    datos = nullptr;
    siguiente = nullptr;
  }
};

class Imagen {
private:
  Zelda *imag;
public:
  // Constructor por defecto
  Imagen() {
    imag = nullptr;
  }
};

// Septiembre 2007
class Cadena {
public:
  char *cad; // Array de caracteres (cadenas tipo c con '\0')
  ...
  Cadena() {
    cad = new char[100];
  }
  Cadena(char *contenido) {
    cad = new char[strlen(contenido) + 1];
    strcpy(cad, contenido);
  }
  void asignar(char *contenido) {
    if (cad == nullptr) {
      cad = new char[strlen(contenido + 1)];
    }
    strcpy(cad, contenido);
  }
};

class Conjunto {
public:
  Cadena *cadena; // Array de objetos Cadena
  int numero;
  ...
  Conjunto() {
    cadena = nullptr;
    numero = 0;
  }
  Conjunto(int numero, char *cadenas[]) {
    this->numero = numero;
    cadenas = new Cadena[numero];
    for (int i = 0; i < numero; i++) {
      cadena[i].asignar(cadenas[i]);
    }
  }
};

/*
Se puede preguntar si es necesario implementar un destructor: Solo es necesario
si en los datos de la clase aparece un puntero
*/

// Septiembre 2012
class Matriz {
private:
  int nFilas;
  int *nColumnas; // = {3, 2, 5, 2} // Puede ser distinto para cada fila
  double **datos;
public:
  // Constructores
  Matriz() {
    nFilas = 0;
    nColumnas = nullptr;
    datos = nullptr;
  }
  Matriz(int nFilas, int longitudes[]) {
    this->nFilas = nFilas;
    nColumnas = new int[nFilas];
    datos = new double*[nFilas];
    for (int i=0; i<nFilas; i++) {
      nColumnas[i] = longitudes[i];
      datos[i] = new double[longitud[i]];
    }
  }
  // Destructor
  ~Matriz() {
    liberar();
  }

  void liberar() {
    for (int i = 0; i < nFilas; i++) {
      delete[] datos[i];
    }
    delete[] nColumnas;
    delete[] datos;

  }
};

/*
MINI-GUIÓN DE LAS COSAS QUE VAMOS A VER A TRAVÉS DE LA SEMANA QUE VIENE
  En el video tenemos de ejemplo Listas Enlazadas, pero en clase vamos a montar
  la clase Polilinea, que depende de la clase Punto
*/
class Punto {
  double x, y;
  ...
};

class Polilinea {
  Punto *puntos;
  int numeroVertices;
  int espacioReservado;
  ...
};
