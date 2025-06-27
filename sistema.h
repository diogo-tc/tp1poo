#ifndef SISTEMA_H
#define SISTEMA_H

#include <vector>
#include <string>
#include "Aeronave.h"
#include "Pessoa.h"
#include "Voo.h"
using namespace std;

class Sistema {
private:
    vector<Aeronave> aeronaves;
    vector<Pessoa*> pessoas;
    vector<Voo> voos;

public:
    Sistema();
    ~Sistema();

    void cadastrarAeronave(const Aeronave& aeronave);
    void cadastrarPiloto(const Piloto& piloto);
    void cadastrarPassageiro(const Passageiro& passageiro);
    void criarVoo(const Voo& voo);

    bool embarcarPassageiro(const string& codigoVoo, const string& cpf);

    void listarVoos() const;
    void listarPassageirosDoVoo(const string& codigoVoo) const;

    void salvarDados() const;
    void carregarDados();

    // Versões não-const (para modificação)
    Aeronave* buscarAeronave(const string& codigo);
    Piloto* buscarPiloto(const string& matricula);
    Passageiro* buscarPassageiro(const string& cpf);
    Voo* buscarVoo(const string& codigo);

    // Versões const (para acesso somente leitura)
    const Aeronave* buscarAeronave(const string& codigo) const;
    const Piloto* buscarPiloto(const string& matricula) const;
    const Passageiro* buscarPassageiro(const string& cpf) const;
    const Voo* buscarVoo(const string& codigo) const;
};

#endif