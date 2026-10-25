#include <iostream>
#include "logica/LectorPacientes.h"
#include "logica/ArbolDecision.h"
#include "logica/ArbolAVL.h"
#include <cassert>
using namespace std;

int main() {
    cout << "=== HOSPITAL MARMAJA ===" << endl;

    ColaPacientes cola;
    ArbolDecision arbol;

    int cargados = LectorPacientes::cargarArchivo(
        "datos/pacientes.txt", cola
    );

    if (cargados == -1) {
        return 1;
    }

    cout << "Pacientes cargados: " << cargados << endl;

    while (!cola.estaVacia()) {
        Paciente paciente = cola.desencolar();

        try {
            auto resultado = arbol.clasificar(paciente);

            cout << "\nPaciente: "
                 << paciente.getNombre() << endl;

            cout << "Ruta: "
                 << resultado.ruta << endl;

            cout << "Servicio: "
                 << nombreServicio(resultado.servicio) << endl;

        } catch (const exception& error) {
            cerr << "Error: " << error.what() << endl;
        }
    }
    
    arbol.mostrarPreorden();
    arbol.mostrarInorden();
    arbol.mostrarPostorden();

    cout << "\n=== PROBANDO AVL ===" << endl;

    ArbolAVL avl;

    Paciente p30("030", "Paciente A", 30, 37,120,2,"otro",false,false,false, 0);

    Paciente p20("020","Paciente B", 30, 37,120,2,"otro",false,false,false, 0);

    Paciente p10("010", "Paciente C", 30, 37, 120, 2, "otro", false, false, false, 0);

    assert(avl.insertar(p30));
    assert(avl.insertar(p20));
    assert(avl.insertar(p10));

    assert(avl.obtenerAltura() == 2);
    assert(avl.buscarPorId("020") != nullptr);
    assert(!avl.insertar(p20));

    avl.mostrarInorden();

    cout << "Altura AVL: " << avl.obtenerAltura() << endl;        
    return 0;
}