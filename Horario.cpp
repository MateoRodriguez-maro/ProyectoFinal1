#include "Horario.h"
#include <sstream>
#include <stdexcept>

const int Horario::TOLERANCIA;

Horario::Horario() {
    idHorario = "";
    horaInicio = "";
    horaFin = "";
}

Horario::Horario(string idHorario, string horaInicio, string horaFin) {
    int inicio = convertirHora(horaInicio);
    int fin = convertirHora(horaFin);

    if (fin <= inicio) {
        throw invalid_argument(
            "La hora de fin debe ser posterior a la hora de inicio."
        );
    }

    this->idHorario = idHorario;
    this->horaInicio = horaInicio;
    this->horaFin = horaFin;
}

int Horario::convertirHora(string hora) {
    int horas, minutos;
    char separador;

    stringstream flujo(hora);

    if (!(flujo >> horas >> separador >> minutos) ||
        separador != ':' || !flujo.eof() ||
        horas < 0 || horas > 23 ||
        minutos < 0 || minutos > 59) {

        throw invalid_argument("Formato incorrecto. Utilice HH:MM.");
    }

    return horas * 60 + minutos;
}

string Horario::getIdHorario() const {
    return idHorario;
}

string Horario::getHoraInicio() const {
    return horaInicio;
}

string Horario::getHoraFin() const {
    return horaFin;
}

bool Horario::validarEntrada(string hora) const {
    int registro = convertirHora(hora);
    int inicio = convertirHora(horaInicio);

    return registro >= inicio - TOLERANCIA &&
           registro <= inicio + TOLERANCIA;
}

bool Horario::validarSalida(string hora) const {
    int registro = convertirHora(hora);
    int fin = convertirHora(horaFin);

    return registro >= fin - TOLERANCIA &&
           registro <= fin + TOLERANCIA;
}