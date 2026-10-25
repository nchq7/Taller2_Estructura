
#pragma once

#include "dominio/Paciente.h"
#include <string>

class ArbolAVL {
private:
    struct Nodo {
        Paciente paciente;
        Nodo* izquierdo;
        Nodo* derecho;
        int altura;

        explicit Nodo(const Paciente& p)
            : paciente(p), izquierdo(nullptr),
              derecho(nullptr), altura(1) {}
    };

    Nodo* raiz;

    static int obtenerAlturaNodo(Nodo* nodo);
    static int factorBalance(Nodo* nodo);
    static void actualizarAltura(Nodo* nodo);

    static Nodo* rotarDerecha(Nodo* nodo);
    static Nodo* rotarIzquierda(Nodo* nodo);

    static Nodo* insertarRec(Nodo* nodo,
                            const Paciente& paciente,
                            bool& insertado);

    static void recorrerInorden(const Nodo* nodo);
    static void liberar(Nodo* nodo);
    
    static Nodo* buscarMenor(Nodo* nodo);
    static Nodo* eliminarRec(Nodo* nodo,const std::string& id,bool& eliminado);

    static const Paciente* buscarNombreRec(
    const Nodo* nodo,
    const std::string& nombre);

    static void recorrerPreorden(const Nodo* nodo);
    static void recorrerPostorden(const Nodo* nodo);
    static void mostrarBalancesRec(Nodo* nodo);
public:
    ArbolAVL();
    ~ArbolAVL();

    ArbolAVL(const ArbolAVL&) = delete;
    ArbolAVL& operator=(const ArbolAVL&) = delete;

    bool insertar(const Paciente& paciente);
    const Paciente* buscarPorId(const std::string& id) const;
    int obtenerAltura() const;
    void mostrarInorden() const;
    bool eliminar(const std::string& id);

    const Paciente* buscarPorNombre(
        const std::string& nombre) const;

    void mostrarPreorden() const;
    void mostrarPostorden() const;
    void mostrarFactoresBalance() const;
};
