#ifndef BARQUITOS_H_
#define BARQUITOS_H_

class Barquito {
private:
  int** tablero;
  int numeroFilas;
  int numeroColumnas;
  // Métodos privados
  void reservarEspacio();
  void liberarEspacio();
  void copiarTablero(const int** otro);

  inline int generarAleatorio(int min, int max)const { //(extra)
    return (min + (rand() % (max-min+1));
  }
public:
  // Constantes
  static const int AGUA = 9;
  static const char HORIZONTAL = "H";
  static const char VERTICAL = "V";
  static const string IDENTIFICADOR; // = "MP-BARQ-V1.0";

  // Constructores;
  Barquito(int, int);
  ~Barquito();
  Barquito(const Barquito&);

  // Métodos
  bool chequearPosicionado(char, int, int, char);
  void posicionarBarco(int);
  bool escribir(const char*);

  // Sobrecarga de operadores
  const Barquito& operator=(const Barquito&);
}

#endif
