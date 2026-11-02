#ifndef PROFESOR_H
#define PROFESOR_H

#include "Persona.h"
#include <string>

class Profesor : public Persona {
private:
    string idProfesor;
    string especialidad;

public:
    Profesor();
    Profesor(string cedula, string nombres, string apellidos,
             string idProfesor, string especialidad);

    string getIdProfesor() const;
    string getEspecialidad() const;
};

#endif