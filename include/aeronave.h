#ifndef AERONAVE_H
#define AERONAVE_H

#include <string>
using namespace std;    

class Aeronave {
private:
    string codigo;    
    string modelo;
    int capacidade;
    double velocidadeMedia;
    double autonomia; // em milhas

public:
    Aeronave();
    Aeronave(const string& codigo, const string& modelo, int capacidade, double velocidadeMedia, double autonomia);

    // Getters e Setters
    string getCodigo() const;
    void setCodigo(const string& codigo);

    string getModelo() const;
    void setModelo(const string& modelo);

    int getCapacidade() const;
    void setCapacidade(int capacidade);

    double getVelocidadeMedia() const;
    void setVelocidadeMedia(double velocidade);

    double getAutonomia() const;
    void setAutonomia(double autonomia);

    // Serialização para CSV
    string toCSV() const;
    static Aeronave fromCSV(const string& linha);
};

#endif