#ifndef ALBUM_H
#define ALBUM_H

#include <string>
#include "Foto.h"
#include "Lista.h"

class Album {
private:
    std::string nombre;
    std::string ruta;
    unsigned char privacidad;
    Lista<Foto> fotos;

public:
    enum Privacidad { PUBLICO = 0, PRIVADO = 1, AMIGOS = 2 };

    Album();
    Album(const std::string& nombre, const std::string& ruta, unsigned char privacidad);

    void agregarFoto(const Foto& foto);
    bool esVisiblePara(bool esDueno, bool esAmigo) const;
    unsigned int cantidadFotos() const;
    Foto& getFoto(unsigned int posicion);

    std::string getNombre() const;
    std::string getRuta() const;
    unsigned char getPrivacidad() const;

    unsigned long memoriaUsada() const; //Ver luego
};

#endif