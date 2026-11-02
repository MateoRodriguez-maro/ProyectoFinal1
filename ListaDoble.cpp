#include "ListaDoble.h"
#include <iostream>
#include <fstream>

using namespace std;


ListaDoble::Nodo::Nodo(RegistroAsistencia dato) : dato(dato) {
    anterior = nullptr;
    siguiente = nullptr;
}


ListaDoble::ListaDoble() {
    cabeza = nullptr;
    cola = nullptr;
}


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

bool ListaDoble::exportarTXT(string nombreArchivo) const {

    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        return false;
    }

    const Nodo* actual = cabeza;

    archivo << "========================================\n";
    archivo << "       SISTEMA DE ASISTENCIA DOCENTE\n";
    archivo << "========================================\n";

    if (actual == nullptr) {
        archivo << "\nNo existen registros de asistencia.\n";
    }

    while (actual != nullptr) {

        archivo << "\n----------------------------------------\n";
        archivo << "ID Registro: " << actual->dato.getIdRegistro() << endl;
        archivo << "Profesor: "
                << actual->dato.getProfesor().getNombreCompleto() << endl;
        archivo << "Cedula: "
                << actual->dato.getProfesor().getCedula() << endl;
        archivo << "ID Profesor: "
                << actual->dato.getProfesor().getIdProfesor() << endl;
        archivo << "Especialidad: "
                << actual->dato.getProfesor().getEspecialidad() << endl;

        archivo << "Materia: "
                << actual->dato.getMateria().getNombreMateria() << endl;
        archivo << "NRC: "
                << actual->dato.getMateria().getNRC() << endl;

        archivo << "Horario: "
                << actual->dato.getMateria().getHorario().getHoraInicio()
                << " - "
                << actual->dato.getMateria().getHorario().getHoraFin()
                << endl;

        archivo << "Entrada: "
                << actual->dato.getHoraEntrada() << endl;

        if (actual->dato.tieneSalida()) {
            archivo << "Salida: "
                    << actual->dato.getHoraSalida() << endl;
        }
        else {
            archivo << "Salida: Pendiente" << endl;
        }

        archivo << "----------------------------------------\n";

        actual = actual->siguiente;
    }

    archivo.close();

    return true;
}


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