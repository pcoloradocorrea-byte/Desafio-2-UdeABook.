#ifndef MEDIDOR_H
#define MEDIDOR_H

#include <string>
using namespace std;


class Medidor{
private:
    static unsigned int iteraciones;

public:
    static void contar(unsigned int cantidad = 1);
    static void reiniciar();
    static unsigned int obtenerIteraciones();
    static void mostrarReporte(unsigned int memoriaBytes);
};


template <typename T>

unsigned long memoriaDe(const T& elemento) {
    return elemento.memoriaUsada();
}
inline unsigned long memoriaDe(const unsigned int&){
    return sizeof(unsigned int);
}

inline unsigned long memoriaDe(const string& texto){
    return sizeof(string) + texto.capacity();
}

#endif // MEDIDOR_H
