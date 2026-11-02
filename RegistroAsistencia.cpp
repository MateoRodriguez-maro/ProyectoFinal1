#include "RegistroAsistencia.h"
#include <iostream>

RegistroAsistencia::RegistroAsistencia(
    int idRegistro,
    Profesor profesor,
    Materia materia,
    string horaEntrada
) {
    this->idRegistro = idRegistro;
    this->profesor = profesor;
    this->materia = materia;
    this->horaEntrada = horaEntrada;
    this->horaSalida = "";
}

int RegistroAsistencia::getIdRegistro() const {
    return idRegistro;
}

Profesor RegistroAsistencia::getProfesor() const {
    return profesor;
}

Materia RegistroAsistencia::getMateria() const {
    return materia;
}

string RegistroAsistencia::getHoraEntrada() const {
    return horaEntrada;
}

string RegistroAsistencia::getHoraSalida() const {
    return horaSalida;
}

bool RegistroAsistencia::tieneSalida() const {
    return !horaSalida.empty();
}

void RegistroAsistencia::registrarSalida(string hora) {
    horaSalida = hora;
}

void RegistroAsistencia::imprimir() const {
    cout << "\n----------------------------------------\n";
    cout << "ID Registro: " << idRegistro << endl;
    cout << "Profesor: " << profesor.getNombreCompleto() << endl;
    cout << "Cedula: " << profesor.getCedula() << endl;
    cout << "ID Profesor: " << profesor.getIdProfesor() << endl;
    cout << "Especialidad: " << profesor.getEspecialidad() << endl;
    cout << "Materia: " << materia.getNombreMateria() << endl;
    cout << "NRC: " << materia.getNRC() << endl;

    cout << "Horario: "
         << materia.getHorario().getHoraInicio()
         << " - "
         << materia.getHorario().getHoraFin() << endl;

    cout << "Entrada: " << horaEntrada << endl;

    if (tieneSalida()) {
        cout << "Salida: " << horaSalida << endl;
    }
    else {
        cout << "Salida: Pendiente" << endl;
    }

    cout << "----------------------------------------\n";
}