class Entero {
public:
  int* v;
public:
  Entero(int i = 0) {
    v = new int;
    *v = i;
  }
  nEntero() {
    delete v;
  }
  void set(int i) {
    *v = i;
  }
  int get()const {
    return *v;
  }
  // Añadido
}

// Código
Entero Doble(Entero e) { // Copia de argumento -> constructor de copia
  return e.get()*2; // get devuelve un int -> get return Entero
  // sobrecarga operator*(Entero, int)
}

// main
Entero x(5), y;
y = Doble(x); // memoria dinamica -> operator=
cout << "Resultado: " << y << endl; // operator<<



// Solución
// Constructor de copia
Entero::Entero(const Entero& otro) {
  v = new int;
  *v = *(otro.v);
}

// Operador de asignación
const Entero& Entero::operator=(const Entero& otro) {
  if (this != &otro) {
    delete v;
    v = new int;
    *v = *(otro.v);
    return *this;
  }
}

// Operador por
Entero Entero::operator*(int valor)const {
  Entero resultado(*v * valor);
  return resultado;
}

// Operador de salida (Función amiga)
ostream& operator<<(ostream& flujo, Entero& otro)const {
  flujo << *(otro.v) << endl;
  return flujo;
}
