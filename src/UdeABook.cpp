#include "UdeABook.h"
#include "Medidor.h"
#include <fstream>

UdeABook::UdeABook() {
}



void UdeABook::agregarUsuario(const Usuario& usuario) {
    usuarios.agregar(usuario);
}



void UdeABook::agregarMensaje(const Mensaje& mensaje) {
    mensajes.agregar(mensaje);
}



//inicializamos la matriz de amistades
void UdeABook::prepararAmigos() {
    amigos = Amigos(usuarios.getTamano());
}



//buscamos un usuario y retornamos su posicion
int UdeABook::buscarUsuario(const string& nombreUsuario) const {
    for (unsigned int i = 0; i < usuarios.getTamano(); i++) {
        Medidor::contar(); //contamos las iteraciones
        if (usuarios[i].getNombreUsuario() == nombreUsuario) {
            return i;
        }
    }
    return -1;
}



unsigned int UdeABook::cantidadUsuarios() const {
    return usuarios.getTamano();
}



//obtengo un usuario con su posicion
Usuario& UdeABook::obtenerUsuario(unsigned int posicion) {
    return usuarios[posicion];
}


//getters
Solicitudes_amistad& UdeABook::obtenerSolicitudes() {
    return solicitudes;
}



Amigos& UdeABook::obtenerAmigos() {
    return amigos;
}



Lista<Mensaje>& UdeABook::obtenerMensajes() {
    return mensajes;
}



unsigned long UdeABook::memoriaUsada() const {
    return sizeof(UdeABook) - sizeof(Lista<Usuario>) - sizeof(Lista<Mensaje>)
    - sizeof(Solicitudes_amistad) - sizeof(Amigos)
        + usuarios.memoriaUsada() + mensajes.memoriaUsada()
        + solicitudes.memoriaUsada() + amigos.memoriaUsada();
}



//Todo nos queda en Lista<ususarios>
bool UdeABook::cargarUsuarios(const string& ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        return false;
    }

    string nombre, nacimiento, correo, foto, ciudad, pais, inscripcion;

    while (getline(archivo, nombre, ';')) {
        getline(archivo, nacimiento, ';');
        getline(archivo, correo, ';');
        getline(archivo, foto, ';');
        getline(archivo, ciudad, ';');
        getline(archivo, pais, ';');
        getline(archivo, inscripcion);

        Medidor::contar();

        if (nombre.empty()) {
            continue;
        }

        usuarios.agregar(Usuario(nombre, nacimiento, correo, foto, ciudad, pais, inscripcion));
    }

    archivo.close();
    return true;
}



//se obtiene cada nombre de usuario y se hace la amistad anita;carla a =anita y b = carla
bool UdeABook::cargarAmigos(const string& ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        return false;
    }

    prepararAmigos();

    string usuarioA, usuarioB;

    while (getline(archivo, usuarioA, ';')) {
        getline(archivo, usuarioB);

        Medidor::contar();

        int a = buscarUsuario(usuarioA);
        int b = buscarUsuario(usuarioB);

        if (a >= 0 && b >= 0) {
            amigos.agregarAmistad(a, b);
        }
    }

    archivo.close();
    return true;
}



int UdeABook::enviarSolicitud(const string& emisor, const string& receptor, const string& fecha) {
    int a = buscarUsuario(emisor);
    int b = buscarUsuario(receptor);

    if (a < 0 || b < 0) {
        return 1; //no existe
    }

    if (a == b) {
        return 2; //no te puedes enviar una solicitud a ti mismo
    }

    if (amigos.sonAmigos(a, b) == true) {
        return 3; //ya son amigos
    }

    if (solicitudes.existe(emisor, receptor) == true) {
        return 4; //ya le enviaste una solicitud
    }

    if (solicitudes.existe(receptor, emisor) == true) {
        return 5; //ya tienes una solicitud de el
    }

    solicitudes.agregar(SolicitudAmistad(emisor, receptor, fecha));
    return 0; //enviada
}



