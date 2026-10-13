#ifndef ALBUM_H
#define ALBUM_H

#include "Foto.h"
#include <string>
using namespace std;

class Album{
private:
    string nombre;
    string ruta;
    bool privacidad;
    unsigned int Nfotos;
public:
    enum privacidad{
        publico = 0,  //cualquiera
        privado = 1,  //solo el dueño
        amigos = 2 //dueño y amigos
    }

    //constructores
    Album();
    Album(const string& nombre, const string& ruta, unsigned char privacidad);

    void agregarFoto(const Foto& foto);
    bool Visibilidad(bool beDueno, bool beAmigo);//es el dueño o un amigo?
    unsigned short cantidadFotos() const;

    Foto& obtenerFoto(unsigned short posicion);
    string obtenerNombre() const;
    string obtenerRuta() const;
    unsigned char obtenerPrivacidad() const;
};

//faltaria un metodo de memoria
#endif // ALBUM_H
