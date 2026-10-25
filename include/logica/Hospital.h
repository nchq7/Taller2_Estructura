#pragma once

#include "dominio/Paciente.h"
#include "dominio/Servicio.h"
#include "logica/ArbolAVL.h"
#include "logica/ArbolDecision.h"
#include "logica/ColaPacientes.h"
#include <string>

class Hospital {
private:
    ArbolAVL departamentos[8];
    ArbolDecision arbolDecision;

    static int indice(Servicio servicio);

public:
    int atenderPacientes(ColaPacientes& cola);

    const Paciente* buscarPorId(
        const std::string& id,
        Servicio& servicio) const;

    const Paciente* buscarPorNombre(
        const std::string& nombre,
        Servicio& servicio) const;

    bool eliminarPaciente(const std::string& id);
    void mostrarDepartamentos() const;
};
