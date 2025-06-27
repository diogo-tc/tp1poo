#ifndef PESSOA_H
#define PESSOA_H

#include <string>
// using namespace std; // Removido

class Pessoa {
protected:
    std::string nome;

public:
    Pessoa();
    Pessoa(const std::string& nome);

    virtual ~Pessoa() = default;

    std::string getNome() const;
    void setNome(const std::string& nome);

    virtual std::string toCSV() const = 0;
};

class Piloto : public Pessoa {
private:
    std::string matricula;
    std::string breve;
    double horasVoo;

public:
    Piloto();
    Piloto(const std::string& nome, const std::string& matricula, const std::string& breve, double horasVoo);

    std::string getMatricula() const;
    void setMatricula(const std::string& matricula);

    std::string getBreve() const;
    void setBreve(const std::string& breve);

    double getHorasVoo() const;
    void setHorasVoo(double horas);

    std::string toCSV() const override;
    static Piloto fromCSV(const std::string& linha);
};

class Passageiro : public Pessoa {
private:
    std::string cpf;
    std::string bilhete;

public:
    Passageiro();
    Passageiro(const std::string& nome, const std::string& cpf, const std::string& bilhete);

    std::string getCPF() const;
    void setCPF(const std::string& cpf);

    std::string getBilhete() const;
    void setBilhete(const std::string& bilhete);

    std::string toCSV() const override;
    static Passageiro fromCSV(const std::string& linha);
};

#endif