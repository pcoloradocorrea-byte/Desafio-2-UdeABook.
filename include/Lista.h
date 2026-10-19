#ifndef LISTA_H
#define LISTA_H

#include "Medidor.h"

// Lista es un molde: T es el tipo de dato que guardará (int, Foto, Album, ...)
template <typename T>
class Lista{
private:
    T* elementos;
    unsigned int tamano;
    unsigned int capacidad;

public:
    Lista(){
        elementos = nullptr;
        tamano = 0;
        capacidad = 0;
    }



    ~Lista(){
        delete[] elementos;
    }


    //me da una copia de  otra (ambos del mismo tipo)
    Lista(const Lista<T>& ListaCopia){
        elementos = nullptr;    // Empieza vacía
        tamano = 0;
        capacidad = 0;
        *this = ListaCopia;
    }


    // Copia el contenido de otra lista dentro de esta lista1 = lista2, los datos ya agregados
    Lista<T>& operator=(const Lista<T>& ListaCopiar){
        if(this != &ListaCopiar){
            delete[] elementos;
            tamano = ListaCopiar.tamano;
            capacidad = ListaCopiar.tamano;
            if(tamano > 0){
                elementos = new T[capacidad];
                for(unsigned int i = 0; i < tamano; i++){
                    elementos[i] = ListaCopiar.elementos[i];
                }
            }

            else {
                elementos = nullptr;                // Si la otra está vacía, esta también
            }
        }
        return *this;
    }



    // Agrega un dato a la lista. Si el arreglo está lleno, lo agranda al doble
    void agregar(const T& elemento){
        if(tamano == capacidad){
            unsigned int nuevaCapacidad = 4;
            if(capacidad > 0){
                nuevaCapacidad = capacidad * 2;
            }//caso en el que necesitemos más espacio

            T* nuevo = new T[nuevaCapacidad];
            for(unsigned int i = 0; i < tamano; i++){
                nuevo[i] = elementos[i];            // Copia los datos viejos al arreglo nuevo
            }

            nuevo[tamano] = elemento;  // Guarda el dato nuevo en el primer espacio libre

            delete[] elementos;

            elementos = nuevo;                      // Ahora la lista apunta al arreglo nuevo
            capacidad = nuevaCapacidad;             // Guarda la nueva capacidad
        }

        else {
            elementos[tamano] = elemento;           // Hay espacio: guarda el dato directamente
        }

        tamano++;                                   // Ahora hay un dato más
    }


    // Devuelve el dato de una posición, para leerlo o cambiarlo
    T& operator[](unsigned int posicion){
        return elementos[posicion];
    }


    const T& operator[](unsigned int posicion) const{
        return elementos[posicion];
    }


    // Devuelve cuántos datos hay guardados
    unsigned int getTamano() const{
        return tamano;
    }


    //Quitamos un dato de una posicion y corremos los datos de adelante para atras
    void quitarEn(unsigned int posicion){
        for(unsigned int i = posicion; i + 1 < tamano; i++){
            elementos[i] = elementos[i + 1];
        }
        tamano--;
    }


    unsigned long memoriaUsada() const{
        unsigned long total = sizeof(Lista<T>);
        for(unsigned int i = 0; i < capacidad; i++){
            total += memoriaDe(elementos[i]);
        }
        return total;
    }
};

#endif // LISTA_H
