#ifndef FOTO_H
#define FOTO_H
#include <string>
using namespace std;

//la foto es una ruta
class Foto{
private:
    string fechaCaptura;
    unsigned short tamano;
    string ruta;
    unsigned int likes;

public:
    //constructores
    Foto();
    Foto(string& fechaCaptura, unsigned short tamaño, const std::string& ruta);

    void mostrarRuta() const;
    void darLike();
    void quitarLike();

    string obtenerFechacaptura()const;
    unsigned short obtenerTamano() const;
    string obtenerRuta() const;
    int obtenerLikes() const;

    unsigned long memoriaUsada() const;

};

#endif // FOTO_H
