#ifndef MEDIDOR_H
#define MEDIDOR_H

#include <string>
using namespace std;
//Requisito VII
//Se mide las iteraciones
//cada clase reporta reporta lo que ocupa

class Medidor{
private:
    static unsigned int iteraciones;

public:
    static void contar(unsigned int cantidad = 1);
    static void reiniciar();
    static unsigned int obtenerIteraciones();
    static void mostrarReporte(unsigned int memoriaBytes);
};

//¡Cuantos bytes ocupa este elemento?
//
template <typename T>

unsigned long memoriaDe(const T& elemento) { //No modificamos el elemento
    return elemento.memoriaUsada(); //Se le pregunta al objeto cuanto ocupa y devuelve
}
inline unsigned long memoriaDe(const unsigned int&){
    return sizeof(unsigned int); //Retorna cuantos bytes tiene un tipo
}

inline unsigned long memoriaDe(const string& texto){
    return sizeof(string) + texto.capacity(); //calcular memoria de un string
}

#endif // MEDIDOR_H
