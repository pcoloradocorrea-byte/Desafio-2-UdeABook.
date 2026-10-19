cmake_minimum_required(VERSION 3.16)
project(Udeabook LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(Udeabook
    src/main.cpp
    src/Foto.cpp
    src/Medidor.cpp
    include/Foto.h
    include/Medidor.h
    include/Lista.h
    include/Album.h
    src/Album.cpp
    include/Usuario.h
    src/Usuario.cpp
    include/Mensaje.h
    src/Mensaje.cpp
    include/SolicitudAmistad.h
    src/SolicitudAmistad.cpp
    include/Amigos.h
    src/Amigos.cpp
    include/Solicitudes_amistad.h
    src/Solicitudes_amistad.cpp
    include/UdeABook.h
    src/UdeABook.cpp
    datos/usuarios.txt
    datos/amigos.txt
    datos/solicitudes.txt

    datos/albumes.txt
    datos/fotos.txt
    datos/mensajes.txt



)