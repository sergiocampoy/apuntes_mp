#ifndef POLILINEA_H_
#define POLILINEA_H_

class Polilinea {
private:
  // Constante estática que está asociada a la clase entera
  static const int BLOQUE = 10;

  // Datos miembro
  Punto *puntos;        // Puntero al array
  int numeroVertices;   // Número de vértices
  int espacioReservado; // Espacio reservado

  // Métodos privados
  Punto* reservarEspacio(int dimension);
  void liberarEspacio();

public:
  // Constructores
  Polilinea();
  Polilinea(int espacioAlmacenamiento);
  Polilinea(double x, double y);

  // Destructor
  ~Polilinea() {
    liberarEspacio();
  }

  // Interfaz básica
  inline int obtenerNumeroVertices()const {
    return numeroVertices;
  }
  inline int obtenerEspacioReservado()const {
    return espacioReservado;
  }
  Punto obtenerVertice(int indice)const; // Excepciones :D
  int buscarVertice(double x, double y)const;
  bool asignarVertice(int indice, double x, double y); // Está mal (de momento)
  bool insertarVertice(int indice, double x, double y);
  bool borrarVertice(int n);

  // Interfaz adicional
  void mostrar()const;
  Polilinea* unionOP(const Polilinea& otra)const;
  Polilinea* interseccionOP(const Polilinea& otra)const;
};

#endif
