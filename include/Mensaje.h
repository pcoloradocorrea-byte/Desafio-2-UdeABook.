#ifndef MENSAJE_H
#define MENSAJE_H
#include <string>
using namespace std;

class Mensaje{
private:
    string emisor;
    string receptor;
    string fecha;
    string texto;
    bool leido;

public:
    Mensaje();
    Mensaje(const string& emisor, const string& receptor, const string& fecha, const string& texto);

    void marcarLeido();
    string obtenerEmisor() const;
    string obtenerReceptor() const;
    string obtenerFecha() const;
    string obtenerTexto() const;
    bool estaLeido() const;

    //falta Memoria
};

#endif // MENSAJE_H
