#include "Aeronave.h"
#include <sstream>     // Necessário para std::stringstream
#include <stdexcept>   // Necessário para std::invalid_argument, std::out_of_range
#include <iostream>    // Necessário para std::cerr

// Construtor padrão
Aeronave::Aeronave() : codigo(""), modelo(""), capacidade(0), velocidadeMedia(0.0), autonomia(0.0) {}

// Construtor com parâmetros
Aeronave::Aeronave(const std::string& codigo, const std::string& modelo, int capacidade, double velocidadeMedia, double autonomia)
    : codigo(codigo), modelo(modelo), capacidade(capacidade), velocidadeMedia(velocidadeMedia), autonomia(autonomia) {}

// Getters
std::string Aeronave::getCodigo() const {
    return codigo;
}

std::string Aeronave::getModelo() const {
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
void Aeronave::setCodigo(const std::string& codigo) {
    this->codigo = codigo;
}

void Aeronave::setModelo(const std::string& modelo) {
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
std::string Aeronave::toCSV() const {
    std::stringstream ss;
    ss << codigo << "," << modelo << "," << capacidade << "," << velocidadeMedia << "," << autonomia;
    return ss.str();
}

// Método estático para criar uma Aeronave a partir de uma linha CSV
Aeronave Aeronave::fromCSV(const std::string& linha) {
    std::stringstream ss(linha);
    std::string codigo, modelo, sCapacidade, sVelocidadeMedia, sAutonomia;
    int capacidade;
    double velocidadeMedia, autonomia;

    std::getline(ss, codigo, ',');
    std::getline(ss, modelo, ',');
    std::getline(ss, sCapacidade, ',');
    std::getline(ss, sVelocidadeMedia, ',');
    std::getline(ss, sAutonomia);

    // Converte as strings para os tipos numéricos apropriados
    try {
        capacidade = std::stoi(sCapacidade);
        velocidadeMedia = std::stod(sVelocidadeMedia);
        autonomia = std::stod(sAutonomia);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Erro de conversão de dados ao carregar Aeronave do CSV: " << e.what() << " Linha: '" << linha << "'" << std::endl;
        capacidade = 0;
        velocidadeMedia = 0.0;
        autonomia = 0.0;
    } catch (const std::out_of_range& e) {
        std::cerr << "Erro de faixa ao carregar Aeronave do CSV: " << e.what() << " Linha: '" << linha << "'" << std::endl;
        capacidade = 0;
        velocidadeMedia = 0.0;
        autonomia = 0.0;
    }

    return Aeronave(codigo, modelo, capacidade, velocidadeMedia, autonomia);
}