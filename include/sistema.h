#ifndef SISTEMA_H
#define SISTEMA_H

#include <vector>
#include <string>
#include "aeronave.h"
#include "pessoa.h" 
#include "voo.h"
using namespace std; 

class Sistema {
private:
    vector<Aeronave> aeronaves;
    vector<Pessoa*> pessoas; // Pode conter Piloto* e Passageiro*
    vector<Voo> voos;

public:
    Sistema() {}
    ~Sistema(); // Destrutor para liberar memória de Pessoa*

    // Cadastro
    void cadastrarAeronave(const Aeronave& aeronave);
    void cadastrarPiloto(const Piloto& piloto);
    void cadastrarPassageiro(const Passageiro& passageiro);
    void criarVoo(const Voo& voo); 

    // Associações
    bool embarcarPassageiro(const string& codigoVoo, const string& cpf);

    // Listagens
    void listarVoos() const;
    void listarPassageirosDoVoo(const string& codigoVoo) const;

    // Persistência
    void salvarDados() const;
    void carregarDados();

    // Buscas internas (retornam ponteiros para objetos gerenciados pelo Sistema)
    // Versão não-const (para modificação)
    Aeronave* buscarAeronave(const string& codigo);
    Piloto* buscarPiloto(const string& matricula);
    Passageiro* buscarPassageiro(const string& cpf);
    Voo* buscarVoo(const string& codigo); // Retorna Voo* para poder adicionar passageiros

    // Versão const (para acesso somente leitura)
    const Aeronave* buscarAeronave(const string& codigo) const;
    const Piloto* buscarPiloto(const string& matricula) const;
    const Passageiro* buscarPassageiro(const string& cpf) const;
    const Voo* buscarVoo(const string& codigo) const;
    // Relatórios estatísticos
    string relatorioTotalVoos() const;
    string relatorioMediaPassageirosPorVoo() const;
    string relatorioAeronavesMaisUtilizadas() const;
    string relatorioPassageirosMaisDeUmVoo() const;
    string relatorioVoos90PorcentoCapacidade() const;
    string relatorioDistanciaPorAeronave() const;
};

#endif