bool UdeABook::aceptarSolicitud(unsigned int posicion) {
    //caso en el que posicion del usuario al que le quieren enviar solicitud no este en el rango
    if (posicion >= solicitudes.cantidad()) {
        return false;
    }

    SolicitudAmistad& s = solicitudes.obtener(posicion);
    int a = buscarUsuario(s.obtenerEmisor());
    int b = buscarUsuario(s.obtenerReceptor());

    if (a < 0 || b < 0) {
        return false;
    }

    amigos.agregarAmistad(a, b);
    solicitudes.quitar(posicion);
    return true;
}



bool UdeABook::cargarSolicitudes(const string& ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        return false;
    }

    string emisor, receptor, fecha;

    while (getline(archivo, emisor, ';')) {
        getline(archivo, receptor, ';');
        getline(archivo, fecha);

        Medidor::contar();

        if (emisor.empty()) {
            continue;
        }

        solicitudes.agregar(SolicitudAmistad(emisor, receptor, fecha));
    }

    archivo.close();
    return true;
}



bool UdeABook::cargarMensajes(const string& ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        return false;
    }

    string emisor, receptor, fecha, leido, texto;

    while (getline(archivo, emisor, ';')) {
        getline(archivo, receptor, ';');
        getline(archivo, fecha, ';');
        getline(archivo, leido, ';');
        getline(archivo, texto);

        Medidor::contar();

        if (emisor.empty()) {
            continue;
        }

        Mensaje mensaje(emisor, receptor, fecha, texto);
        if (leido == "1") {
            mensaje.marcarLeido();
        }
        mensajes.agregar(mensaje);
    }

    archivo.close();
    return true;
}



int UdeABook::enviarMensaje(const string& emisor, const string& receptor, const string& fecha, const string& texto) {
    int a = buscarUsuario(emisor);
    int b = buscarUsuario(receptor);

    if (a < 0 || b < 0) {
        return 1;
    }
    if (!amigos.sonAmigos(a, b)) {
        return 2;
    }

    bool vacio = true;
    for (unsigned int i = 0; i < texto.length(); i++) {
        Medidor::contar();
        if (texto[i] != ' ') {
            vacio = false;
            break;
        }
    }
    if (vacio) {
        return 3;
    }
    if (texto.length() > 512) {
        return 4;
    }

    mensajes.agregar(Mensaje(emisor, receptor, fecha, texto));
    return 0;
}



bool UdeABook::cargarAlbumes(const string& rutaAlbumes, const string& rutaFotos) {
    ifstream archivoAlbumes(rutaAlbumes);
    if (!archivoAlbumes.is_open()) {
        return false;
    }

    string dueno, nombre, ruta, privacidad;

    while (getline(archivoAlbumes, dueno, ';')) {
        getline(archivoAlbumes, nombre, ';');
        getline(archivoAlbumes, ruta, ';');
        getline(archivoAlbumes, privacidad);

        Medidor::contar();

        int u = buscarUsuario(dueno);
        if (u < 0 || privacidad.empty()) {
            continue;
        }

        usuarios[u].agregarAlbum(Album(nombre, ruta, privacidad[0] - '0'));
    }

    archivoAlbumes.close();

    ifstream archivoFotos(rutaFotos);
    if (!archivoFotos.is_open()) {
        return false;
    }

    string nombreAlbum, fecha, tamano, rutaFoto, likes;

    while (getline(archivoFotos, dueno, ';')) {
        getline(archivoFotos, nombreAlbum, ';');
        getline(archivoFotos, fecha, ';');
        getline(archivoFotos, tamano, ';');
        getline(archivoFotos, rutaFoto, ';');
        getline(archivoFotos, likes);

        Medidor::contar();

        int u = buscarUsuario(dueno);
        if (u < 0 || tamano.empty() || likes.empty()) {
            continue;
        }

        Usuario& usuario = usuarios[u];

        for (unsigned int i = 0; i < usuario.cantidadAlbumes(); i++) {
            Medidor::contar();
            if (usuario.getAlbum(i).getNombre() == nombreAlbum) {
                Foto foto(fecha, stoi(tamano), rutaFoto);
                int cantidadLikes = stoi(likes);
                for (int k = 0; k < cantidadLikes; k++) {
                    foto.darLike();
                }
                usuario.getAlbum(i).agregarFoto(foto);
                break;
            }
        }
    }

    archivoFotos.close();
    return true;
}



