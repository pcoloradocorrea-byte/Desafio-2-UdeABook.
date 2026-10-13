#ifndef USUARIO_H
#define USUARIO_H
#include <string>
#include "Album.h"
using namespace std;

class Usuario{
private:
    string nombreUsuario;
    string fotoPerfil;
    string fechaNacimiento;
    string correoElectronico;
    string ciudad;
    string pais;
    string fechaInscripcion;
    //faltaria  algo de albumnes ver desde mañana
public:
    Usuario();
    Usuario(string& nombreUsuario, string& fotoPerfil, string fechaNacimiento, string& correoElectronico, string& ciudad, string& pais, string fechaInscripcion);

    void agregarAlbum(const Album& album);
    unsigned int cantidadAlbumnes() const;
    Album& obtenerAlbum(unsigned int posicion);

    string obtenerNombre() const;
    string obtenerFotoPerfil() const;
    string obtenerFechaNacimiento() const;
    string obtenerCorreoElectronico() const;
    string obtenerCiudad() const;
    string obtenerPais() const;
    string obtenerFechaInscripcion() const;

    //faltaria el tema de la memoria
};

#endif // USUARIO_H
