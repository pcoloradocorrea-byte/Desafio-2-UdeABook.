#ifndef MEDIDOR_H
#define MEDIDOR_H

#include <string>

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

#endif // MEDIDOR_H
