#ifndef LISTA_H
#define LISTA_H

#include "Medidor.h"

//Arreglo dinamico que sirve para reemplazar std::vector
//cuando este se llena se duplica
template <typename T> //Esta clase sirve para cualquier tipo de dato

class Lista{
private:
    T* elementos;
    unsigned int tamaño;
    unsigned int capacidad;

    void redimensionar(unsigned int nuevaCapacidad);
public:
    Lista();
    Lista(const Lista<T>& otra);
    ~Lista();
};


#endif // LISTA_H
