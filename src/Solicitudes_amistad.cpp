#include "Solicitudes_amistad.h"
#include "Medidor.h"

Solicitudes_amistad::Solicitudes_amistad() {
}


//se agrega una solicitud de amistad enviada a pendientes
void Solicitudes_amistad::agregar(const SolicitudAmistad& solicitud) {
    pendientes.agregar(solicitud);
}


//se elimina una solicitud de amistal al momento de aceptarla
void Solicitudes_amistad::quitar(unsigned int posicion) {
    pendientes.quitarEn(posicion);
}



//revisa si hay una solicitud pendiente del emisor al receptor
bool Solicitudes_amistad::existe(const string& emisor, const string& receptor) const {
    for (unsigned int i = 0; i < pendientes.getTamano(); i++) {
        Medidor::contar();
        if (pendientes[i].obtenerEmisor() == emisor && pendientes[i].obtenerReceptor() == receptor) {
            return true; //
        }
    }
    return false;
}


//obtenemos la cantidad de solicitudes pendientes
unsigned int Solicitudes_amistad::cantidad() const {
    return pendientes.getTamano();
}


//obtenemos una solicitud de amistad pendiente
SolicitudAmistad& Solicitudes_amistad::obtener(unsigned int posicion) {
    return pendientes[posicion];
}

unsigned long Solicitudes_amistad::memoriaUsada() const {
    return sizeof(Solicitudes_amistad) - sizeof(Lista<SolicitudAmistad>) + pendientes.memoriaUsada();
}