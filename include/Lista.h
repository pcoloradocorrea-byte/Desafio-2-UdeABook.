#ifndef LISTA_H
#define LISTA_H

#include "Medidor.h"

// Lista es un molde: T es el tipo de dato que guardará (int, Foto, Album, ...)
template <typename T>
class Lista{
private:
    T* elementos;           //Aqui se guardan los atributos del tipo, por asi decirlo ejemplo foto [fecha, tamano, ruta, likes]
    unsigned int tamano;    //Numero de datos agregados
    unsigned int capacidad; // Cuántos datos caben antes de tener que agrandar el arreglo

public:
    // Crea una lista vacía: sin arreglo, sin datos y sin espacio reservado
    Lista(){
        elementos = nullptr;    // Todavía no hay arreglo
        tamano = 0;             // No hay datos guardados
        capacidad = 0;          // No hay espacio reservado
    }


    // Se ejecuta cuando la lista deja de existir: libera la memoria del arreglo
    ~Lista(){
        delete[] elementos;     // Devuelve al sistema la memoria del arreglo
    }


    //me da una copia de  otra (ambos del mismo tipo)
    Lista(const Lista<T>& otra){
        elementos = nullptr;    // Empieza vacía
        tamano = 0;
        capacidad = 0;
        *this = otra;
    }


    // Copia el contenido de otra lista dentro de esta lista1 = lista2, los datos ya agregados
    Lista<T>& operator=(const Lista<T>& otra){
        if(this != &otra){                          // validacion de que no sea la misma lista
            delete[] elementos;                     // Libera el arreglo viejo de esta lista
            tamano = otra.tamano;                   // Toma el mismo tamaño que la otra
            capacidad = otra.tamano;                // El arreglo nuevo tendrá justo ese espacio
            if(tamano > 0){                         // Si la otra tiene datos
                elementos = new T[capacidad];       // Crea un arreglo propio para esta lista
                for(unsigned int i = 0; i < tamano; i++){
                    elementos[i] = otra.elementos[i];   // Copia cada dato, uno por uno
                }
            } else {
                elementos = nullptr;                // Si la otra está vacía, esta también
            }
        }
        return *this;                               // Devuelve esta lista, para permitir a = b = c
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


    // Devuelve el dato de una posición, para leerlo o cambiarlo: lista[2]
    T& operator[](unsigned int posicion){
        return elementos[posicion];                 // Devuelve el dato original, no una copia
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
        tamano--; //dato menos
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
