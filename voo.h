#ifndef VOO_H
#define VOO_H

#include <string>
#include <vector>
#include "Aeronave.h"
#include "Pessoa.h" // Inclui Piloto e Passageiro
using namespace std; 

class Voo {
private:
    string codigo;
    string origem;
    string destino;
    double distancia; // em milhas
    string horaSaida;

    Aeronave* aeronave;
    Piloto* comandante;
    Piloto* primeiroOficial;

    int numeroEscalas;
    double tempoEstimado; // em horas

    vector<Passageiro*> passageiros;

public:
    Voo();
    Voo(const string& codigo, const string& origem, const string& destino, double distancia, const string& horaSaida,
        Aeronave* aeronave, Piloto* comandante, Piloto* primeiroOficial);

    string getCodigo() const;
    void setCodigo(const string& codigo);

    string getOrigem() const;
    void setOrigem(const string& origem);

    string getDestino() const;
    void setDestino(const string& destino);

    double getDistancia() const;
    void setDistancia(double distancia);

    string getHoraSaida() const;
    void setHoraSaida(const string& hora);

    int getNumeroEscalas() const;
    double getTempoEstimado() const;

    Aeronave* getAeronave() const;
    void setAeronave(Aeronave* aeronave);

    Piloto* getComandante() const;
    void setComandante(Piloto* comandante);

    Piloto* getPrimeiroOficial() const;
    void setPrimeiroOficial(Piloto* oficial);

    const vector<Passageiro*>& getPassageiros() const;
    bool adicionarPassageiro(Passageiro* passageiro);

    void calcularEscalasETempo();

    string toCSV() const;
    static Voo fromCSV(const string& linha); // Nota: Esta função é um placeholder para o Systema

    void listarPassageiros() const;
};

#endif