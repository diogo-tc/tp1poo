#include "Aeronave.h"
#include <sstream>     // Necessário para stringstream
#include <stdexcept>   // Necessário para invalid_argument, out_of_range
#include <iostream>    // Necessário para cerr
using namespace std;

// Construtor padrão
Aeronave::Aeronave() : codigo(""), modelo(""), capacidade(0), velocidadeMedia(0.0), autonomia(0.0) {}

// Construtor com parâmetros
Aeronave::Aeronave(const string& codigo, const string& modelo, int capacidade, double velocidadeMedia, double autonomia)
    : codigo(codigo), modelo(modelo), capacidade(capacidade), velocidadeMedia(velocidadeMedia), autonomia(autonomia) {}

// Getters
string Aeronave::getCodigo() const {
    return codigo;
}

string Aeronave::getModelo() const {
    return modelo;
}

int Aeronave::getCapacidade() const {
    return capacidade;
}

double Aeronave::getVelocidadeMedia() const {
    return velocidadeMedia;
}

double Aeronave::getAutonomia() const {
    return autonomia;
}

// Setters
void Aeronave::setCodigo(const string& codigo) {
    this->codigo = codigo;
}

void Aeronave::setModelo(const string& modelo) {
    this->modelo = modelo;
}

void Aeronave::setCapacidade(int capacidade) {
    this->capacidade = capacidade;
}

void Aeronave::setVelocidadeMedia(double velocidadeMedia) {
    this->velocidadeMedia = velocidadeMedia;
}

void Aeronave::setAutonomia(double autonomia) {
    this->autonomia = autonomia;
}

// Método para converter dados da aeronave para o formato CSV
string Aeronave::toCSV() const {
    stringstream ss;
    ss << codigo << "," << modelo << "," << capacidade << "," << velocidadeMedia << "," << autonomia;
    return ss.str();
}

// Método estático para criar uma Aeronave a partir de uma linha CSV
Aeronave Aeronave::fromCSV(const string& linha) {
    stringstream ss(linha);
    string codigo, modelo, sCapacidade, sVelocidadeMedia, sAutonomia;
    int capacidade;
    double velocidadeMedia, autonomia;

    getline(ss, codigo, ',');
    getline(ss, modelo, ',');
    getline(ss, sCapacidade, ',');
    getline(ss, sVelocidadeMedia, ',');
    getline(ss, sAutonomia);

    // Converte as strings para os tipos numéricos apropriados
    try {
        capacidade = stoi(sCapacidade);
        velocidadeMedia = stod(sVelocidadeMedia);
        autonomia = stod(sAutonomia);
    } catch (const invalid_argument& e) {
        cerr << "Erro de conversão de dados ao carregar Aeronave do CSV: " << e.what() << " Linha: '" << linha << "'" << endl;
        capacidade = 0;
        velocidadeMedia = 0.0;
        autonomia = 0.0;
    } catch (const out_of_range& e) {
        cerr << "Erro de faixa ao carregar Aeronave do CSV: " << e.what() << " Linha: '" << linha << "'" << endl;
        capacidade = 0;
        velocidadeMedia = 0.0;
        autonomia = 0.0;
    }

    return Aeronave(codigo, modelo, capacidade, velocidadeMedia, autonomia);
}