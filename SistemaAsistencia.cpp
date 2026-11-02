#include "SistemaAsistencia.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

// Constructor.
SistemaAsistencia::SistemaAsistencia() {
    siguienteId = 1;
}

// Leer texto obligatorio.
string SistemaAsistencia::leerTexto(string mensaje) {
    string dato;

    do {
        cout << mensaje;
        getline(cin, dato);

        if (dato.empty()) {
            cout << "Error: el campo no puede estar vacio.\n";
        }

    } while (dato.empty());

    return dato;
}

// Leer solamente numeros.
string SistemaAsistencia::leerNumero(string mensaje) {
    string dato;
    bool valido;

    do {
        cout << mensaje;
        getline(cin, dato);

        valido = !dato.empty();

        for (int i = 0; i < (int)dato.length(); i++) {
            if (dato[i] < '0' || dato[i] > '9') {
                valido = false;
                break;
            }
        }

        if (!valido) {
            cout << "Error: ingrese solamente numeros.\n";
        }

    } while (!valido);

    return dato;
}

// Leer y validar hora.
string SistemaAsistencia::leerHora(string mensaje) {
    string hora;

    while (true) {
        try {
            hora = leerTexto(mensaje);
            Horario::convertirHora(hora);
            return hora;
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
}

// Registrar entrada.
void SistemaAsistencia::registrarEntrada() {
    try {
        cout << "\n======= REGISTRAR ENTRADA =======\n";

        string idProfesor = leerNumero("ID del profesor: ");
        string NRC = leerNumero("NRC de la materia: ");

        if (lista.buscarPendiente(idProfesor, NRC) != nullptr) {
            cout << "\nEste profesor ya tiene un registro para esta materia.\n";
            return;
        }

        string cedula = leerNumero("Cedula: ");
        string nombres = leerTexto("Nombres: ");
        string apellidos = leerTexto("Apellidos: ");
        string especialidad = leerTexto("Especialidad: ");

        string nombreMateria = leerTexto("Nombre de la materia: ");

        string idHorario = leerNumero("ID del horario: ");
        string horaInicio = leerHora("Hora de inicio (HH:MM): ");
        string horaFin = leerHora("Hora de fin (HH:MM): ");

        Horario horario(idHorario, horaInicio, horaFin);

        string horaEntrada = leerHora("Hora de entrada (HH:MM): ");

        if (!horario.validarEntrada(horaEntrada)) {
            int inicio = Horario::convertirHora(horaInicio);

            cout << "\nEntrada rechazada.\n";
            cout << "Horario permitido: ";

            int limiteInicio = inicio - 10;
            int limiteFin = inicio + 10;

            cout << setfill('0')
                 << setw(2) << limiteInicio / 60 << ":"
                 << setw(2) << limiteInicio % 60;

            cout << " hasta ";

            cout << setw(2) << limiteFin / 60 << ":"
                 << setw(2) << limiteFin % 60 << endl;

            cout << setfill(' ');
            return;
        }

        Profesor profesor(
            cedula, nombres, apellidos,
            idProfesor, especialidad
        );

        Materia materia(NRC, nombreMateria, horario);

        RegistroAsistencia registro(
            siguienteId, profesor, materia, horaEntrada
        );

        lista.insertar(registro);

        siguienteId++;

        cout << "\nEntrada registrada correctamente.\n";
    }
    catch (const exception& e) {
        cout << "\nError: " << e.what() << endl;
    }
}

// Registrar salida.
void SistemaAsistencia::registrarSalida() {
    try {
        cout << "\n======= REGISTRAR SALIDA =======\n";

        string idProfesor = leerNumero("ID del profesor: ");
        string NRC = leerNumero("NRC de la materia: ");

        RegistroAsistencia* registro =
            lista.buscarPendiente(idProfesor, NRC);

        if (registro == nullptr) {
            cout << "\nNo existe una entrada registrada para estos datos.\n";
            return;
        }

        if (registro->tieneSalida()) {
            cout << "\nLa salida ya fue registrada anteriormente.\n";
            return;
        }

        string horaSalida = leerHora("Hora de salida (HH:MM): ");

        Horario horario = registro->getMateria().getHorario();

        if (!horario.validarSalida(horaSalida)) {
            cout << "\nSalida rechazada. Fuera del rango permitido.\n";
            cout << "Horario de salida: " << horario.getHoraFin()
                 << " con tolerancia de +/- 10 minutos.\n";
            return;
        }

        int entrada = Horario::convertirHora(
            registro->getHoraEntrada()
        );

        int salida = Horario::convertirHora(horaSalida);

        if (salida <= entrada) {
            cout << "\nLa salida debe ser posterior a la entrada.\n";
            return;
        }

        registro->registrarSalida(horaSalida);

        cout << "\nSalida registrada correctamente.\n";
    }
    catch (const exception& e) {
        cout << "\nError: " << e.what() << endl;
    }
}

// Consultar registros.
void SistemaAsistencia::consultarRegistros() {
    cout << "\n======= CONSULTAR REGISTROS =======\n";

    string idProfesor = leerNumero("Ingrese el ID del profesor: ");

    lista.consultarProfesor(idProfesor);
}

// Eliminar registro.
void SistemaAsistencia::eliminarRegistro() {
    cout << "\n======= ELIMINAR REGISTRO =======\n";

    string dato = leerNumero("Ingrese el ID del registro: ");

    try {
        int id = stoi(dato);

        if (lista.eliminar(id)) {
            cout << "\nRegistro eliminado correctamente.\n";
        }
        else {
            cout << "\nNo se encontro el registro indicado.\n";
        }
    }
    catch (const exception&) {
        cout << "\nEl identificador es demasiado grande.\n";
    }
}

// Imprimir lista.
void SistemaAsistencia::imprimirLista() {
    lista.imprimir();
}

// Menú principal.
void SistemaAsistencia::menuPrincipal() {
    string opcion;

    do {
        cout << "\n====================================\n";
        cout << "     SISTEMA DE ASISTENCIA DOCENTE\n";
        cout << "====================================\n";
        cout << "1. Registrar entrada\n";
        cout << "2. Registrar salida\n";
        cout << "3. Consultar registros\n";
        cout << "4. Eliminar registro\n";
        cout << "5. Imprimir lista de asistencias\n";
        cout << "0. Salir\n";
        cout << "====================================\n";
        cout << "Seleccione una opcion: ";

        getline(cin, opcion);

        if (opcion == "1") {
            registrarEntrada();
        }
        else if (opcion == "2") {
            registrarSalida();
        }
        else if (opcion == "3") {
            consultarRegistros();
        }
        else if (opcion == "4") {
            eliminarRegistro();
        }
        else if (opcion == "5") {
            imprimirLista();
        }
        else if (opcion == "0") {
            cout << "\nSaliendo del sistema...\n";
        }
        else {
            cout << "\nOpcion incorrecta. Intente nuevamente.\n";
        }

    } while (opcion != "0");
}