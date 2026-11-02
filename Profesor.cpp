#include "Profesor.h"

Profesor::Profesor() {
    idProfesor = "";
    especialidad = "";
}

Profesor::Profesor(string cedula, string nombres, string apellidos,
                   string idProfesor, string especialidad)
    : Persona(cedula, nombres, apellidos) {

    this->idProfesor = idProfesor;
    this->especialidad = especialidad;
}

string Profesor::getIdProfesor() const {
    return idProfesor;
}

string Profesor::getEspecialidad() const {
    return especialidad;
}