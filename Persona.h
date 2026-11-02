#ifndef PERSONA_H
#define PERSONA_H

#include <string>
using namespace std;

class Persona {
protected:
    string cedula;
    string nombres;
    string apellidos;

public:
    Persona();
    Persona(string cedula, string nombres, string apellidos);

    string getCedula() const;
    string getNombres() const;
    string getApellidos() const;
    string getNombreCompleto() const;
};

#endif