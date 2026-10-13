#ifndef LISTA_H
#define LISTA_H


//Arreglo dinamico que sirve para reemplazar std::vector
//cuando este se llena se duplica
template <typename T> //Esta clase sirve para cualquier tipo de dato

class Lista{
private:
    T* elementos; //apuntador
    unsigned int tamano; //cantidad de elementos saved
    unsigned int capacidad; //cuantos caben en el arreglo

public:
    Lista(){
        elementos = nullptr;
        tamano = 0;
        capacidad = 0;
    }
    ~Lista(){
        delete[] elementos;
    }

    Lista<T>& operator=(constLista<T>& otra);
};




#endif // LISTA_H
