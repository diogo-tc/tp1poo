#ifndef VOO_H
#define VOO_H

#include <string>
#include <vector>
#include "Aeronave.h"
#include "Pessoa.h" // Inclui Piloto e Passageiro
// using namespace std; // Removido

class Voo {
private:
    std::string codigo;
    std::string origem;
    std::string destino;
    double distancia; // em milhas
    std::string horaSaida;

    Aeronave* aeronave;
    Piloto* comandante;
    Piloto* primeiroOficial;

    int numeroEscalas;
    double tempoEstimado; // em horas

    std::vector<Passageiro*> passageiros;

public:
    Voo();
    Voo(const std::string& codigo, const std::string& origem, const std::string& destino, double distancia, const std::string& horaSaida,
        Aeronave* aeronave, Piloto* comandante, Piloto* primeiroOficial);

    std::string getCodigo() const;
    void setCodigo(const std::string& codigo);

    std::string getOrigem() const;
    void setOrigem(const std::string& origem);

    std::string getDestino() const;
    void setDestino(const std::string& destino);

    double getDistancia() const;
    void setDistancia(double distancia);

    std::string getHoraSaida() const;
    void setHoraSaida(const std::string& hora);

    int getNumeroEscalas() const;
    double getTempoEstimado() const;

    Aeronave* getAeronave() const;
    void setAeronave(Aeronave* aeronave);

    Piloto* getComandante() const;
    void setComandante(Piloto* comandante);

    Piloto* getPrimeiroOficial() const;
    void setPrimeiroOficial(Piloto* oficial);

    const std::vector<Passageiro*>& getPassageiros() const;
    bool adicionarPassageiro(Passageiro* passageiro);

    void calcularEscalasETempo();

    std::string toCSV() const;
    static Voo fromCSV(const std::string& linha); // Nota: Esta função é um placeholder para o Systema

    void listarPassageiros() const;
};

#endif