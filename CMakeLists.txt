cmake_minimum_required(VERSION 3.16)

project(Udeabook LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Udeabook main.cpp
    Medidor.h
    Medidor.cpp
    Lista.h
    Foto.h
    Foto.cpp)

include(GNUInstallDirs)
install(TARGETS Udeabook
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
