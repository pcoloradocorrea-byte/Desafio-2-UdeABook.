#include <iostream>
#include "UdeABook.h"

using namespace std;

int main() {
    UdeABook red;

    red.agregarUsuario(Usuario("juanito76", "1990-05-10", "juan@mail.com", "juan.jpg", "Medellin", "Colombia", "2024-01-01"));
    red.agregarUsuario(Usuario("maria22", "1995-03-02", "maria@mail.com", "maria.jpg", "Bogota", "Colombia", "2024-01-02"));
    red.agregarUsuario(Usuario("pedro10", "1992-07-21", "pedro@mail.com", "pedro.jpg", "Cali", "Colombia", "2024-01-03"));
    red.agregarUsuario(Usuario("laura99", "1999-11-15", "laura@mail.com", "laura.jpg", "Quito", "Ecuador", "2024-01-04"));

    red.prepararAmigos();

    Amigos& amigos = red.obtenerAmigos();
    amigos.agregarAmistad(0, 1);
    amigos.agregarAmistad(0, 2);
    amigos.agregarAmistad(1, 3);
    amigos.agregarAmistad(2, 3);

    cout << "Posicion de pedro10: " << red.buscarUsuario("pedro10") << endl;
    cout << "Amigos de juanito76: " << amigos.cantidadAmigos(0) << endl;

    Lista<unsigned int> candidatos;
    Lista<unsigned int> comunes;
    amigos.sugerencias(0, candidatos, comunes);

    cout << "Sugerencias para juanito76:" << endl;
    for (unsigned int i = 0; i < candidatos.getTamano(); i++) {
        cout << red.obtenerUsuario(candidatos[i]).getNombreUsuario()
        << " (" << comunes[i] << " amigos en comun)" << endl;
    }

    return 0;
}
