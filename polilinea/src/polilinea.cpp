#include "polilinea.h"

Polilinea::Polilinea() {
  // Se inicializa todo a 0
  puntos = nullptr;
  numeroVertices = 0;
  espacioReservado = 0;
}

Polilinea::Polilinea(int espacioAlmacenamiento) {
  // Reserva de espacio
  puntos = reservarEspacio(espacioAlmacenamiento);

  //Asignar datos miembro
  numeroVertices = 0;
}

Polilinea::Polilinea(double x, double y) {
  puntos = reservarEspacio(1);

  // Asignar coordenadas
  puntos[0].asignarX(x);
  puntos[0].asignarY(y);

  numeroVertices = 1;
  espacioReservado = 1;
}

Punto* Polilinea::reservarEspacio(int dimension) {
  Punto* espacio = nullptr;
  if (dimension > 0) {
    espacio = new Punto[dimension];
    espacioReservado = dimension;
  }
  return espacio;
}

Punto Polilinea::obtenerVertice(int indice)const {  // Necesita <stdexcept>
  if (indice < 0 || indice >= numeroVertices) {
    throw invalid_argument("Indice inválido en Polilinea::obtenerVertice");
  }
  return puntos[indice];
}

int Polilinea::buscarVertice(double x, double y)const {
  int posicion = -1;
  bool encontrado = false; // Nos lo podemos ahorrar, pero da igual
  for (int i = 0; i < numeroVertices && !encontrado; i++) {
    if (puntos[i].obtenerX() == x && puntos[i].obtenerY() == y) {
      encontrado = true;
      posicion = i;
    }
  }
  return posicion;
}

bool Polilinea::asignarVertice(int indice, double x, double y) {
  bool resultado = false;
  if (indice >= 0) {
    resultado = true;
    // Hay espacio
    if (indice < espacioReservado) {
      puntos[indice].asignarX(x);
      puntos[indice].asignarY(y);
      if (indice >= numeroVertices) {
        numeroVertices = indice + 1;
      }

    } else {
      // No hay espacio
      Punto* nuevoPuntos = reservarEspacio(indice + BLOQUE);
      for (int i = 0; i < numeroVertices; i++) {
        nuevoPuntos[i].asignarX(puntos[i].obtenerX());
        nuevoPuntos[i].asignarY(puntos[i].obtenerY());

        // Valdría esto?
     // nuevoPuntos[i] = puntos[i]; // Operador de asignación
        // Como punto no tiene memoria dinámica, esto es válido
        // NO sería correcto en cualquier clase con memoria dinámica,
        // a menos que el = esté sobrecargado (SPOILER)

        // Si Puntos usara memoria dinámica, lo que pasaría es que los punteros
        // apuntarían al mismo objeto, no se duplica
      }
      nuevoPuntos[indice].asignarX(x);
      nuevoPuntos[indice].asignarY(y);
      numeroVertices = indice + 1;
      // Liberamos la memoria previa
      delete[] puntos;
      puntos = nuevoPuntos;
    }
  }
  return resultado;
}

bool Polilinea::insertarVertice(int indice, double x, double y) {
  bool resultado = false;
  if (indice >= 0 && indice < numeroVertices) {
    resultado = true;

    // Hay espacio
    if (espacioReservado > numeroVertices) {
      // Realojar los vértices desde indice + 1 en adelante

      for (int i = numeroVertices; i > indice; i--) {
        puntos[i].asignarX(puntos[i-1].obtenerX());
        puntos[i].asginarY(puntos[i-1].obtenerY());
      }
      puntos[indice].asignarX(x);
      puntos[indice].asignarY(y);
    } else {
      Punto* nuevoPuntos = reservarEspacio(espacioReservado+BLOQUE);

      // Copiar datos desde 0 hasta indice -1
      for (int i = 0; i < indice; i++) {
        nuevoPuntos[i].asignarX(puntos[i].obtenerX());
        nuevoPuntos[i].asignarY(puntos[i].obtenerY());
      }

      // Insertamos el dato
      nuevoPuntos[indice].asignarX(x);
      nuevoPuntos[indice].asginarY(y);

      // Copiamos desde indice+1 en adelante
      for (int i = indice; i < numeroVertices; i++) {
        nuevoPuntos[i+1].asignarX(puntos[i].obtenerX());
        nuevoPuntos[i+1].asignarY(puntos[i].obtenerY());
      }

      // Liberar espacio previo y asignar nuevoPuntos a puntos
      delete[] puntos;
      puntos = nuevoPuntos;
    }
    numeroVertices++;
  }
  return resultado;
}

bool Polilinea::borrarVertice(int indice) {
  bool resultado = false;
  if (indice >= 0 && indice < numeroVertices) {
    resultado = true;
    for (int i = indice; i < numeroVertices - 1; i++) {
      puntos[i].asignarX(puntos[i+1].obtenerX());
      puntos[i].asignarY(puntos[i+1].obtenerY());
    }
    numeroVertices = numeroVertices - 1;
  }
  return resultado;
}

void Polilinea::mostrar()const {
  cout << "Contenido obtejo clase Polilinea..." << endl;
  cout << "Vértices: " << numeroVertices << endl;
  cout << "Espacio Reservado: " << espacioReservado << endl;
  // Bucle de recorrido
  for (int i = 0; i < numeroVertices; i++) {
    cout << "(" << i << "):";
    obtenerVertice(i).mostrar();
  }
  cout << "..........................................................." << endl;
}

Polilinea* Polilinea::unionOP(const Polilinea& otra)const {
  Polilinea* resultado = nullptr;
  resultado = new Polilinea(numeroVertices + otra.numeroVertices + BLOQUE);

  // Copia de datos (this)
  for (int i = 0; i < numeroVertices; i++) {
    resultado->asignarVertice(i, obtenerVertice(i).obtenerX(),
                                 obtenerVertice(i).obtenerY());
  }
  for (int i = 0; i < otra.numeroVertices; i++) {
    resultado->asignarVertice(numeroVertices+i, obtenerVertice(i).obtenerX(),
                                                obtenerVertice(i).obtenerY());
  }
  resultado->numeroVertices = numeroVertices + otra.numeroVertices;

  return resultado;
}

Polilinea* Polilinea::interseccionOP(const Polilinea& otra)const {
  Polilinea* resultado = nullptr;
  resultado = new Polilinea(BLOQUE); // Crea 1 objeto de Polilinea
  Punto vertice;
  int pos;
  for (int i = 0; i < numeroVertices; i++) {
    vertice = obtenerVertice(i);
    pos = otra.buscarVertice(vertice.obtenerX(), vertice.obtenerY());
    if (pos != -1) {
      resultado->asignarVertice(numeroVertices, vertice.obtenerX(),
                                                vertice.obtenerY());
    }
  }
  return resultado;
}

void Polilinea::liberarEspacio() {
  delete[] puntos;
}
