
#include <iostream>
#include <string>
#include <limits>
#include "logica/Hospital.h"
#include "logica/LectorPacientes.h"

using namespace std;

int main() {
    Hospital hospital;
    ColaPacientes cola;

    int cargados = LectorPacientes::cargarArchivo(
        "datos/pacientes.txt", cola
    );

    if (cargados >= 0) {
        cout << "Pacientes en espera: "
             << cargados << "\n";
    } else {
        cout << "No se pudo cargar el archivo.\n";
    }

    int opcion = 0;

    do {
        cout << "\n=== HOSPITAL MARMAJA ===\n";
        cout << "1. Atender pacientes\n";
        cout << "2. Ver departamentos\n";
        cout << "3. Buscar paciente\n";
        cout << "4. Eliminar paciente\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion)) {
            if (cin.eof()) break;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opcion invalida.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1: {
                cout << "\n=== ATENDIENDO PACIENTES ===\n";

                int atendidos = hospital.atenderPacientes(cola);

                cout << "\nPacientes atendidos: "
                     << atendidos << "\n";
                break;
            }

            case 2: {
                hospital.mostrarDepartamentos();
                break;
            }

            case 3: {
                string consulta;
                cout << "Ingrese ID o nombre: ";
                getline(cin, consulta);

                Servicio servicio = Servicio::MedicinaGeneral;

                const Paciente* paciente =
                    hospital.buscarPorId(consulta, servicio);

                if (paciente == nullptr) {
                    paciente = hospital.buscarPorNombre(
                        consulta, servicio
                    );
                }

                if (paciente == nullptr) {
                    cout << "Paciente no encontrado.\n";
                } else {
                    cout << "\nPaciente encontrado:\n";
                    cout << "ID: " << paciente->getId() << "\n";
                    cout << "Nombre: "
                         << paciente->getNombre() << "\n";
                    cout << "Edad: "
                         << paciente->getEdad() << "\n";
                    cout << "Temperatura: "
                         << paciente->getTemperatura() << "\n";
                    cout << "Presion: "
                         << paciente->getPresionArterial() << "\n";
                    cout << "Dolor: "
                         << paciente->getDolor() << "\n";
                    cout << "Tipo dolor: "
                         << paciente->getTipoDolor() << "\n";
                    cout << "Trauma: "
                         << paciente->getTrauma() << "\n";
                    cout << "Sintomas neurologicos: "
                         << paciente->getSintomasNeurologicos() << "\n";
                    cout << "Requiere cirugia: "
                         << paciente->getRequiereCirugia() << "\n";
                    cout << "Dias hospitalizacion: "
                         << paciente->getDiasHospitalizacion() << "\n";
                    cout << "Servicio: "
                         << nombreServicio(servicio) << "\n";
                }
                break;
            }

            case 4: {
                string id;
                cout << "ID del paciente a eliminar: ";
                getline(cin, id);

                if (hospital.eliminarPaciente(id)) {
                    cout << "Paciente eliminado correctamente.\n";
                } else {
                    cout << "Paciente no encontrado.\n";
                }
                break;
            }

            case 5:
                cout << "Saliendo del hospital...\n";
                break;

            default:
                cout << "Opcion no valida.\n";
                break;
        }

    } while (opcion != 5);

    return 0;
}
