#ifndef SOLICITUDES_AMISTAD_H
#define SOLICITUDES_AMISTAD_H

#include "Lista.h"
#include "SolicitudAmistad.h"

class Solicitudes_amistad {
private:
    Lista<SolicitudAmistad> pendientes;

public:
    Solicitudes_amistad();

    void agregar(const SolicitudAmistad& solicitud);
    void quitar(unsigned int posicion);
    bool existe(const string& emisor, const string& receptor) const;
    unsigned int cantidad() const;
    SolicitudAmistad& obtener(unsigned int posicion);

    unsigned long memoriaUsada() const;
};

#endif // SOLICITUDES_AMISTAD_H
