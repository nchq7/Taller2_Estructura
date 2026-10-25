#pragma once

#include <string>
#include "logica/ColaPacientes.h"

class LectorPacientes {
public:
    static int cargarArchivo(const std::string& ruta,
                             ColaPacientes& cola);
};