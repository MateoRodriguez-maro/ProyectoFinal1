#ifndef MATERIA_H
#define MATERIA_H

#include <string>
#include "Horario.h"

using namespace std;

class Materia {
private:
    string NRC;
    string nombreMateria;
    Horario horario;

public:
    Materia();
    Materia(string NRC, string nombreMateria, Horario horario);

    string getNRC() const;
    string getNombreMateria() const;
    Horario getHorario() const;
};

#endif