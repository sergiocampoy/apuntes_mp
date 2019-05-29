#include <iostream>

class Zelda {
public:
  // Datos miembro
  double valor;
  Zelda* siguiente;

  // Constructor
  Zelda(double valor) {
    this->valor = valor;
    siguiente = nullptr;
  }
};

class Lista {
  friend std::ostream& operator<<(std::ostream&, const Lista&);
private:
  Zelda* primero;
  void liberarEspacio();
  void copiarDatos(const Lista&);
  ...

public:
  // Constructores/destructores
  inline Lista() {
    primero = nullptr;
  }
  inline Lista(const Lista& otra) {
    copiarDatos(otra);
  }
  inline ~Lista() {
    liberarEspacio();
  }
  int longitud()const;
  void agregarInicio(double valor);
  Zelda* obtenerUltimo()const;
  void agregarFinal(double);
  const Lista& operator=(const Lista&);
  Lista operator+(const Lista&)const;
  const Lista operator+=(const Lista&);

  // Ejercicio 1 (2014)
  Lista* particionar(int);
};
