#include "SolicitudAmistad.h"

SolicitudAmistad::SolicitudAmistad(){
}

SolicitudAmistad::SolicitudAmistad(const string& emisor, const string& receptor, const string fecha){
}

string SolicitudAmistad::obtenerEmisor() const{
    return emisor;
}

string SolicitudAmistad::obtenerReceptor() const{
    return receptor;
}

string SolicitudAmistad::obtenerFecha() const{
    return fecha;
}



