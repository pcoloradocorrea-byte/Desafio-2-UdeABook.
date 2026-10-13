#include "Mensaje.h"


Mensaje::Mensaje() : leido(false){

}

Mensaje::Mensaje(const string& emisor, const string& receptor, const string& fecha, const string& texto) : emisor(emisor), receptor(receptor), fecha(fecha), texto(texto), leido(false){

}

void Mensaje::marcarLeido(){
    leido = true;
}

string Mensaje::obtenerEmisor() const{
    return emisor;
}

string Mensaje::obtenerReceptor() const{
    return receptor;
}

string Mensaje::obtenerFecha() const{
    return fecha;
}

string Mensaje::obtenerTexto() const{
    return texto;
}

bool Mensaje::estaLeido() const{
    return leido;
}

//Memoria