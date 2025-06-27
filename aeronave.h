#ifndef AERONAVE_H
#define AERONAVE_H

#include <string>

// Recomenda-se não usar 'using namespace std;' em headers.
// Se realmente quiser, adicione-o apenas nos arquivos .cpp
// ou use 'std::string', 'std::vector' etc. explicitamente.
// using namespace std; // Removido para evitar poluição de namespace

class Aeronave {
private:
    std::string codigo;
    std::string modelo;
    int capacidade;
    double velocidadeMedia;
    double autonomia; // em milhas

public:
    Aeronave();
    Aeronave(const std::string& codigo, const std::string& modelo, int capacidade, double velocidadeMedia, double autonomia);

    // Getters e Setters
    std::string getCodigo() const;
    void setCodigo(const std::string& codigo);

    std::string getModelo() const;
    void setModelo(const std::string& modelo);

    int getCapacidade() const;
    void setCapacidade(int capacidade);

    double getVelocidadeMedia() const;
    void setVelocidadeMedia(double velocidade);

    double getAutonomia() const;
    void setAutonomia(double autonomia);

    // Serialização para CSV
    std::string toCSV() const;
    static Aeronave fromCSV(const std::string& linha);
};

#endif