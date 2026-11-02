#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include "RegistroAsistencia.h"

class ListaDoble {
private:
    struct Nodo {
        RegistroAsistencia dato;
        Nodo* anterior;
        Nodo* siguiente;

        Nodo(RegistroAsistencia dato);
    };

    Nodo* cabeza;
    Nodo* cola;

public:
    ListaDoble();

    ListaDoble(const ListaDoble&) = delete;
    ListaDoble& operator=(const ListaDoble&) = delete;

    ~ListaDoble();

    void insertar(RegistroAsistencia registro);

    RegistroAsistencia* buscar(int id);

    RegistroAsistencia* buscarPendiente(string idProfesor, string NRC);

    bool eliminar(int id);

    void imprimir() const;

    void consultarProfesor(string idProfesor) const;
    bool existeRegistroActivo(string idProfesor, string cedula) const;
    bool existeNRCyHorario(string NRC, string horaInicio, string horaFin) const;
};

#endif