
#include "logica/ArbolAVL.h"
#include <algorithm>
#include <iostream>

ArbolAVL::ArbolAVL() : raiz(nullptr) {}

int ArbolAVL::obtenerAlturaNodo(Nodo* nodo) {
    return nodo == nullptr ? 0 : nodo->altura;
}

int ArbolAVL::factorBalance(Nodo* nodo) {
    if (nodo == nullptr) return 0;

    return obtenerAlturaNodo(nodo->izquierdo) -
           obtenerAlturaNodo(nodo->derecho);
}

void ArbolAVL::actualizarAltura(Nodo* nodo) {
    if (nodo == nullptr) return;

    nodo->altura = 1 + std::max(
        obtenerAlturaNodo(nodo->izquierdo),
        obtenerAlturaNodo(nodo->derecho)
    );
}

ArbolAVL::Nodo* ArbolAVL::rotarDerecha(Nodo* y) {
    Nodo* x = y->izquierdo;
    Nodo* temporal = x->derecho;

    x->derecho = y;
    y->izquierdo = temporal;

    actualizarAltura(y);
    actualizarAltura(x);

    return x;
}

ArbolAVL::Nodo* ArbolAVL::rotarIzquierda(Nodo* x) {
    Nodo* y = x->derecho;
    Nodo* temporal = y->izquierdo;

    y->izquierdo = x;
    x->derecho = temporal;

    actualizarAltura(x);
    actualizarAltura(y);

    return y;
}

ArbolAVL::Nodo* ArbolAVL::insertarRec(
    Nodo* nodo, const Paciente& paciente, bool& insertado) {

    if (nodo == nullptr) {
        insertado = true;
        return new Nodo(paciente);
    }

    if (paciente.getId() < nodo->paciente.getId()) {
        nodo->izquierdo = insertarRec(
            nodo->izquierdo, paciente, insertado
        );
    }
    else if (paciente.getId() > nodo->paciente.getId()) {
        nodo->derecho = insertarRec(
            nodo->derecho, paciente, insertado
        );
    }
    else {
        return nodo;
    }

    actualizarAltura(nodo);

    int balance = factorBalance(nodo);

    if (balance > 1) {
        if (factorBalance(nodo->izquierdo) < 0) {
            nodo->izquierdo =
                rotarIzquierda(nodo->izquierdo);
        }

        return rotarDerecha(nodo);
    }

    if (balance < -1) {
        if (factorBalance(nodo->derecho) > 0) {
            nodo->derecho =
                rotarDerecha(nodo->derecho);
        }

        return rotarIzquierda(nodo);
    }

    return nodo;
}

bool ArbolAVL::insertar(const Paciente& paciente) {
    bool insertado = false;
    raiz = insertarRec(raiz, paciente, insertado);
    return insertado;
}

const Paciente* ArbolAVL::buscarPorId(
    const std::string& id) const {

    Nodo* actual = raiz;

    while (actual != nullptr) {
        if (id == actual->paciente.getId()) {
            return &actual->paciente;
        }

        if (id < actual->paciente.getId()) {
            actual = actual->izquierdo;
        } else {
            actual = actual->derecho;
        }
    }

    return nullptr;
}

void ArbolAVL::recorrerInorden(const Nodo* nodo) {
    if (nodo == nullptr) return;

    recorrerInorden(nodo->izquierdo);

    std::cout << nodo->paciente.getId()
              << " - " << nodo->paciente.getNombre()
              << "\n";

    recorrerInorden(nodo->derecho);
}

void ArbolAVL::mostrarInorden() const {
    recorrerInorden(raiz);
}

int ArbolAVL::obtenerAltura() const {
    return obtenerAlturaNodo(raiz);
}

void ArbolAVL::liberar(Nodo* nodo) {
    if (nodo == nullptr) return;

    liberar(nodo->izquierdo);
    liberar(nodo->derecho);

    delete nodo;
}

ArbolAVL::~ArbolAVL() {
    liberar(raiz);
}

ArbolAVL::Nodo* ArbolAVL::buscarMenor(Nodo* nodo) {
    Nodo* actual = nodo;

    while (actual->izquierdo != nullptr) {
        actual = actual->izquierdo;
    }

    return actual;
}

