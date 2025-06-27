#include "Aeronave.h"
#include <sstream> // Necessário para std::stringstream
#include <stdexcept> // Necessário para std::stod
#include <iostream>  // Necessário para std::cerr

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

void Aeronave::setVelocidadeMedia(double velocidade) { 
    this->velocidadeMedia = velocidade;
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
    } catch (const std::invalid_argument& e) {
        // Lida com erros de conversão (e.g., string não numérica)
        std::cerr << "Erro de conversão de dados ao carregar Aeronave do CSV: " << e.what() << " Linha: '" << linha << "'" << std::endl;
        capacidade = 0; // Define um valor padrão em caso de erro
        velocidadeMedia = 0.0; // Define um valor padrão em caso de erro
        autonomia = 0.0; // Define um valor padrão em caso de erro
    } catch (const std::out_of_range& e) {
        // Lida com erros de estouro de faixa para números muito grandes/pequenos
        std::cerr << "Erro de faixa ao carregar Aeronave do CSV: " << e.what() << " Linha: '" << linha << "'" << std::endl;
        capacidade = 0; // Define um valor padrão em caso de erro
        velocidadeMedia = 0.0; // Define um valor padrão em caso de erro
        autonomia = 0.0; // Define um valor padrão em caso de erro
    }

    return Aeronave(codigo, modelo, capacidade, velocidadeMedia, autonomia);
}