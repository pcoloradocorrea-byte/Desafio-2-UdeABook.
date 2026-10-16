#include "Album.h"

Album::Album() : nombre(""), ruta(""), privacidad(PUBLICO) {
}

Album::Album(const std::string& nombre, const std::string& ruta, unsigned char privacidad)
    : nombre(nombre), ruta(ruta), privacidad(privacidad) {
}

void Album::agregarFoto(const Foto& foto) {
    fotos.agregar(foto);
}

bool Album::esVisiblePara(bool esDueno, bool esAmigo) const {
    if (esDueno) {
        return true;
    }
    if (privacidad == PUBLICO) {
        return true;
    }
    if (privacidad == AMIGOS) {
        return esAmigo;
    }
    return false;
}

unsigned int Album::cantidadFotos() const {
    return fotos.getTamano();
}

Foto& Album::getFoto(unsigned int posicion) {
    return fotos[posicion];
}

std::string Album::getNombre() const {
    return nombre;
}

std::string Album::getRuta() const {
    return ruta;
}

unsigned char Album::getPrivacidad() const {
    return privacidad;
}

unsigned long Album::memoriaUsada() const {
    return sizeof(Album) - sizeof(Lista<Foto>) + nombre.capacity() + ruta.capacity()
    + fotos.memoriaUsada();
}