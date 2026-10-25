#include "dominio/Paciente.h"

Paciente::Paciente(const std::string& id, const std::string& nombre,
                   int edad, double temperatura, int presionArterial,
                   int dolor, const std::string& tipoDolor, bool trauma,
                   bool sintomasNeurologicos, bool requiereCirugia,
                   int diasHospitalizacion) {
    this->id = id;
    this->nombre = nombre;
    this->edad = edad;
    this->temperatura = temperatura;
    this->presionArterial = presionArterial;
    this->dolor = dolor;
    this->tipoDolor = tipoDolor;
    this->trauma = trauma;
    this->sintomasNeurologicos = sintomasNeurologicos;
    this->requiereCirugia = requiereCirugia;
    this->diasHospitalizacion = diasHospitalizacion;
}

std::string Paciente::getId() const { return id; }
std::string Paciente::getNombre() const { return nombre; }
int Paciente::getEdad() const { return edad; }
double Paciente::getTemperatura() const { return temperatura; }
int Paciente::getPresionArterial() const { return presionArterial; }
int Paciente::getDolor() const { return dolor; }
std::string Paciente::getTipoDolor() const { return tipoDolor; }
bool Paciente::getTrauma() const { return trauma; }
bool Paciente::getSintomasNeurologicos() const { return sintomasNeurologicos; }
bool Paciente::getRequiereCirugia() const { return requiereCirugia; }
int Paciente::getDiasHospitalizacion() const { return diasHospitalizacion; }
  