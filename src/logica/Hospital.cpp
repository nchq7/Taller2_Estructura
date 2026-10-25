
#include "logica/Hospital.h"
#include <iostream>
#include <exception>

int Hospital::indice(Servicio servicio) {
    return static_cast<int>(servicio);
}

const Paciente* Hospital::buscarPorId(
    const std::string& id, Servicio& servicio) const {

    for (int i = 0; i < 8; i++) {
        const Paciente* paciente =
            departamentos[i].buscarPorId(id);

        if (paciente != nullptr) {
            servicio = static_cast<Servicio>(i);
            return paciente;
        }
    }

    return nullptr;
}

const Paciente* Hospital::buscarPorNombre(
    const std::string& nombre, Servicio& servicio) const {

    for (int i = 0; i < 8; i++) {
        const Paciente* paciente =
            departamentos[i].buscarPorNombre(nombre);

        if (paciente != nullptr) {
            servicio = static_cast<Servicio>(i);
            return paciente;
        }
    }

    return nullptr;
}

int Hospital::atenderPacientes(ColaPacientes& cola) {
    int procesados = 0;

    while (!cola.estaVacia()) {
        Paciente paciente = cola.desencolar();

        Servicio servicioExistente;

        if (buscarPorId(paciente.getId(),
                        servicioExistente) != nullptr) {
            std::cout << "ID duplicado: "
                      << paciente.getId() << "\n";
            continue;
        }

        try {
            auto resultado = arbolDecision.clasificar(paciente);

            ArbolAVL& arbol =
                departamentos[indice(resultado.servicio)];

            if (arbol.insertar(paciente)) {
                std::cout << "\nPaciente: "
                          << paciente.getNombre() << "\n";
                std::cout << "Ruta: "
                          << resultado.ruta << "\n";
                std::cout << "Servicio asignado: "
                          << nombreServicio(resultado.servicio)
                          << "\n";

                procesados++;
            }
        }
        catch (const std::exception& error) {
            std::cerr << "No se pudo procesar el ID "
                      << paciente.getId() << ": "
                      << error.what() << "\n";
        }
    }

    return procesados;
}

bool Hospital::eliminarPaciente(const std::string& id) {
    Servicio servicio;

    if (buscarPorId(id, servicio) == nullptr) {
        return false;
    }

    return departamentos[indice(servicio)].eliminar(id);
}

void Hospital::mostrarDepartamentos() const {
    std::cout << "\n=== ESTADO DE LOS DEPARTAMENTOS ===\n";

    for (int i = 0; i < 8; i++) {
        Servicio servicio = static_cast<Servicio>(i);

        std::cout << "\n--- "
                  << nombreServicio(servicio)
                  << " ---\n";

        const ArbolAVL& arbol = departamentos[i];

        if (arbol.obtenerAltura() == 0) {
            std::cout << "Sin pacientes\n";
            continue;
        }

        std::cout << "Inorden:\n";
        arbol.mostrarInorden();

        arbol.mostrarPreorden();
        arbol.mostrarPostorden();

        std::cout << "Altura: "
                  << arbol.obtenerAltura() << "\n";

        arbol.mostrarFactoresBalance();
    }
}
