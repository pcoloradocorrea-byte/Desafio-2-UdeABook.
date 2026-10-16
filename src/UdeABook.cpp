#include "UdeABook.h"
#include "Medidor.h"

UdeABook::UdeABook() {
}

void UdeABook::agregarUsuario(const Usuario& usuario) {
    usuarios.agregar(usuario);
}

void UdeABook::agregarMensaje(const Mensaje& mensaje) {
    mensajes.agregar(mensaje);
}

void UdeABook::prepararAmigos() {
    amigos = Amigos(usuarios.getTamano());
}

int UdeABook::buscarUsuario(const string& nombreUsuario) const {
    for (unsigned int i = 0; i < usuarios.getTamano(); i++) {
        Medidor::contar();
        if (usuarios[i].getNombreUsuario() == nombreUsuario) {
            return i;
        }
    }
    return -1;
}

unsigned int UdeABook::cantidadUsuarios() const {
    return usuarios.getTamano();
}

Usuario& UdeABook::obtenerUsuario(unsigned int posicion) {
    return usuarios[posicion];
}

Solicitudes_amistad& UdeABook::obtenerSolicitudes() {
    return solicitudes;
}

Amigos& UdeABook::obtenerAmigos() {
    return amigos;
}

Lista<Mensaje>& UdeABook::obtenerMensajes() {
    return mensajes;
}

unsigned long UdeABook::memoriaUsada() const {
    return sizeof(UdeABook) - sizeof(Lista<Usuario>) - sizeof(Lista<Mensaje>)
    - sizeof(Solicitudes_amistad) - sizeof(Amigos)
        + usuarios.memoriaUsada() + mensajes.memoriaUsada()
        + solicitudes.memoriaUsada() + amigos.memoriaUsada();
}