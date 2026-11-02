#ifndef HORARIO_H
#define HORARIO_H

#include <string>
using namespace std;

class Horario {
private:
    string idHorario;
    string horaInicio;
    string horaFin;

    static const int TOLERANCIA = 10;

public:
    Horario();
    Horario(string idHorario, string horaInicio, string horaFin);

    string getIdHorario() const;
    string getHoraInicio() const;
    string getHoraFin() const;

    static int convertirHora(string hora);

    bool validarEntrada(string hora) const;
    bool validarSalida(string hora) const;
};

#endif