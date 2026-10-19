#ifndef AMIGOS_H
#define AMIGOS_H

#include "Lista.h"

class Amigos {
private:
    unsigned int cantidadUsuarios;
    bool* matriz;

public:
    Amigos();
    Amigos(unsigned int cantidadUsuarios);
    Amigos(const Amigos& otro);
    ~Amigos();

    void operator=(const Amigos& otro);

    void agregarAmistad(unsigned int PosicionA, unsigned int b); //Usuario que envia = a y Usuario que recibe = b
    void quitarAmistad(unsigned int PosicionA, unsigned int b);
    bool sonAmigos(unsigned int PosicionA, unsigned int b) const;
    unsigned int cantidadAmigos(unsigned int PosicionA) const;
    unsigned int amigosEnComun(unsigned int PosicionA, unsigned int b) const;
    void sugerencias(unsigned int PosicionA, Lista<unsigned int>& candidatos, Lista<unsigned int>& comunes) const;
    unsigned int obtenerCantidadUsuarios() const;

    unsigned long memoriaUsada() const;
};

#endif // AMIGOS_H
