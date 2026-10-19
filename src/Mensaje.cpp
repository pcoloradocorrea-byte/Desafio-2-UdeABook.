#include "Mensaje.h"


Mensaje::Mensaje() : leido(false){

}



Mensaje::Mensaje(const string& emisor, const string& receptor, const string& fecha, const string& texto) : emisor(emisor), receptor(receptor), fecha(fecha), texto(texto), leido(false){

}

//cambiamos el estado del mensaje
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


//nos indica si un mensaje ya fue leido o no
bool Mensaje::estaLeido() const{
    return leido;
}

unsigned long Mensaje::memoriaUsada() const{
    return sizeof(Mensaje) + emisor.capacity() + receptor.capacity() + fecha.capacity() + texto.capacity();
}