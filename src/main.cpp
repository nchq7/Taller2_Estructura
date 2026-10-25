#include <iostream>
#include "logica/LectorPacientes.h"
#include "logica/ColaPacientes.h"

using namespace std;

int main() {
    cout << "=== HOSPITAL MARMAJA ===" << endl;

    ColaPacientes cola;

    int cargados = LectorPacientes::cargarArchivo(
        "datos/pacientes.txt", cola
    );

    if (cargados == -1) {
        return 1;
    }

    cout << "Pacientes cargados: " << cargados << endl;

    cout << "\n=== COLA DE PACIENTES ===" << endl;

    while (!cola.estaVacia()) {
        Paciente paciente = cola.desencolar();

        cout << paciente.getId() << " - "
             << paciente.getNombre() << endl;
    }

    return 0;
}