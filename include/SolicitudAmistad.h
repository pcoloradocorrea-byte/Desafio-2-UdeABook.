#ifndef SOLICITUDAMISTAD_H
#define SOLICITUDAMISTAD_H
#include <string>
using namespace std;

class SolicitudAmistad{
private:
    string emisor;
    string receptor;
    string fecha;

public:
    SolicitudAmistad();
    SolicitudAmistad(const string& emisor, const string& receptor, const string fecha);
    string obtenerEmisor() const;
    string obtenerReceptor() const;
    string obtenerFecha() const;

    //memoria
};
#endif // SOLICITUDAMISTAD_H
