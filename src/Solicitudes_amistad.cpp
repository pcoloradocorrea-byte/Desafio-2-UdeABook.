#include "Solicitudes_amistad.h"
#include "Medidor.h"

Solicitudes_amistad::Solicitudes_amistad() {
}

void Solicitudes_amistad::agregar(const SolicitudAmistad& solicitud) {
    pendientes.agregar(solicitud);
}

void Solicitudes_amistad::quitar(unsigned int posicion) {
    pendientes.quitarEn(posicion);
}

bool Solicitudes_amistad::existe(const string& emisor, const string& receptor) const {
    for (unsigned int i = 0; i < pendientes.getTamano(); i++) {
        Medidor::contar();
        if (pendientes[i].obtenerEmisor() == emisor && pendientes[i].obtenerReceptor() == receptor) {
            return true;
        }
    }
    return false;
}

unsigned int Solicitudes_amistad::cantidad() const {
    return pendientes.getTamano();
}

SolicitudAmistad& Solicitudes_amistad::obtener(unsigned int posicion) {
    return pendientes[posicion];
}

unsigned long Solicitudes_amistad::memoriaUsada() const {
    return sizeof(Solicitudes_amistad) - sizeof(Lista<SolicitudAmistad>) + pendientes.memoriaUsada();
}