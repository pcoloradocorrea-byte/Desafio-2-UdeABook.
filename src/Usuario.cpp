#include "Usuario.h"

Usuario::Usuario() : nombreUsuario(""), fechaNacimiento(""), correo(""), fotoPerfil(""), ciudad(""), pais(""), fechaInscripcion("") {
}

Usuario::Usuario(const std::string& nombreUsuario, const std::string& fechaNacimiento, const std::string& correo, const std::string& fotoPerfil, const std::string& ciudad, const std::string& pais, const std::string& fechaInscripcion)
    : nombreUsuario(nombreUsuario), fechaNacimiento(fechaNacimiento), correo(correo),
    fotoPerfil(fotoPerfil), ciudad(ciudad), pais(pais),
    fechaInscripcion(fechaInscripcion) {
}

void Usuario::agregarAlbum(const Album& album) {
    albumes.agregar(album);
}

unsigned int Usuario::cantidadAlbumes() const {
    return albumes.getTamano();
}

Album& Usuario::getAlbum(unsigned int posicion) {
    return albumes[posicion];
}

std::string Usuario::getNombreUsuario() const {
    return nombreUsuario;
}

std::string Usuario::getFechaNacimiento() const {
    return fechaNacimiento;
}

std::string Usuario::getCorreo() const {
    return correo;
}

std::string Usuario::getFotoPerfil() const {
    return fotoPerfil;
}

std::string Usuario::getCiudad() const {
    return ciudad;
}

std::string Usuario::getPais() const {
    return pais;
}

std::string Usuario::getFechaInscripcion() const {
    return fechaInscripcion;
}

unsigned long Usuario::memoriaUsada() const {
    return sizeof(Usuario) - sizeof(Lista<Album>) + nombreUsuario.capacity()
    + fechaNacimiento.capacity() + correo.capacity() + fotoPerfil.capacity()
        + ciudad.capacity() + pais.capacity() + fechaInscripcion.capacity()
        + albumes.memoriaUsada();
}

