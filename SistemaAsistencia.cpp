
#include "SistemaAsistencia.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>

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

// Validar cedula ecuatoriana.
bool SistemaAsistencia::validarCedulaEcuatoriana(string cedula) {

    if (cedula.length() != 10) {
        return false;
    }

    // Verificar que contenga solamente numeros.
    for (int i = 0; i < 10; i++) {
        if (cedula[i] < '0' || cedula[i] > '9') {
            return false;
        }
    }

    // Verificar provincia.
    int provincia = (cedula[0] - '0') * 10 + (cedula[1] - '0');
    int tercerDigito = cedula[2] - '0';

    if (!((provincia >= 1 && provincia <= 24) || provincia == 30)) {
        return false;
    }

    // Validar tercer digito.
    if (provincia == 30) {
        if (tercerDigito != 4 && tercerDigito != 5) {
            return false;
        }
    }
    else if (tercerDigito > 5) {
        return false;
    }

    // Calcular digito verificador.
    int suma = 0;

    for (int i = 0; i < 9; i++) {
        int valor = cedula[i] - '0';

        if (i % 2 == 0) {
            valor *= 2;

            if (valor > 9) {
                valor -= 9;
            }
        }

        suma += valor;
    }

    int digitoVerificador = (10 - (suma % 10)) % 10;

    return digitoVerificador == (cedula[9] - '0');
}

// Solicitar una cedula valida.
string SistemaAsistencia::leerCedula(string mensaje) {
    string cedula;

    do {
        cedula = leerNumero(mensaje);

        if (!validarCedulaEcuatoriana(cedula)) {
            cout << "Error: la cedula ecuatoriana no es valida.\n";
        }

    } while (!validarCedulaEcuatoriana(cedula));

    return cedula;
}

// Validar nombres y apellidos.
bool SistemaAsistencia::validarNombre(string nombre) {

    if (nombre.empty()) {
        return false;
    }

    bool tieneLetra = false;

    for (int i = 0; i < (int)nombre.length(); i++) {

        unsigned char caracter = nombre[i];

        // Letras normales.
        if ((caracter >= 'A' && caracter <= 'Z') ||
            (caracter >= 'a' && caracter <= 'z')) {

            tieneLetra = true;
        }
        // Permitir espacios.
        else if (caracter == ' ') {
            continue;
        }
        // Permitir tildes, ñ y ü.
        else if (caracter == 0xC3 && i + 1 < (int)nombre.length()) {

            unsigned char siguiente = nombre[i + 1];

            switch (siguiente) {
                case 0x81: // Á
                case 0x89: // É
                case 0x8D: // Í
                case 0x93: // Ó
                case 0x9A: // Ú
                case 0x91: // Ñ
                case 0x9C: // Ü
                case 0xA1: // á
                case 0xA9: // é
                case 0xAD: // í
                case 0xB3: // ó
                case 0xBA: // ú
                case 0xB1: // ñ
                case 0xBC: // ü

                    tieneLetra = true;
                    i++;
                    break;

                default:
                    return false;
            }
        }
        else {
            return false;
        }
    }

    return tieneLetra;
}

// Leer nombres y apellidos.
string SistemaAsistencia::leerNombre(string mensaje) {
    string nombre;

    do {
        cout << mensaje;
        getline(cin, nombre);

        if (!validarNombre(nombre)) {
            cout << "Error: ingrese solamente letras y espacios.\n";
        }

    } while (!validarNombre(nombre));

    return nombre;
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
        string cedula = leerCedula("Cedula: ");

        if (lista.existeRegistroActivo(idProfesor, cedula)) {
        cout << "\nError: el profesor tiene una asistencia pendiente de salida.\n";
        cout << "Primero debe registrar la salida de su materia anterior.\n";
        return;
        }  //desde aqui
        string nombres = leerNombre("Nombres: ");
        string apellidos = leerNombre("Apellidos: ");
        string especialidad = leerNombre("Especialidad: ");

        string nombreMateria = leerNombre("Nombre de la materia: ");

        string idHorario = "H" + NRC;
        string horaInicio = leerHora("Hora de inicio (HH:MM): ");
        string horaFin = leerHora("Hora de fin (HH:MM): ");

        
        Horario horario(idHorario, horaInicio, horaFin);

// Ve si hay misma materia 
        if (lista.existeNRCyHorario(NRC, horaInicio, horaFin)) {
        cout << "\nError: ya existe una materia registrada con ese NRC y horario.\n";
        return;
        }


        string horaEntrada = leerHora("Hora de entrada (HH:MM): ");


        int minutosEntrada = Horario::convertirHora(horaEntrada);

        if (minutosEntrada < Horario::convertirHora("07:00") ||
        minutosEntrada > Horario::convertirHora("19:00")) {

        cout << "\nError: no se permiten registros fuera del horario general.\n";
        cout << "El horario permitido es de 07:00 a 19:00.\n";
        return;
        }

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

// Menu principal.
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
