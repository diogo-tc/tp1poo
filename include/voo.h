#ifndef VOO_H
#define VOO_H

#include <string>
#include <vector>
using namespace std; 

 
class Voo {
private:
    string codigo;
    string origem;
    string destino;
    double distancia; // em milhas
    string horaSaida;

    // armazenama APENAS os identificadores (IDs) como strings
    string codigoAeronave;
    string matriculaComandante;
    string matriculaPrimeiroOficial;

    int numeroEscalas;
    double tempoEstimado; // em horas

    vector<string> cpfsPassageiros; // Armazena apenas os CPFs dos passageiros

public:
    Voo();
    // Construtor recebe IDs como strings
    Voo(const string& codigo, const string& origem, const string& destino, double distancia, const string& horaSaida,
        const string& codigoAeronave, const string& matriculaComandante, const string& matriculaPrimeiroOficial);

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

    // Novos getters para os IDs armazenados
    const string& getCodigoAeronave() const;
    const string& getMatriculaComandante() const;
    const string& getMatriculaPrimeiroOficial() const;
    const vector<string>& getCpfsPassageiros() const; // Para acesso aos CPFs

    // adicionarPassageiro recebe CPF
    bool adicionarPassageiro(const string& cpfPassageiro, int capacidadeAeronave); // Precisa da capacidade para verificar lotação

    // Calcular escalas e tempo 
    void calcularEscalasETempo(double autonomiaAeronave, double velocidadeMediaAeronave);

    string toCSV() const;
    // fromCSV extrai as strings; a resolução de IDs será no Sistema::carregarDados
    static Voo fromCSV(const string& linha);
};

#endif