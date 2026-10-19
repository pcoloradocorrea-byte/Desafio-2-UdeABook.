#include "SolicitudAmistad.h"

//se crea una solicitud vacia
SolicitudAmistad::SolicitudAmistad() { emisor = ""; receptor = ""; fecha = "";
}



//guardamos quien envia, quien recibe y la fecha
SolicitudAmistad::SolicitudAmistad(const string& emisor, const string& receptor, const string& fecha) {
    this->emisor = emisor;
    this->receptor = receptor;
    this->fecha = fecha;
}



string SolicitudAmistad::obtenerEmisor() const {
    return emisor;
}



string SolicitudAmistad::obtenerReceptor() const {
    return receptor;
}

string SolicitudAmistad::obtenerFecha() const {
    return fecha;
}



unsigned long SolicitudAmistad::memoriaUsada() const {
    return sizeof(SolicitudAmistad) + emisor.capacity() + receptor.capacity() + fecha.capacity();
}



