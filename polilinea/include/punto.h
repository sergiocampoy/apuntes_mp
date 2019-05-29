#ifndef PUNTO_H_
#define PUNTO_H_

class Punto {
private:
  // Datos miembro para las coordenadas del punto
  double x, y;
public:
  // Constructores
  inline Punto() {
    x = 0; y = 0;
  }
  inline Punto(double x, double y) {
    this->x = x;
    this->y = y;
  }

  // Métodos get
  inline double getX()const {
    return x;
  }
  inline double getY()const {
    return y;
  }

  // Métodos set
  inline void asignarX(double x) {
    this->x = x;
  }
  inline void asignarY(double y) {
    this->y = y;
  }

  // Método para mostrar
  inline void mostrar()const {
    std::cout << "(" << x << ", " << y << ")" << std::endl;
  }
};

#endif
