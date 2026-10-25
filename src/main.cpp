#include <iostream>
#include "logica/LectorPacientes.h"
#include "logica/ArbolDecision.h"

using namespace std;

int main() {
    cout << "=== HOSPITAL MARMAJA ===" << endl;

    ColaPacientes cola;
    ArbolDecision arbol;

    int cargados = LectorPacientes::cargarArchivo(
        "datos/pacientes.txt", cola
    );

    if (cargados == -1) {
        return 1;
    }

    cout << "Pacientes cargados: " << cargados << endl;

    while (!cola.estaVacia()) {
        Paciente paciente = cola.desencolar();

        try {
            auto resultado = arbol.clasificar(paciente);

            cout << "\nPaciente: "
                 << paciente.getNombre() << endl;

            cout << "Ruta: "
                 << resultado.ruta << endl;

            cout << "Servicio: "
                 << nombreServicio(resultado.servicio) << endl;

        } catch (const exception& error) {
            cerr << "Error: " << error.what() << endl;
        }
    }

    return 0;
}