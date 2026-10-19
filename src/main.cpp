#include <iostream>
#include "UdeABook.h"
#include <ctime>
#include <cstdlib>
using namespace std;




void mostrarFotosPerfil(UdeABook& red, unsigned int actual, Lista<unsigned int>& anteriores) {
    Medidor::reiniciar();

    Lista<unsigned int> elegidos;
    red.seleccionarFotosPerfil(actual, anteriores, elegidos);

    if (elegidos.getTamano() == 0) {
        cout << "Aun no tienes amigos." << endl;
    } else {
        cout << "Fotos de perfil de tus amigos:" << endl;
        for (unsigned int i = 0; i < elegidos.getTamano(); i++) {
            cout << "- " << red.obtenerUsuario(elegidos[i]).getNombreUsuario() << ": "
                 << red.obtenerUsuario(elegidos[i]).getFotoPerfil() << endl;
        }
    }

    anteriores = elegidos;
    Medidor::mostrarReporte(red.memoriaUsada() + elegidos.memoriaUsada());
}

int leerNumero() {
    int numero;
    while ((cin >> numero).fail() == true) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Escribe un numero: ";
    }
    return numero;
}

int main() {
    UdeABook red;
    srand(time(nullptr));

    string carpeta = "C:/Users/Pablo Colorado/Documents/Udeabook/datos/";

    if (!red.cargarUsuarios(carpeta + "usuarios.txt")) {
        cout << "No se pudo abrir usuarios.txt" << endl;
        return 1;
    }

    if (!red.cargarAmigos(carpeta + "amigos.txt")) {
        cout << "No se pudo abrir amigos.txt" << endl;
        return 1;
    }

    if (!red.cargarSolicitudes(carpeta + "solicitudes.txt")) {
        cout << "No se pudo abrir solicitudes.txt" << endl;
        return 1;
    }

    if (!red.cargarMensajes(carpeta + "mensajes.txt")) {
        cout << "No se pudo abrir mensajes.txt" << endl;
        return 1;
    }

    if (!red.cargarAlbumes(carpeta + "albumes.txt", carpeta + "fotos.txt")) {
        cout << "No se pudo abrir albumes.txt o fotos.txt" << endl;
        return 1;
    }



    string nombre;
    int actual = -1;

    while (actual == -1) {
        cout << "Usuario: ";
        cin >> nombre;
        actual = red.buscarUsuario(nombre); //obtenemos la posicion del usuario
        if (actual == -1) {
            cout << "Ese usuario no existe." << endl;
        }
    }

    cout << endl << "Bienvenido a UdeABook: " << red.obtenerUsuario(actual).getNombreUsuario() << endl;
    Lista<unsigned int> anteriores;
    cout << endl;
    mostrarFotosPerfil(red, actual, anteriores);

    int opcion = -1;
    while (opcion != 0) {
        cout << endl;
        cout << "1. Administrar amistades" << endl;
        cout << "2. Visitar perfil de un amigo" << endl;
        cout << "3. Ver sugerencias de amistad" << endl;
        cout << "4. Administrar mensajes" << endl;
        cout << "5. Actualizar fotos de perfil de mis amigos" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        opcion = leerNumero();
        cout<<endl;

        if (opcion == 1) {

            int subOpcion;
            cout << "1. Enviar solicitud de amistad" << endl;
            cout << "2. Ver y aceptar solicitudes recibidas" << endl;
            cout << "Opcion: ";
            subOpcion = leerNumero();
            cout<<endl;

            if (subOpcion == 1) {
                string destino;
                cout << "Nombre de usuario: ";
                cin >> destino;

                time_t ahora = time(nullptr);
                char fecha[11]; //arreglo estatico
                strftime(fecha, sizeof(fecha), "%Y-%m-%d", localtime(&ahora));
                string fechaenvio = fecha;

                Medidor::reiniciar();
                int resultado = red.enviarSolicitud(nombre, destino, fecha);

                if (resultado == 0) {
                    cout << "Solicitud enviada." << endl;
                } else if (resultado == 1) {
                    cout << "Ese usuario no existe." << endl;
                } else if (resultado == 2) {
                    cout << "No puedes enviarte una solicitud a ti mismo." << endl;
                } else if (resultado == 3) {
                    cout << "Ya son amigos." << endl;
                } else if (resultado == 4) {
                    cout << "Ya enviaste una solicitud a esa persona." << endl;
                } else if (resultado == 5) {
                    cout << "Esa persona ya te envio una solicitud. Acepta la suya." << endl;
                }

                Medidor::mostrarReporte(red.memoriaUsada());


            //Ver y aceptar solicitudes
            } else if (subOpcion == 2) {
                Medidor::reiniciar();

                Lista<unsigned int> posiciones; //almacenamos las posiciones reales de las solicitudes
                Solicitudes_amistad& bandeja = red.obtenerSolicitudes();

                for (unsigned int i = 0; i < bandeja.cantidad(); i++) {
                    Medidor::contar();
                    if (bandeja.obtener(i).obtenerReceptor() == nombre) {
                        posiciones.agregar(i);
                        cout << posiciones.getTamano() << ". " << bandeja.obtener(i).obtenerEmisor() << " (" << bandeja.obtener(i).obtenerFecha() << ")" << endl;
                    }
                }

                if (posiciones.getTamano() == 0) {
                    cout << "No tienes solicitudes." << endl;
                } else {
                    int eleccion;
                    cout << "Tienes esta cantidad de solicitudes de amistad. (0 para cancelar): ";
                    eleccion = leerNumero();

                    if (eleccion >= 1 && eleccion <= (int)posiciones.getTamano()) {
                        red.aceptarSolicitud(posiciones[eleccion - 1]);
                        cout << "Solicitud aceptada." << endl;
                    }
                }

                Medidor::mostrarReporte(red.memoriaUsada() + posiciones.memoriaUsada());
            }
        }

        else if (opcion == 2) {
            string amigoNombre;
            cout << "Nombre de tu amigo: ";
            cin >> amigoNombre;

            Medidor::reiniciar();
            int a = red.buscarUsuario(amigoNombre);

            if (a < 0 || !red.obtenerAmigos().sonAmigos(actual, a)) {
                cout << "Ese usuario no es tu amigo." << endl;
            } else {
                Usuario& amigo = red.obtenerUsuario(a);
                Lista<unsigned int> visibles;

                for (unsigned int i = 0; i < amigo.cantidadAlbumes(); i++) {
                    Medidor::contar();
                    if (amigo.getAlbum(i).esVisiblePara(false, true)) {
                        visibles.agregar(i);
                        cout << visibles.getTamano() << ". " << amigo.getAlbum(i).getNombre() << endl;
                    }
                }

                if (visibles.getTamano() == 0) {
                    cout << "No tiene albumes visibles." << endl;
                } else {
                    int eleccion;
                    cout << "Album a ver (0 para cancelar): ";
                    eleccion = leerNumero();

                    if (eleccion >= 1 && eleccion <= (int)visibles.getTamano()) {
                        Album& album = amigo.getAlbum(visibles[eleccion - 1]);
                        unsigned int total = album.cantidadFotos();

                        if (total == 0) {
                            cout << "El album no tiene fotos." << endl;
                        } else {
                            Lista<unsigned int> meGusta;
                            for (unsigned int i = 0; i < total; i++) {
                                meGusta.agregar(0);
                            }

                            unsigned int pos = 0;
                            int accion = -1;

                            while (accion != 0) {
                                cout << endl;
                                album.getFoto(pos).mostrarRuta();
                                cout << "1. Siguiente   2. Previa   3. Dar/quitar like   0. Salir" << endl;
                                cout << "Opcion: ";
                                accion = leerNumero();
                                Medidor::contar();

                                if (accion == 1) {
                                    pos = (pos + 1) % total;
                                } else if (accion == 2) {
                                    pos = (pos + total - 1) % total;
                                } else if (accion == 3) {
                                    if (meGusta[pos] == 0) {
                                        album.getFoto(pos).darLike();
                                        meGusta[pos] = 1;
                                        cout << "Diste like." << endl;
                                    } else {
                                        album.getFoto(pos).quitarLike();
                                        meGusta[pos] = 0;
                                        cout << "Quitaste el like." << endl;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            Medidor::mostrarReporte(red.memoriaUsada());
        }


        else if (opcion == 3) {
            int numeroDeSugerencias; //cuantas sugerencias se veran
            cout << "Cuantas sugerencias quieres ver (1 a 20): ";
            numeroDeSugerencias = leerNumero();

            if (numeroDeSugerencias < 1 || numeroDeSugerencias > 20) {
                cout << "Valor no valido." << endl;
            } else {
                Medidor::reiniciar();

                Lista<unsigned int> candidatos;
                Lista<unsigned int> comunes;
                red.obtenerAmigos().sugerencias(actual, candidatos, comunes);

                unsigned int cantidad = candidatos.getTamano();
                if (cantidad > (unsigned int)numeroDeSugerencias) {
                    cantidad = numeroDeSugerencias;
                }

                if (cantidad == 0) {
                    cout << "No hay sugerencias por ahora." << endl;
                }

                for (unsigned int i = 0; i < cantidad; i++) {
                    cout << (i + 1) << ". " << red.obtenerUsuario(candidatos[i]).getNombreUsuario()
                    << " (" << comunes[i] << " amigos en comun)" << endl;
                }

                Medidor::mostrarReporte(red.memoriaUsada() + candidatos.memoriaUsada() + comunes.memoriaUsada());
            }
        }

        else if (opcion == 4) {
            int sub;
            cout << "1. Enviar mensaje" << endl;
            cout << "2. Leer mensajes nuevos" << endl;
            cout << "3. Buscar mensajes por rango de fecha" << endl;
            cout << "Opcion: ";
            sub = leerNumero();

            Lista<Mensaje>& todos = red.obtenerMensajes();

            if (sub == 1) {
                string destino, texto;
                cout << "Nombre del amigo: ";
                cin >> destino;
                cout << "Mensaje: ";
                cin.ignore();
                getline(cin, texto);

                time_t ahora = time(nullptr);
                char FechaHora[17];
                strftime(FechaHora, sizeof(FechaHora), "%Y-%m-%d %H:%M", localtime(&ahora));
                string fecha = FechaHora;

                Medidor::reiniciar();
                int resultado = red.enviarMensaje(nombre, destino, fecha, texto);

                if (resultado == 0) {
                    cout << "Mensaje enviado." << endl;
                } else if (resultado == 1) {
                    cout << "Ese usuario no existe." << endl;
                } else if (resultado == 2) {
                    cout << "Solo puedes escribir a tus amigos." << endl;
                } else if (resultado == 3) {
                    cout << "El mensaje esta vacio." << endl;
                } else {
                    cout << "El mensaje pasa de 512 caracteres." << endl;
                }

                Medidor::mostrarReporte(red.memoriaUsada());
            } else if (sub == 2) {
                Medidor::reiniciar();
                bool hayNuevos = false;

                for (unsigned int i = 0; i < todos.getTamano(); i++) {
                    Medidor::contar();
                    if (todos[i].obtenerReceptor() == nombre && !todos[i].estaLeido()) {
                        cout << todos[i].obtenerEmisor() << " (" << todos[i].obtenerFecha() << "): "
                             << todos[i].obtenerTexto() << endl;
                        todos[i].marcarLeido();
                        hayNuevos = true;
                    }
                }

                if (!hayNuevos) {
                    cout << "No tienes mensajes nuevos." << endl;
                }

                Medidor::mostrarReporte(red.memoriaUsada());

            } else if (sub == 3) {
                string inicio, fin;
                cout << "Fecha de inicio (AAAA-MM-DD): ";
                cin >> inicio;
                cout << "Fecha de fin (AAAA-MM-DD): ";
                cin >> fin;
                fin = fin + " 23:59";

                Medidor::reiniciar();
                bool hayMensajes = false;

                for (unsigned int i = 0; i < todos.getTamano(); i++) {
                    Medidor::contar();
                    if (todos[i].obtenerReceptor() == nombre && todos[i].obtenerFecha() >= inicio && todos[i].obtenerFecha() <= fin) {
                        cout << todos[i].obtenerEmisor() << " (" << todos[i].obtenerFecha() << "): " << todos[i].obtenerTexto() << endl;
                        hayMensajes = true;
                    }
                }

                if (hayMensajes == false) {
                    cout << "No hay mensajes en ese rango." << endl;
                }

                Medidor::mostrarReporte(red.memoriaUsada());
            }
        }

        else if (opcion == 5) {
            mostrarFotosPerfil(red, actual, anteriores);
        }


        else if (opcion != 0) {
            cout << "Opcion no valida." << endl;
        }
    }

    red.guardarSolicitudes(carpeta + "solicitudes.txt");
    red.guardarAmigos(carpeta + "amigos.txt");
    red.guardarMensajes(carpeta + "mensajes.txt");


    return 0;
}
