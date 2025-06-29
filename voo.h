#ifndef VOO_H
#define VOO_H

#include <string>
#include <vector>

// Forward declarations para evitar inclusões circulares e problemas de tipo
// Voo não precisa conhecer os detalhes completos de Aeronave, Piloto, Passageiro
// ele só precisa saber que esses tipos existem (para o construtor ou se tivesse ponteiros)
// mas agora ele só guarda IDs (strings).
// No entanto, para o fromCSV poder ser um "parser" completo, é bom ter.
// Para este setup, a forward declaration é mais limpa.
// class Aeronave;
// class Piloto;
// class Passageiro;

class Voo {
private:
    std::string codigo;
    std::string origem;
    std::string destino;
    double distancia; // em milhas
    std::string horaSaida;

    // Agora armazenamos APENAS os identificadores (IDs) como strings
    std::string codigoAeronave;
    std::string matriculaComandante;
    std::string matriculaPrimeiroOficial;

    int numeroEscalas;
    double tempoEstimado; // em horas

    std::vector<std::string> cpfsPassageiros; // Armazena apenas os CPFs dos passageiros

public:
    Voo();
    // Construtor agora recebe IDs como strings
    Voo(const std::string& codigo, const std::string& origem, const std::string& destino, double distancia, const std::string& horaSaida,
        const std::string& codigoAeronave, const std::string& matriculaComandante, const std::string& matriculaPrimeiroOficial);

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

    // Novos getters para os IDs armazenados
    const std::string& getCodigoAeronave() const;
    const std::string& getMatriculaComandante() const;
    const std::string& getMatriculaPrimeiroOficial() const;
    const std::vector<std::string>& getCpfsPassageiros() const; // Para acesso aos CPFs

    // Agora adicionarPassageiro recebe CPF
    bool adicionarPassageiro(const std::string& cpfPassageiro, int capacidadeAeronave); // Precisa da capacidade para verificar lotação

    // Calcular escalas e tempo agora precisa de informações da aeronave como parâmetros
    void calcularEscalasETempo(double autonomiaAeronave, double velocidadeMediaAeronave);

    std::string toCSV() const;
    // fromCSV agora só extrai as strings; a resolução de IDs será no Sistema::carregarDados
    static Voo fromCSV(const std::string& linha);
};

#endif