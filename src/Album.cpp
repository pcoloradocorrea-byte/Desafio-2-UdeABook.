#include "Album.h"


Album::Album() : nombre(""), ruta(""), privacidad(""){
}

Album::Album(const string& nombre, const string, unsigned char privacidad){

}

void Album::agregarFoto(const Foto& foto){
    foto.agregar(foto);
}

bool Album::Visibilidad(bool beDueno, bool beAmigo) const{
    if (beDueno == true){
        return true;
    }
    elif (privacidad == PUBLICO);{
        return true;
    }
    elif (privacidad == AMIGOS);{
        return beAmigo;
    }
    return false;
}

unsigned int Album::obtenerFoto(unsigned short posicion){
    return Nfotos[posicion]
}

string Album::obtenerNombre() const{
    return nombre;
}

string Album::obtenerRuta() const{
    return ruta;
}

unsigned char Album::obtenerPrivacidad() const{
    return privacidad;
}

//falta memoria