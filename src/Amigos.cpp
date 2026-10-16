#include "Amigos.h"
#include "Medidor.h"

//inicializacion
Amigos::Amigos() {
    cantidadUsuarios = 0;
    matriz = nullptr;
}

//constructor
Amigos::Amigos(unsigned int cantidadUsuarios) {
    this->cantidadUsuarios = cantidadUsuarios;

    matriz = new bool[cantidadUsuarios * cantidadUsuarios]; //apuntamos a una matriz

    for (unsigned int i = 0; i < cantidadUsuarios * cantidadUsuarios; i++) {
        matriz[i] = false;
    }
} //"matriz" de falses


Amigos::~Amigos() {
    delete[] matriz;
}


//validacion y aceptacion
void Amigos::agregarAmistad(unsigned int a, unsigned int b) {
    if (a < cantidadUsuarios && b < cantidadUsuarios && a != b) {
        matriz[a * cantidadUsuarios + b] = true;
        matriz[b * cantidadUsuarios + a] = true;
    }
}//establecemos la amistad


//validacion y eliminacion
void Amigos::quitarAmistad(unsigned int a, unsigned int b) {
    if (a < cantidadUsuarios && b < cantidadUsuarios && a != b) {
        matriz[a * cantidadUsuarios + b] = false;
        matriz[b * cantidadUsuarios + a] = false;
    }
} //eliminamos la amistad


//me retorna un bool (true=amigos) o (false = No lo son)
bool Amigos::sonAmigos(unsigned int a, unsigned int b) const {
    if (a >= cantidadUsuarios || b >= cantidadUsuarios || a == b) {
        return false;
    }

    return matriz[a * cantidadUsuarios + b];
}


//me da el numero de usuarios del objeto
unsigned int Amigos::obtenerCantidadUsuarios() const {
    return cantidadUsuarios;
}



//crea una tabla nueva que es copia de otra
Amigos::Amigos(const Amigos& otro) {
    cantidadUsuarios = otro.cantidadUsuarios;
    matriz = nullptr;

    if (cantidadUsuarios > 0) {
        matriz = new bool[cantidadUsuarios * cantidadUsuarios];
        for (unsigned int i = 0; i < cantidadUsuarios * cantidadUsuarios; i++) {
            matriz[i] = otro.matriz[i];
            Medidor::contar();
        }
    }
}


//copia otra tabla dentro de esta: amigos1 = amigos2
void Amigos::operator=(const Amigos& otro) {
    bool* nueva = nullptr;

    if (otro.cantidadUsuarios > 0) {
        nueva = new bool[otro.cantidadUsuarios * otro.cantidadUsuarios];
        for (unsigned int i = 0; i < otro.cantidadUsuarios * otro.cantidadUsuarios; i++) {
            nueva[i] = otro.matriz[i];
            Medidor::contar();
        }
    }

    delete[] matriz;
    matriz = nueva;
    cantidadUsuarios = otro.cantidadUsuarios;
}


//cuenta cuantos amigos tiene el usuario a
unsigned int Amigos::cantidadAmigos(unsigned int a) const {
    if (a >= cantidadUsuarios) {
        return 0;
    }

    unsigned int total = 0;
    for (unsigned int i = 0; i < cantidadUsuarios; i++) {
        if (matriz[a * cantidadUsuarios + i]) {
            total++;
        }
        Medidor::contar();
    }
    return total;
}


//cuenta cuantos amigos tienen en comun a y b
unsigned int Amigos::amigosEnComun(unsigned int a, unsigned int b) const {
    if (a >= cantidadUsuarios || b >= cantidadUsuarios || a == b) {
        return 0;
    }

    unsigned int total = 0;
    for (unsigned int i = 0; i < cantidadUsuarios; i++) {
        if (matriz[a * cantidadUsuarios + i] && matriz[b * cantidadUsuarios + i]) {
            total++;
        }
        Medidor::contar();
    }
    return total;
}



//___REVISAR___

//llena dos listas paralelas: candidatos[i] es un usuario sugerido para a y
//comunes[i] es cuantos amigos tiene en comun con a. Quedan de mayor a menor.
void Amigos::sugerencias(unsigned int a, Lista<unsigned int>& candidatos, Lista<unsigned int>& comunes) const {
    if (a >= cantidadUsuarios) {
        return;
    }

    for (unsigned int i = 0; i < cantidadUsuarios; i++) {
        Medidor::contar();

        if (i == a || sonAmigos(a, i)) {
            continue;
        }

        unsigned int enComun = amigosEnComun(a, i);
        if (enComun == 0) {
            continue;
        }

        candidatos.agregar(i);
        comunes.agregar(enComun);

        //sube el nuevo hasta su lugar, intercambiando con el anterior si tiene menos
        unsigned int pos = candidatos.getTamano() - 1;
        while (pos > 0 && comunes[pos - 1] < comunes[pos]) {
            unsigned int auxCandidato = candidatos[pos - 1];
            candidatos[pos - 1] = candidatos[pos];
            candidatos[pos] = auxCandidato;

            unsigned int auxComun = comunes[pos - 1];
            comunes[pos - 1] = comunes[pos];
            comunes[pos] = auxComun;

            pos--;
            Medidor::contar();
        }
    }
}


//bytes que ocupa el objeto y su tabla
unsigned long Amigos::memoriaUsada() const {
    return sizeof(Amigos) + cantidadUsuarios * cantidadUsuarios * sizeof(bool);
}