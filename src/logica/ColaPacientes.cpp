
#include "logica/ColaPacientes.h"
#include <stdexcept>

ColaPacientes::ColaPacientes() {
    frente = nullptr;
    ultimo = nullptr;
    cantidad = 0;
}

void ColaPacientes::encolar(const Paciente& paciente) {
    Nodo* nuevo = new Nodo(paciente);

    if (estaVacia()) {
        frente = nuevo;
        ultimo = nuevo;
    } else {
        ultimo->siguiente = nuevo;
        ultimo = nuevo;
    }

    cantidad++;
}

Paciente ColaPacientes::desencolar() {
    if (estaVacia()) {
        throw std::underflow_error("La cola esta vacia");
    }

    Nodo* temporal = frente;
    Paciente paciente = temporal->paciente;

    frente = frente->siguiente;

    if (frente == nullptr) {
        ultimo = nullptr;
    }

    delete temporal;
    cantidad--;

    return paciente;
}

bool ColaPacientes::estaVacia() const {
    return frente == nullptr;
}

std::size_t ColaPacientes::tamano() const {
    return cantidad;
}

ColaPacientes::~ColaPacientes() {
    while (frente != nullptr) {
        Nodo* temporal = frente;
        frente = frente->siguiente;
        delete temporal;
    }

    ultimo = nullptr;
    cantidad = 0;
}
