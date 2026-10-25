
#pragma once

#include "dominio/Paciente.h"
#include <cstddef>

class ColaPacientes {
private:
    struct Nodo {
        Paciente paciente;
        Nodo* siguiente;

        Nodo(const Paciente& p)
            : paciente(p), siguiente(nullptr) {}
    };

    Nodo* frente;
    Nodo* ultimo;
    std::size_t cantidad;

public:
    ColaPacientes();
    ~ColaPacientes();

    ColaPacientes(const ColaPacientes&) = delete;
    ColaPacientes& operator=(const ColaPacientes&) = delete;

    void encolar(const Paciente& paciente);
    Paciente desencolar();
    bool estaVacia() const;
    std::size_t tamano() const;
};
