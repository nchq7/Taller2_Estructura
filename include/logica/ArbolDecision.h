#pragma once

#include "dominio/Paciente.h"
#include "dominio/Servicio.h"
#include <string>

class ArbolDecision{
public:
    struct Resultado{
        Servicio servicio;
        std::string ruta;
    };

    ArbolDecision();
    ~ArbolDecision();

    ArbolDecision(const ArbolDecision&) = delete;
    ArbolDecision& operator=(const ArbolDecision&) = delete;

    Resultado clasificar(const Paciente& paciente) const;

private:
     enum class Pregunta {
        Cirugia,
        Neurologia,
        Trauma,
        Urgencia,
        Pecho,
        Pediatria,
        Hospitalizacion
    };

    struct Nodo{
        bool esHoja;
        Pregunta pregunta;
        Servicio servicio;
        Nodo* si;
        Nodo* no;

        explicit Nodo(Pregunta p)
            : esHoja(false), pregunta(p),
              servicio(Servicio::MedicinaGeneral),
              si(nullptr), no(nullptr) {}

        explicit Nodo(Servicio s)
            : esHoja(true), pregunta(Pregunta::Cirugia),
              servicio(s), si(nullptr), no(nullptr) {}
    };

    Nodo* raiz;

    static bool cumple(Pregunta pregunta, const Paciente& paciente);
    static const char* describir(Pregunta pregunta);
    static bool datosValidos(const Paciente& paciente);
    static void liberar(Nodo* nodo);
};