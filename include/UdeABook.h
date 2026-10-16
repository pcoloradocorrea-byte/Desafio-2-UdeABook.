#ifndef UDEABOOK_H
#define UDEABOOK_H

#include "Lista.h"
#include "Usuario.h"
#include "Mensaje.h"
#include "Amigos.h"
#include "Solicitudes_amistad.h"

class UdeABook {
private:
    Lista<Usuario> usuarios;
    Lista<Mensaje> mensajes;
    Solicitudes_amistad solicitudes;
    Amigos amigos;

public:
    UdeABook();

    void agregarUsuario(const Usuario& usuario);
    void agregarMensaje(const Mensaje& mensaje);
    void prepararAmigos();

    int buscarUsuario(const string& nombreUsuario) const;
    unsigned int cantidadUsuarios() const;
    Usuario& obtenerUsuario(unsigned int posicion);

    Solicitudes_amistad& obtenerSolicitudes();
    Amigos& obtenerAmigos();
    Lista<Mensaje>& obtenerMensajes();

    unsigned long memoriaUsada() const;
};

#endif
