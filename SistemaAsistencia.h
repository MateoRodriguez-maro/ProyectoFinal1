#ifndef SISTEMAASISTENCIA_H
#define SISTEMAASISTENCIA_H

#include "ListaDoble.h"
#include <string>

using namespace std;

class SistemaAsistencia {
private:
    ListaDoble lista;
    int siguienteId;

    string leerTexto(string mensaje);
    string leerNumero(string mensaje);
    string leerHora(string mensaje);
    string leerCedula(string mensaje);
    string leerNombre(string mensaje);

    bool validarCedulaEcuatoriana(string cedula);
    bool validarNombre(string nombre);

public:
    SistemaAsistencia();

    void registrarEntrada();
    void registrarSalida();

    void consultarRegistros();
    void eliminarRegistro();
    void imprimirLista();

    void menuPrincipal();
};

#endif