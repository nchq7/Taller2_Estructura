#include <iostream>
#include "dominio/Paciente.h"

using namespace std;

int main() {
    Paciente paciente("001", "Juan Perez", 25, 37.0, 120,
                      3, "otro", false, false, false, 0);

    cout << "=== HOSPITAL MARMAJA ===" << endl;
    cout << "ID: " << paciente.getId() << endl;
    cout << "Nombre: " << paciente.getNombre() << endl;
    cout << "Edad: " << paciente.getEdad() << endl;
    cout << "Temperatura: " << paciente.getTemperatura() << endl;

    return 0;
}