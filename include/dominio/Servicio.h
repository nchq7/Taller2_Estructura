#pragma once

enum class Servicio {
    Urgencias,
    MedicinaGeneral,
    Cardiologia,
    Neurologia,
    Traumatologia,
    Cirugia,
    Pediatria,
    Hospitalizacion
};

inline const char* nombreServicio(Servicio s) {
    switch (s) {
        case Servicio::Urgencias: return "Urgencias";
        case Servicio::MedicinaGeneral: return "Medicina General";
        case Servicio::Cardiologia: return "Cardiologia";
        case Servicio::Neurologia: return "Neurologia";
        case Servicio::Traumatologia: return "Traumatologia";
        case Servicio::Cirugia: return "Cirugia";
        case Servicio::Pediatria: return "Pediatria";
        case Servicio::Hospitalizacion: return "Hospitalizacion";
    }

    return "Servicio desconocido";
}