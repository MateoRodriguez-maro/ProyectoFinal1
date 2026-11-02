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