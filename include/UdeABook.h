#ifndef UDEABOOK_H
#define UDEABOOK_H

#include "Lista.h"
#include "Usuario.h"
#include "Mensaje.h"
#include "Amigos.h"
#include "Solicitudes_amistad.h"
using namespace std;

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

    //lectura de archivos
    bool cargarUsuarios(const string& ruta);
    bool cargarAmigos(const string& ruta);
    bool cargarSolicitudes(const string& ruta);
    bool cargarMensajes(const string& ruta);
    bool cargarAlbumes(const string& rutaAlbumes, const string& rutaFotos);


    //guardar los datos
    void guardarSolicitudes(const string& ruta);
    void guardarAmigos(const string& ruta);
    void guardarMensajes(const string& ruta);
    void guardarFotos(const string& ruta);

    //manejo de usuarios
    int buscarUsuario(const string& nombreUsuario) const;
    unsigned int cantidadUsuarios() const;
    Usuario& obtenerUsuario(unsigned int posicion);
    void seleccionarFotosPerfil(unsigned int usuario, const Lista<unsigned int>& excluir, Lista<unsigned int>& elegidos);

    //manejo de temas de amistades
    Solicitudes_amistad& obtenerSolicitudes();
    Amigos& obtenerAmigos();
    Lista<Mensaje>& obtenerMensajes();

    unsigned long memoriaUsada() const;

    int enviarSolicitud(const string& emisor, const string& receptor, const string& fecha);
    bool aceptarSolicitud(unsigned int posicion);
    int enviarMensaje(const string& emisor, const string& receptor, const string& fecha, const string& texto);

};

#endif
