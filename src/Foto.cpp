#include "Foto.h"
#include <iostream>

//inicializar constructores
Foto::Foto() : fechaCaptura(""), tamano(0), ruta(""), likes(0) {
}

Foto::Foto(const string& fechaCaptura, unsigned short tamano, const string ruta)

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