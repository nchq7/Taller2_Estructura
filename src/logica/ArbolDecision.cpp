#include "logica/ArbolDecision.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

ArbolDecision::ArbolDecision() {
    raiz = new Nodo(Pregunta::Cirugia);
    Nodo* actual = raiz;

    actual->si = new Nodo(Servicio::Cirugia);
    actual->no = new Nodo(Pregunta::Neurologia);
    actual = actual->no;

    actual->si = new Nodo(Servicio::Neurologia);
    actual->no = new Nodo(Pregunta::Trauma);
    actual = actual->no;

    actual->si = new Nodo(Servicio::Traumatologia);
    actual->no = new Nodo(Pregunta::Urgencia);
    actual = actual->no;

    actual->si = new Nodo(Servicio::Urgencias);
    actual->no = new Nodo(Pregunta::Pecho);
    actual = actual->no;

    actual->si = new Nodo(Servicio::Cardiologia);
    actual->no = new Nodo(Pregunta::Pediatria);
    actual = actual->no;

    actual->si = new Nodo(Servicio::Pediatria);
    actual->no = new Nodo(Pregunta::Hospitalizacion);
    actual = actual->no;

    actual->si = new Nodo(Servicio::Hospitalizacion);
    actual->no = new Nodo(Servicio::MedicinaGeneral);
}

bool ArbolDecision::cumple(Pregunta pregunta, const Paciente& p) {
    switch (pregunta) {
        case Pregunta::Cirugia:
            return p.getRequiereCirugia();

        case Pregunta::Neurologia:
            return p.getSintomasNeurologicos();

        case Pregunta::Trauma:
            return p.getTrauma();

        case Pregunta::Urgencia:
            return p.getTemperatura() >= 38.5 ||
                   p.getDolor() >= 8;

        case Pregunta::Pecho:
            return p.getTipoDolor() == "pecho";

        case Pregunta::Pediatria:
            return p.getEdad() < 14;

        case Pregunta::Hospitalizacion:
            return p.getDiasHospitalizacion() >= 2;
    }

    return false;
}

const char* ArbolDecision::describir(Pregunta pregunta) {
    switch (pregunta) {
        case Pregunta::Cirugia:
            return "RequiereCirugia == 1";
        case Pregunta::Neurologia:
            return "SintomasNeurologicos == 1";
        case Pregunta::Trauma:
            return "Trauma == 1";
        case Pregunta::Urgencia:
            return "Temperatura >= 38.5 o Dolor >= 8";
        case Pregunta::Pecho:
            return "TipoDolor == pecho";
        case Pregunta::Pediatria:
            return "Edad < 14";
        case Pregunta::Hospitalizacion:
            return "DiasHospitalizacion >= 2";
    }

    return "Pregunta desconocida";
}

bool ArbolDecision::datosValidos(const Paciente& p) {
    const std::string tipo = p.getTipoDolor();

    bool tipoValido =
        tipo == "pecho" ||
        tipo == "cabeza" ||
        tipo == "abdomen" ||
        tipo == "extremidad" ||
        tipo == "otro";

    return !p.getId().empty() &&
           !p.getNombre().empty() &&
           p.getEdad() >= 0 && p.getEdad() <= 120 &&
           std::isfinite(p.getTemperatura()) &&
           p.getTemperatura() >= 30 &&
           p.getTemperatura() <= 45 &&
           p.getPresionArterial() >= 50 &&
           p.getPresionArterial() <= 250 &&
           p.getDolor() >= 0 && p.getDolor() <= 10 &&
           p.getDiasHospitalizacion() >= 0 &&
           p.getDiasHospitalizacion() <= 365 &&
           tipoValido;
}

ArbolDecision::Resultado ArbolDecision::clasificar(
    const Paciente& p) const {

    if (!datosValidos(p)) {
        throw std::invalid_argument(
            "Paciente con atributos invalidos"
        );
    }

    Nodo* actual = raiz;
    std::string ruta;

    while (!actual->esHoja) {
        bool respuesta = cumple(actual->pregunta, p);

        if (!ruta.empty()) {
            ruta += " -> ";
        }

        ruta += std::string(describir(actual->pregunta));
        ruta += respuesta ? " [SI]" : " [NO]";

        actual = respuesta ? actual->si : actual->no;
    }

    ruta += " -> ";
    ruta += nombreServicio(actual->servicio);

    return {actual->servicio, ruta};
}

void ArbolDecision::liberar(Nodo* nodo) {
    if (nodo == nullptr) {
        return;
    }

    liberar(nodo->si);
    liberar(nodo->no);

    delete nodo;
}

ArbolDecision::~ArbolDecision() {
    liberar(raiz);
}

void ArbolDecision::imprimirNodo(const Nodo* nodo) {
    if (nodo->esHoja) {
        std::cout << "[Servicio] "
                  << nombreServicio(nodo->servicio) << "\n";
    } else {
        std::cout << "[Pregunta] "
                  << describir(nodo->pregunta) << "\n";
    }
}

void ArbolDecision::preorden(const Nodo* nodo) {
    if (nodo == nullptr) return;

    imprimirNodo(nodo);
    preorden(nodo->si);
    preorden(nodo->no);
}

void ArbolDecision::inorden(const Nodo* nodo) {
    if (nodo == nullptr) return;

    inorden(nodo->si);
    imprimirNodo(nodo);
    inorden(nodo->no);
}

void ArbolDecision::postorden(const Nodo* nodo) {
    if (nodo == nullptr) return;

    postorden(nodo->si);
    postorden(nodo->no);
    imprimirNodo(nodo);
}

void ArbolDecision::mostrarPreorden() const {
    std::cout << "\n=== Preorden ===\n";
    preorden(raiz);
}

void ArbolDecision::mostrarInorden() const {
    std::cout << "\n=== Inorden ===\n";
    inorden(raiz);
}

void ArbolDecision::mostrarPostorden() const {
    std::cout << "\n=== Postorden ===\n";
    postorden(raiz);
}