//.h
class Menu {
private:
  // File
  // Guardar, guardar como, abrir, exportar...
  char* titulo; // Encabezado que damos al menu
  char** opc; // Cadenas de longitud variable que describen las opciones
  int nopc; // numero de opciones (util de opc)

  // La trifecta de los métodos privados
  void liberarEspacio();
  void reservar();
  void copiarDatos(const Menu&);
public:
  // Constructores/destructor
  Menu();
};

//.cpp
Menu::Menu() {
  titulo = 0;
  opc = 0;
  nopc = 0;
}

void Menu::liberarEspacio() { // privado
  // liberar el titulo
  delete[] titulo;
  for (int i = 0; i < nopc; i++) {
    // liberar cada una de las opciones
    delete[] opc[i];
  }
  // liberar el array de opciones
  delete[] opc;
}

Menu::~Menu() {
  liberarEspacio();
}

void Menu::copiarDatos(const Menu& otro) { // privado
  // copiar titulo
  titulo = new char[strlen(otro.titulo) + 1]; // longitud + '\0'
  strcpy(titulo, otro.titulo); // copia de arg1 a arg0

  // asignar nopc
  nopc = otro.nopc;
  opc = new char*[nopc];

  // copiamos las opciones
  for (int i = 0; i < nopc; i++) {
    opc[i] = new char[strlen(otro.opc[i]) + 1];
    strcpy(opc[i], otro.opc[i]);
  }
}

Menu::Menu(const Menu& otro) {
  copiarDatos(otro);
}

const Menu& Menu::operator=(const Menu& otro) {
  if (this != &otro) {
    liberarEspacio();
    copiarDatos(otro);
  }
  return *this;
}

void Menu::setTitulo(const char* _titulo) {
  // borrar la memoria asociada al titulo
  delete[] titulo; // no hace falta comprobar si no es null
  titulo = new char[strlen(_titulo) + 1];
  strcpy(titulo, _titulo);
}

void Menu::addOpcion(const char* opcion) {
  char** nuevoOpc = new char*[nopc + 1];
  for (int i = 0; i < nopc; i++) {
    nuevoOpc[i] = opc[i];
  }
  nuevoOpc[nopc] = new char[strlen(opcion) + 1];
  strcpy(nuevoOpc[nopc], opcion);
  delete[] opc;
  opc = nuevoOpc;
  nopc++;
}

ostream& operator<<(ostream& flujo, const Menu& objeto) {
  flujo << "   " << titulo << endl;
  for (int i = 0; i < objeto.nopc; i++) {
    flujo << i+1 << ". " << objeto.opc[i] << endl;
  }
  return flujo;
}

// este es un poco raro
void Menu::operator>>(int& opcion) {
  cout << *this;
  cout << "Seleccione opcion entre 1 y " << nopc << ": ";
  opcion = -1;
  while (opcion < 1 || opcion > nopc) {
    cin >> opcion;
  }
  cout << "La opcion seleccionada es " << opcion << endl;
  // tener cuidado con opcion porque no está basada en 0
}
