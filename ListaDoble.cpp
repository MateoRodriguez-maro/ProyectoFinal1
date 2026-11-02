#include "ListaDoble.h"
#include <iostream>

using namespace std;

// Constructor del nodo.
ListaDoble::Nodo::Nodo(RegistroAsistencia dato) : dato(dato) {
    anterior = nullptr;
    siguiente = nullptr;
}

// Constructor de la lista.
ListaDoble::ListaDoble() {
    cabeza = nullptr;
    cola = nullptr;
}

// Destructor.
ListaDoble::~ListaDoble() {
    Nodo* actual = cabeza;

    while (actual != nullptr) {
        Nodo* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }

    cabeza = nullptr;
    cola = nullptr;
}

// Insertar al final.
void ListaDoble::insertar(RegistroAsistencia registro) {
    Nodo* nuevo = new Nodo(registro);

    if (cabeza == nullptr) {
        cabeza = nuevo;
        cola = nuevo;
    }
    else {
        nuevo->anterior = cola;
        cola->siguiente = nuevo;
        cola = nuevo;
    }

    cout << "\nRegistro insertado correctamente.\n";
}

// Buscar por ID.
RegistroAsistencia* ListaDoble::buscar(int id) {
    Nodo* actual = cabeza;

    while (actual != nullptr) {
        if (actual->dato.getIdRegistro() == id) {
            return &actual->dato;
        }

        actual = actual->siguiente;
    }

    return nullptr;
}

// Buscar por profesor y materia.
RegistroAsistencia* ListaDoble::buscarPendiente(
    string idProfesor, string NRC) {

    Nodo* actual = cabeza;

    while (actual != nullptr) {

        if (actual->dato.getProfesor().getIdProfesor() == idProfesor &&
            actual->dato.getMateria().getNRC() == NRC &&
            !actual->dato.tieneSalida()) {

            return &actual->dato;
        }

        actual = actual->siguiente;
    }

    return nullptr;
}
// Verificar si un profesor tiene una asistencia pendiente.
bool ListaDoble::existeRegistroActivo(string idProfesor, string cedula) const {

    const Nodo* actual = cabeza;

    while (actual != nullptr) {

        if (!actual->dato.tieneSalida()) {

            if (actual->dato.getProfesor().getIdProfesor() == idProfesor ||
                actual->dato.getProfesor().getCedula() == cedula) {

                return true;
            }
        }

        actual = actual->siguiente;
    }

    return false;
}
// Verificar si existe un NRC con el mismo horario.
bool ListaDoble::existeNRCyHorario(
    string NRC, string horaInicio, string horaFin) const {

    const Nodo* actual = cabeza;

    while (actual != nullptr) {

        Horario horario = actual->dato.getMateria().getHorario();

        if (actual->dato.getMateria().getNRC() == NRC &&
            horario.getHoraInicio() == horaInicio &&
            horario.getHoraFin() == horaFin) {

            return true;
        }

        actual = actual->siguiente;
    }

    return false;
}

// Eliminar por ID.
bool ListaDoble::eliminar(int id) {
    Nodo* actual = cabeza;

    while (actual != nullptr) {

        if (actual->dato.getIdRegistro() == id) {

            if (actual == cabeza) {
                cabeza = actual->siguiente;
            }

            if (actual == cola) {
                cola = actual->anterior;
            }

            if (actual->anterior != nullptr) {
                actual->anterior->siguiente = actual->siguiente;
            }

            if (actual->siguiente != nullptr) {
                actual->siguiente->anterior = actual->anterior;
            }

            delete actual;

            return true;
        }

        actual = actual->siguiente;
    }

    return false;
}

// Imprimir todos los registros.
void ListaDoble::imprimir() const {
    Nodo* actual = cabeza;

    if (actual == nullptr) {
        cout << "\nNo existen registros de asistencia.\n";
        return;
    }

    cout << "\n======= LISTA DE ASISTENCIAS =======\n";

    while (actual != nullptr) {
        actual->dato.imprimir();
        actual = actual->siguiente;
    }
}

// Consultar por profesor.
void ListaDoble::consultarProfesor(string idProfesor) const {
    Nodo* actual = cabeza;
    bool encontrado = false;

    while (actual != nullptr) {

        if (actual->dato.getProfesor().getIdProfesor() == idProfesor) {
            actual->dato.imprimir();
            encontrado = true;
        }

        actual = actual->siguiente;
    }

    if (!encontrado) {
        cout << "\nNo se encontraron registros para ese profesor.\n";
    }
}