ArbolAVL::Nodo* ArbolAVL::eliminarRec(
    Nodo* nodo, const std::string& id, bool& eliminado) {

    if (nodo == nullptr) {
        return nullptr;
    }

    if (id < nodo->paciente.getId()) {
        nodo->izquierdo = eliminarRec(
            nodo->izquierdo, id, eliminado
        );
    }
    else if (id > nodo->paciente.getId()) {
        nodo->derecho = eliminarRec(
            nodo->derecho, id, eliminado
        );
    }
    else {
        eliminado = true;
        if (nodo->izquierdo == nullptr ||
            nodo->derecho == nullptr) {

            Nodo* hijo = nodo->izquierdo != nullptr
                       ? nodo->izquierdo
                       : nodo->derecho;

            delete nodo;
            return hijo;
        }

        Nodo* sucesor = buscarMenor(nodo->derecho);

        std::string idSucesor = sucesor->paciente.getId();
        nodo->paciente = sucesor->paciente;

        bool eliminadoSucesor = false;
        nodo->derecho = eliminarRec(
            nodo->derecho, idSucesor, eliminadoSucesor
        );
    }

    actualizarAltura(nodo);

    int balance = factorBalance(nodo);
    if (balance > 1) {
        if (factorBalance(nodo->izquierdo) < 0) {
            nodo->izquierdo =
                rotarIzquierda(nodo->izquierdo);
        }

        return rotarDerecha(nodo);
    }

    if (balance < -1) {
        if (factorBalance(nodo->derecho) > 0) {
            nodo->derecho =
                rotarDerecha(nodo->derecho);
        }

        return rotarIzquierda(nodo);
    }

    return nodo;
}

bool ArbolAVL::eliminar(const std::string& id) {
    bool eliminado = false;
    raiz = eliminarRec(raiz, id, eliminado);
    return eliminado;
}

const Paciente* ArbolAVL::buscarNombreRec(
    const Nodo* nodo, const std::string& nombre) {

    if (nodo == nullptr) {
        return nullptr;
    }

    if (nodo->paciente.getNombre() == nombre) {
        return &nodo->paciente;
    }

    const Paciente* encontrado = buscarNombreRec(
        nodo->izquierdo, nombre
    );

    if (encontrado != nullptr) {
        return encontrado;
    }

    return buscarNombreRec(nodo->derecho, nombre);
}

const Paciente* ArbolAVL::buscarPorNombre(
    const std::string& nombre) const {

    return buscarNombreRec(raiz, nombre);
}

void ArbolAVL::recorrerPreorden(const Nodo* nodo) {
    if (nodo == nullptr) return;

    std::cout << nodo->paciente.getId()
              << " - " << nodo->paciente.getNombre()
              << "\n";

    recorrerPreorden(nodo->izquierdo);
    recorrerPreorden(nodo->derecho);
}

void ArbolAVL::recorrerPostorden(const Nodo* nodo) {
    if (nodo == nullptr) return;

    recorrerPostorden(nodo->izquierdo);
    recorrerPostorden(nodo->derecho);

    std::cout << nodo->paciente.getId()
              << " - " << nodo->paciente.getNombre()
              << "\n";
}

void ArbolAVL::mostrarPreorden() const {
    std::cout << "\n=== AVL PREORDEN ===\n";
    recorrerPreorden(raiz);
}

void ArbolAVL::mostrarPostorden() const {
    std::cout << "\n=== AVL POSTORDEN ===\n";
    recorrerPostorden(raiz);
}

void ArbolAVL::mostrarBalancesRec(Nodo* nodo) {
    if (nodo == nullptr) return;

    mostrarBalancesRec(nodo->izquierdo);

    std::cout << "ID: " << nodo->paciente.getId()
              << " | Altura: " << nodo->altura
              << " | Balance: " << factorBalance(nodo)
              << "\n";

    mostrarBalancesRec(nodo->derecho);
}

void ArbolAVL::mostrarFactoresBalance() const {
    std::cout << "\n=== FACTORES DE BALANCE ===\n";
    mostrarBalancesRec(raiz);
}
