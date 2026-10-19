#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "Album.h"
#include "Lista.h"
using namespace std;

class Usuario {
private:
    string nombreUsuario;
    string fechaNacimiento;
    string correo;
    string fotoPerfil;
    string ciudad;
    string pais;
    string fechaInscripcion;
    Lista<Album> albumes;

public:
    Usuario();
    Usuario(const string& nombreUsuario,const string& fechaNacimiento, const string& correo, const string& fotoPerfil, const string& ciudad, const string& pais, const string& fechaInscripcion);

    void agregarAlbum(const Album& album);
    unsigned int cantidadAlbumes() const;
    Album& getAlbum(unsigned int posicion);

    string getNombreUsuario() const;
    string getFechaNacimiento() const;
    string getCorreo() const;
    string getFotoPerfil() const;
    string getCiudad() const;
    string getPais() const;
    string getFechaInscripcion() const;

    unsigned long memoriaUsada() const;
};

#endif
