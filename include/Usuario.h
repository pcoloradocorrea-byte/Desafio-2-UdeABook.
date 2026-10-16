#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "Album.h"
#include "Lista.h"

class Usuario {
private:
    std::string nombreUsuario;
    std::string fechaNacimiento;
    std::string correo;
    std::string fotoPerfil;
    std::string ciudad;
    std::string pais;
    std::string fechaInscripcion;
    Lista<Album> albumes;

public:
    Usuario();
    Usuario(const std::string& nombreUsuario, const std::string& fechaNacimiento,
            const std::string& correo, const std::string& fotoPerfil,
            const std::string& ciudad, const std::string& pais,
            const std::string& fechaInscripcion);

    void agregarAlbum(const Album& album);
    unsigned int cantidadAlbumes() const;
    Album& getAlbum(unsigned int posicion);

    std::string getNombreUsuario() const;
    std::string getFechaNacimiento() const;
    std::string getCorreo() const;
    std::string getFotoPerfil() const;
    std::string getCiudad() const;
    std::string getPais() const;
    std::string getFechaInscripcion() const;

    unsigned long memoriaUsada() const;
};

#endif
