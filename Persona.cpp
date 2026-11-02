#include "Persona.h"

Persona::Persona() {
    cedula = "";
    nombres = "";
    apellidos = "";
}

Persona::Persona(string cedula, string nombres, string apellidos) {
    this->cedula = cedula;
    this->nombres = nombres;
    this->apellidos = apellidos;
}

string Persona::getCedula() const {
    return cedula;
}

string Persona::getNombres() const {
    return nombres;
}

string Persona::getApellidos() const {
    return apellidos;
}

string Persona::getNombreCompleto() const {
    return nombres + " " + apellidos;
}