#pragma once

#include <string>

class Paciente {
private:
    std::string id;
    std::string nombre;
    int edad;
    double temperatura;
    int presionArterial;
    int dolor;
    std::string tipoDolor;
    bool trauma;
    bool sintomasNeurologicos;
    bool requiereCirugia;
    int diasHospitalizacion;

public:
    Paciente(const std::string& id, const std::string& nombre,
             int edad, double temperatura, int presionArterial,
             int dolor, const std::string& tipoDolor, bool trauma,
             bool sintomasNeurologicos, bool requiereCirugia,
             int diasHospitalizacion);

    std::string getId() const;
    std::string getNombre() const;
    int getEdad() const;
    double getTemperatura() const;
    int getPresionArterial() const;
    int getDolor() const;
    std::string getTipoDolor() const;
    bool getTrauma() const;
    bool getSintomasNeurologicos() const;
    bool getRequiereCirugia() const;
    int getDiasHospitalizacion() const;
};
