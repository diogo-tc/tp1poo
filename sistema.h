#ifndef SISTEMA_H
#define SISTEMA_H

#include <vector>
#include <string>
#include "Aeronave.h"
#include "Pessoa.h"
#include "Voo.h"

class Sistema {
private:
    std::vector<Aeronave> aeronaves;
    std::vector<Pessoa*> pessoas; // Pode conter Piloto* e Passageiro*
    std::vector<Voo> voos;

public:
    Sistema();
    ~Sistema(); // Destrutor para liberar memória de Pessoa*

    // Cadastro
    void cadastrarAeronave(const Aeronave& aeronave);
    void cadastrarPiloto(const Piloto& piloto);
    void cadastrarPassageiro(const Passageiro& passageiro);
    void criarVoo(const Voo& voo); // Voo já virá com IDs, não ponteiros

    // Associações
    bool embarcarPassageiro(const std::string& codigoVoo, const std::string& cpf);

    // Listagens
    void listarVoos() const;
    void listarPassageirosDoVoo(const std::string& codigoVoo) const;

    // Persistência
    void salvarDados() const;
    void carregarDados();

    // Buscas internas (retornam ponteiros para objetos gerenciados pelo Sistema)
    // Versão não-const (para modificação)
    Aeronave* buscarAeronave(const std::string& codigo);
    Piloto* buscarPiloto(const std::string& matricula);
    Passageiro* buscarPassageiro(const std::string& cpf);
    Voo* buscarVoo(const std::string& codigo); // Retorna Voo* para poder adicionar passageiros

    // Versão const (para acesso somente leitura)
    const Aeronave* buscarAeronave(const std::string& codigo) const;
    const Piloto* buscarPiloto(const std::string& matricula) const;
    const Passageiro* buscarPassageiro(const std::string& cpf) const;
    const Voo* buscarVoo(const std::string& codigo) const;
};

#endif