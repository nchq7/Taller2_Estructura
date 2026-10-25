#include "logica/LectorPacientes.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <stdexcept>
#include <cmath>

using namespace std;

//elimina espacios
static string limpiar(const string& texto) {
    size_t inicio = texto.find_first_not_of(" \t\r\n");

    if (inicio == string::npos) {
        return "";
    }

    size_t fin = texto.find_last_not_of(" \t\r\n");
    return texto.substr(inicio, fin - inicio + 1);
}

static int convertirEntero(const string& texto) {
    size_t posicion = 0;
    int numero = stoi(texto, &posicion);

    if (posicion != texto.size()) {
        throw invalid_argument("Entero invalido");
    }

    return numero;
}

static double convertirDecimal(const string& texto) {
    size_t posicion = 0;
    double numero = stod(texto, &posicion);

    if (posicion != texto.size() || !isfinite(numero)) {
        throw invalid_argument("Decimal invalido");
    }

    return numero;
}

static bool convertirBool(const string& texto) {
    int valor = convertirEntero(texto);

    if (valor != 0 && valor != 1) {
        throw invalid_argument("Valor booleano invalido");
    }

    return valor == 1;
}

int LectorPacientes::cargarArchivo(const string& ruta,
                                  ColaPacientes& cola) {
    ifstream archivo(ruta);

    if (!archivo.is_open()) {
        cerr << "Error: no se pudo abrir " << ruta << endl;
        return -1;
    }

    string linea;
    int numeroLinea = 0;
    int cargados = 0;

    unordered_set<string> idsRegistrados;
    // aca el tipico lector de archivo de toda la vida
    while (getline(archivo, linea)) {
        numeroLinea++;

        if (limpiar(linea).empty()) {
            continue;
        }

        try {
            stringstream ss(linea);
            vector<string> campos;
            string campo;

            while (getline(ss, campo, ';')) {
                campos.push_back(limpiar(campo));
            }

            if (campos.size() != 11) {
                throw invalid_argument(
                    "Cantidad incorrecta de atributos"
                );
            }

            string id = campos[0];
            string nombre = campos[1];

            if (id.empty() || nombre.empty()) {
                throw invalid_argument("ID o nombre vacio");
            }

            if (idsRegistrados.count(id) > 0) {
                throw invalid_argument("ID duplicado");
            }

            int edad = convertirEntero(campos[2]);
            double temperatura = convertirDecimal(campos[3]);
            int presion = convertirEntero(campos[4]);
            int dolor = convertirEntero(campos[5]);
            string tipoDolor = campos[6];

            bool trauma = convertirBool(campos[7]);
            bool sintomas = convertirBool(campos[8]);
            bool cirugia = convertirBool(campos[9]);

            int dias = convertirEntero(campos[10]);

            if (edad < 0 || edad > 120 ||
                temperatura < 30 || temperatura > 45 ||
                presion < 50 || presion > 250 ||
                dolor < 0 || dolor > 10 ||
                dias < 0 || dias > 365) {
                throw invalid_argument("Valor fuera de rango");
            }

            if (tipoDolor != "pecho" &&
                tipoDolor != "cabeza" &&
                tipoDolor != "abdomen" &&
                tipoDolor != "extremidad" &&
                tipoDolor != "otro") {
                throw invalid_argument("Tipo de dolor invalido");
            }

            Paciente paciente(
                id, nombre, edad, temperatura, presion,
                dolor, tipoDolor, trauma, sintomas,
                cirugia, dias
            );

            cola.encolar(paciente);

            idsRegistrados.insert(id);
            cargados++;

        } catch (const exception& error) {
            cerr << "Linea " << numeroLinea
                 << " ignorada: " << error.what() << endl;
        }
    }

    return cargados;
}