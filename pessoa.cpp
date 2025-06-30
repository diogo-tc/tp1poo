#include "Pessoa.h"
#include <sstream>     // Necessário para stringstream
#include <stdexcept>   // Necessário para stod (para horasVoo)
#include <iostream>
using namespace std;

// Implementação da classe Pessoa
Pessoa::Pessoa() : nome("") {}

Pessoa::Pessoa(const string& nome) : nome(nome) {}

string Pessoa::getNome() const {
    return nome;
}

void Pessoa::setNome(const string& nome) {
    this->nome = nome;
}

// Implementação da classe Piloto
Piloto::Piloto() : Pessoa(), matricula(""), breve(""), horasVoo(0.0) {}

Piloto::Piloto(const string& nome, const string& matricula, const string& breve, double horasVoo)
    : Pessoa(nome), matricula(matricula), breve(breve), horasVoo(horasVoo) {}

string Piloto::getMatricula() const {
    return matricula;
}

void Piloto::setMatricula(const string& matricula) {
    this->matricula = matricula;
}

string Piloto::getBreve() const {
    return breve;
}

void Piloto::setBreve(const string& breve) {
    this->breve = breve;
}

double Piloto::getHorasVoo() const {
    return horasVoo;
}

void Piloto::setHorasVoo(double horas) {
    this->horasVoo = horas;
}

string Piloto::toCSV() const {
    stringstream ss;
    ss << "Piloto," << nome << "," << matricula << "," << breve << "," << horasVoo;
    return ss.str();
}

Piloto Piloto::fromCSV(const string& linha) {
    stringstream ss(linha);
    string tipo, nome, matricula, breve, sHorasVoo;
    double horasVoo = 0.0; // Inicializa com valor padrão

    getline(ss, tipo, ','); // Ignora o tipo "Piloto"
    getline(ss, nome, ',');
    getline(ss, matricula, ',');
    getline(ss, breve, ',');
    getline(ss, sHorasVoo); // Lê as horas de voo até o final da linha

    try {
        horasVoo = stod(sHorasVoo); 
    } catch (const invalid_argument& e) {
        cerr << "Erro de conversão de horas de voo para Piloto do CSV: " << e.what() << endl;
    } catch (const out_of_range& e) {
        cerr << "Erro de faixa para horas de voo para Piloto do CSV: " << e.what() << endl;
    }

    return Piloto(nome, matricula, breve, horasVoo);
}

// Implementação da classe Passageiro
Passageiro::Passageiro() : Pessoa(), cpf(""), bilhete("") {}

Passageiro::Passageiro(const string& nome, const string& cpf, const string& bilhete)
    : Pessoa(nome), cpf(cpf), bilhete(bilhete) {}

string Passageiro::getCPF() const {
    return cpf;
}

void Passageiro::setCPF(const string& cpf) {
    this->cpf = cpf;
}

string Passageiro::getBilhete() const {
    return bilhete;
}

void Passageiro::setBilhete(const string& bilhete) {
    this->bilhete = bilhete;
}

string Passageiro::toCSV() const {
    stringstream ss;
    ss << "Passageiro," << nome << "," << cpf << "," << bilhete;
    return ss.str();
}

Passageiro Passageiro::fromCSV(const string& linha) {  
    stringstream ss(linha);
    string tipo, nome, cpf, bilhete;

    getline(ss, tipo, ','); // Ignora o tipo "Passageiro"
    getline(ss, nome, ',');
    getline(ss, cpf, ',');
    getline(ss, bilhete);

    return Passageiro(nome, cpf, bilhete);
}

