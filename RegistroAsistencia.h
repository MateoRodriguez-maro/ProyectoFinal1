#ifndef REGISTROASISTENCIA_H
#define REGISTROASISTENCIA_H

#include "Profesor.h"
#include "Materia.h"
#include <string>

using namespace std;

class RegistroAsistencia {
private:
    int idRegistro;
    Profesor profesor;
    Materia materia;
    string horaEntrada;
    string horaSalida;
    

public:
    RegistroAsistencia(int idRegistro, Profesor profesor,
                       Materia materia, string horaEntrada);

    int getIdRegistro() const;
    Profesor getProfesor() const;
    Materia getMateria() const;

    string getHoraEntrada() const;
    string getHoraSalida() const;

    bool tieneSalida() const;
    void registrarSalida(string hora);

    void imprimir() const;
};

#endif