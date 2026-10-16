#include "Foto.h"
#include <iostream>

//inicializar constructores
Foto::Foto() : fechaCaptura(""), tamano(0), ruta(""), likes(0) {
}

Foto::Foto(const std::string& fechaCaptura, unsigned short tamano, const std::string& ruta)
    : fechaCaptura(fechaCaptura), tamano(tamano), ruta(ruta), likes(0) {
}

//mostrar ruta de la foto
void Foto::mostrarRuta() const{
    cout<< ruta << endl;
}

void Foto::darLike(){
    likes++;
};

void Foto::quitarLike(){
    likes--;
}

string Foto::obtenerFechacaptura() const {
    return fechaCaptura;
}

unsigned short Foto::obtenerTamano() const{
    return tamano;
}

string Foto::obtenerRuta() const{
    return ruta;
}

int Foto::obtenerLikes() const{
    return likes;
}

unsigned long Foto::memoriaUsada() const {
    return sizeof(Foto) + fechaCaptura.capacity() + ruta.capacity();
}