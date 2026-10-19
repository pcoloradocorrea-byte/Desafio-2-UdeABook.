#include "Amigos.h"
#include "Medidor.h"

//inicializacion
Amigos::Amigos() {
    cantidadUsuarios = 0;
    matriz = nullptr;
}


//reserva una matriz de n x n guardada en un arreglo plano
Amigos::Amigos(unsigned int cantidadUsuarios) {
    this->cantidadUsuarios = cantidadUsuarios;

    matriz = new bool[cantidadUsuarios * cantidadUsuarios]; //apuntamos a una matriz

    //al inicio nadie es amigo de nadie
    for (unsigned int i = 0; i < cantidadUsuarios * cantidadUsuarios; i++) {
        matriz[i] = false;
    }
}



Amigos::~Amigos() {
    delete[] matriz;
}




//marca la amistad entre posicion A y posicion B
void Amigos::agregarAmistad(unsigned int PosicionA, unsigned int PosicionB) {
    if (PosicionA < cantidadUsuarios && PosicionB < cantidadUsuarios && PosicionA != PosicionB) {
        matriz[PosicionA * cantidadUsuarios + PosicionB] = true;
        matriz[PosicionB * cantidadUsuarios + PosicionA] = true;
    }
}


//se elimina la amistad entre posicionA y posicion B
void Amigos::quitarAmistad(unsigned int PosicionA, unsigned int PosicionB) {
    if (PosicionA < cantidadUsuarios && PosicionB < cantidadUsuarios && PosicionA != PosicionB) {
        matriz[PosicionA * cantidadUsuarios + PosicionB] = false;
        matriz[PosicionB * cantidadUsuarios + PosicionA] = false;
    }
}


//me retorna un bool (true=amigos) o (false = No lo son)
bool Amigos::sonAmigos(unsigned int PosicionA, unsigned int PosicionB) const {
    if (PosicionA >= cantidadUsuarios || PosicionB >= cantidadUsuarios || PosicionA == PosicionB) {
        return false;
    }
    return matriz[PosicionA * cantidadUsuarios + PosicionB];
}



unsigned int Amigos::obtenerCantidadUsuarios() const {
    return cantidadUsuarios;
}



//constructor de copia para evitar errores
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


//reemplazamos la matriz vacia por una de tamano real
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


//cuenta cuantos amigos tiene el usuario PosicionA
unsigned int Amigos::cantidadAmigos(unsigned int PosicionA) const {
    if (PosicionA >= cantidadUsuarios) {
        return 0;
    }

    unsigned int total = 0;
    for (unsigned int i = 0; i < cantidadUsuarios; i++) {
        if (matriz[PosicionA * cantidadUsuarios + i]) {
            total++;
        }
        Medidor::contar();
    }
    return total;
}


//cuenta cuantos amigos tienen en comun A y B
unsigned int Amigos::amigosEnComun(unsigned int PosicionA, unsigned int PosicionB) const {
    if (PosicionA >= cantidadUsuarios || PosicionB >= cantidadUsuarios || PosicionA == PosicionB) {
        return 0;
    }

    unsigned int total = 0;
    for (unsigned int i = 0; i < cantidadUsuarios; i++) {
        if (matriz[PosicionA * cantidadUsuarios + i] && matriz[PosicionB * cantidadUsuarios + i]) {
            total++;
        }
        Medidor::contar();
    }
    return total;
}



//armamos 2 listas de sugenrencias de amistad para el usuario en PosicionA
void Amigos::sugerencias(unsigned int PosicionA, Lista<unsigned int>& candidatos, Lista<unsigned int>& comunes) const {
    if (PosicionA >= cantidadUsuarios) {
        return;
    }

    //se revisa a cada usuario
    for (unsigned int i = 0; i < cantidadUsuarios; i++) {
        Medidor::contar();

        //si ya son amigos o es el mismo se descarta
        if (i == PosicionA || sonAmigos(PosicionA, i)) {
            continue;
        }


        //si no hay amigos en comun tambien se descarta
        unsigned int enComun = amigosEnComun(PosicionA, i);
        if (enComun == 0) {
            continue;
        }


        //si lo anterior no se cumple se agrega el candidato
        candidatos.agregar(i);
        comunes.agregar(enComun);


        //se realiza un ordenamiento por insercion para que la lista quede de mayor a menor
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



unsigned long Amigos::memoriaUsada() const {
    return sizeof(Amigos) + cantidadUsuarios * cantidadUsuarios * sizeof(bool);
}