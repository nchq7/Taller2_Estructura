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

    auto crearPaciente = [](const std::string& id) {
        return Paciente(id, "Paciente " + id,
                        30, 37.0, 120, 2, "otro",
                        false, false, false, 0);
    };

    auto probarRotacion = [&](const std::string& a,
                            const std::string& b,
                            const std::string& c) {
        ArbolAVL arbol;

        assert(arbol.insertar(crearPaciente(a)));
        assert(arbol.insertar(crearPaciente(b)));
        assert(arbol.insertar(crearPaciente(c)));

        assert(arbol.obtenerAltura() == 2);
        assert(arbol.buscarPorId("020") != nullptr);
    };

    probarRotacion("030", "020", "010");
    probarRotacion("010", "020", "030"); 
    probarRotacion("030", "010", "020"); 
    probarRotacion("010", "030", "020"); 

    cout << "\nLas 4 rotaciones pasaron la prueba." << endl;

    ArbolAVL pruebaEliminar;

    pruebaEliminar.insertar(crearPaciente("020"));
    pruebaEliminar.insertar(crearPaciente("010"));
    pruebaEliminar.insertar(crearPaciente("030"));

    assert(pruebaEliminar.eliminar("020"));
    assert(pruebaEliminar.buscarPorId("020") == nullptr);
    assert(pruebaEliminar.buscarPorId("010") != nullptr);
    assert(pruebaEliminar.buscarPorId("030") != nullptr);
    assert(!pruebaEliminar.eliminar("999"));

    cout << "Eliminacion AVL correcta." << endl;

    assert(
        pruebaEliminar.buscarPorNombre("Paciente 010") != nullptr
    );

    pruebaEliminar.mostrarPreorden();
    pruebaEliminar.mostrarPostorden();
    pruebaEliminar.mostrarFactoresBalance();
    
    return 0;
}