void UdeABook::guardarSolicitudes(const std::string& ruta) {
    std::ofstream archivo(ruta);
    if (!archivo.is_open()) {
        return;
    }
    for (unsigned int i = 0; i < solicitudes.cantidad(); i++) {
        SolicitudAmistad& s = solicitudes.obtener(i);
        archivo << s.obtenerEmisor() << ";"
                << s.obtenerReceptor() << ";"
                << s.obtenerFecha() << "\n";
    }
}


void UdeABook::guardarAmigos(const std::string& ruta) {
    std::ofstream archivo(ruta);
    if (!archivo.is_open()) {
        return;
    }
    for (unsigned int i = 0; i < usuarios.getTamano(); i++) {
        for (unsigned int j = i + 1; j < usuarios.getTamano(); j++) {
            if (amigos.sonAmigos(i, j)) {
                archivo << usuarios[i].getNombreUsuario() << ";"
                        << usuarios[j].getNombreUsuario() << "\n";
            }
        }
    }
}



void UdeABook::guardarMensajes(const std::string& ruta) {
    std::ofstream archivo(ruta);
    if (!archivo.is_open()) {
        return;
    }
    for (unsigned int i = 0; i < mensajes.getTamano(); i++) {
        Mensaje& m = mensajes[i];
        archivo << m.obtenerEmisor() << ";"
                << m.obtenerReceptor() << ";"
                << m.obtenerFecha() << ";"
                << (m.estaLeido() ? 1 : 0) << ";"
                << m.obtenerTexto() << "\n";
    }
}



void UdeABook::guardarFotos(const std::string& ruta) {
    std::ofstream archivo(ruta);
    if (!archivo.is_open()) {
        return;
    }
    for (unsigned int i = 0; i < usuarios.getTamano(); i++) {
        Usuario& u = usuarios[i];
        for (unsigned int a = 0; a < u.cantidadAlbumes(); a++) {
            Album& album = u.getAlbum(a);
            for (unsigned int f = 0; f < album.cantidadFotos(); f++) {
                Foto& foto = album.getFoto(f);
                archivo << u.getNombreUsuario() << ";"
                        << album.getNombre() << ";"
                        << foto.obtenerFechacaptura() << ";"
                        << foto.obtenerTamano() << ";"
                        << foto.obtenerRuta() << ";"
                        << foto.obtenerLikes() << "\n";
            }
        }
    }
}



//fotos de perfil que mostraremos
void UdeABook::seleccionarFotosPerfil(unsigned int usuario, const Lista<unsigned int>& excluir, Lista<unsigned int>& elegidos) {

    //lista con todos los amigos
    Lista<unsigned int> todos;
    for (unsigned int i = 0; i < usuarios.getTamano(); i++) {
        Medidor::contar();
        if (amigos.sonAmigos(usuario, i) == true) {
            todos.agregar(i);
        }
    }

    //segun los amigos en comun se dan las probabilidades (2, 5 o 7) y evitamos que aquellos que ya salieron salgan nuevamente
    Lista<unsigned int> boletas; //almacenamos las probabilidades
    unsigned int cantidad = 0;

    for (unsigned int k = 0; k < todos.getTamano(); k++) {
        unsigned int amigo = todos[k];

        bool esAnterior = false;
        for (unsigned int j = 0; j < excluir.getTamano(); j++) {
            if (excluir[j] == amigo) {
                esAnterior = true;
            }
        }
        if (esAnterior == true ) {
            continue;
        }

        unsigned int comunes = amigos.amigosEnComun(usuario, amigo);
        unsigned int peso = 2;
        if (comunes >= 21) {
            peso = 7;
        } else if (comunes >= 11) {
            peso = 5;
        }

        for (unsigned int p = 0; p < peso; p++) {
            boletas.agregar(amigo);
        }
        cantidad++;
    }

    //se sacan boletas al azar hasta tener 3 amigos distintos
    while (elegidos.getTamano() < 3 && elegidos.getTamano() < cantidad) {
        unsigned int ganador = boletas[rand() % boletas.getTamano()];

        bool repetido = false;
        for (unsigned int j = 0; j < elegidos.getTamano(); j++) {
            if (elegidos[j] == ganador) {
                repetido = true;
            }
        }
        if (repetido == false) {
            elegidos.agregar(ganador);
        }
    }
}
