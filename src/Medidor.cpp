#include "Medidor.h"
#include <iostream>
using namespace std;

unsigned int Medidor::iteraciones = 0;

void Medidor::contar(unsigned int cantidad){
    iteraciones += cantidad;
}

void Medidor::reiniciar(){
    iteraciones = 0;
}

unsigned int Medidor::obtenerIteraciones(){
    return iteraciones;
}

void Medidor::mostrarReporte(unsigned int memoriaBytes){
    cout<<endl;
    cout<<"---Reporte de consumo---"<<endl;
    cout << "iteraciones: " << iteraciones << endl;
    cout << "Memoria en uso: " << memoriaBytes << "bytes" << endl;
}

