#ifndef PESSOA_H
#define PESSOA_H

#include <string>
using namespace std;


class Pessoa {
protected:
    string nome;

public: 
    Pessoa();
    Pessoa(const string& nome);

    virtual ~Pessoa() = default;

    string getNome() const;
    void setNome(const string& nome);

    virtual string toCSV() const = 0;
};

class Piloto : public Pessoa {
private:
    string matricula;
    string breve;
    double horasVoo;

public:
    Piloto();
    Piloto(const string& nome, const string& matricula, const string& breve, double horasVoo);

    string getMatricula() const;
    void setMatricula(const string& matricula);

    string getBreve() const;
    void setBreve(const string& breve);

    double getHorasVoo() const;
    void setHorasVoo(double horas);

    string toCSV() const override;
    static Piloto fromCSV(const string& linha);
};

class Passageiro : public Pessoa {
private:
    string cpf;
    string bilhete;

public:
    Passageiro();
    Passageiro(const string& nome, const string& cpf, const string& bilhete);

    string getCPF() const;
    void setCPF(const string& cpf);

    string getBilhete() const;
    void setBilhete(const string& bilhete);

    string toCSV() const override;
    static Passageiro fromCSV(const string& linha);
};
  
#endif

