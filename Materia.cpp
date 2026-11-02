#include "Materia.h"

Materia::Materia() {
    NRC = "";
    nombreMateria = "";
}

Materia::Materia(string NRC, string nombreMateria, Horario horario) {
    this->NRC = NRC;
    this->nombreMateria = nombreMateria;
    this->horario = horario;
}

string Materia::getNRC() const {
    return NRC;
}

string Materia::getNombreMateria() const {
    return nombreMateria;
}

Horario Materia::getHorario() const {
    return horario;
}