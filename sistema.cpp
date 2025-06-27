#include "Sistema.h"
#include <fstream>     // Para std::ofstream, std::ifstream
#include <iostream>    // Para std::cout, std::cerr, std::endl
#include <algorithm>   // Para std::find_if
#include <string>      // Para std::string
#include <limits>      // Para std::numeric_limits
#include <sstream>     // Adicionado novamente explicitamente para stringstream

// Construtor
Sistema::Sistema() {
    // Inicialização, se necessário
}

// Destrutor para liberar a memória alocada para Pessoa*
Sistema::~Sistema() {
    for (Pessoa* p : pessoas) {
        delete p;
    }
    pessoas.clear();
}

// Métodos de Cadastro
void Sistema::cadastrarAeronave(const Aeronave& aeronave) {
    // Verifica se já existe uma aeronave com o mesmo código
    if (buscarAeronave(aeronave.getCodigo())) { // Chama a versão const de buscarAeronave para verificar
        std::cout << "Erro: Aeronave com código " << aeronave.getCodigo() << " já existe." << std::endl;
        return;
    }
    aeronaves.push_back(aeronave);
    std::cout << "Aeronave " << aeronave.getCodigo() << " cadastrada com sucesso." << std::endl;
}

void Sistema::cadastrarPiloto(const Piloto& piloto) {
    // Verifica se já existe um piloto com a mesma matrícula
    if (buscarPiloto(piloto.getMatricula())) { // Chama a versão const de buscarPiloto para verificar
        std::cout << "Erro: Piloto com matrícula " << piloto.getMatricula() << " já existe." << std::endl;
        return;
    }
    pessoas.push_back(new Piloto(piloto)); // Adiciona uma cópia dinâmica
    std::cout << "Piloto " << piloto.getNome() << " cadastrado com sucesso." << std::endl;
}

void Sistema::cadastrarPassageiro(const Passageiro& passageiro) {
    // Verifica se já existe um passageiro com o mesmo CPF
    if (buscarPassageiro(passageiro.getCPF())) { // Chama a versão const de buscarPassageiro para verificar
        std::cout << "Erro: Passageiro com CPF " << passageiro.getCPF() << " já existe." << std::endl;
        return;
    }
    pessoas.push_back(new Passageiro(passageiro)); // Adiciona uma cópia dinâmica
    std::cout << "Passageiro " << passageiro.getNome() << " cadastrado com sucesso." << std::endl;
}

void Sistema::criarVoo(const Voo& voo) {
    // Verifica se o voo já existe
    if (buscarVoo(voo.getCodigo())) { // Chama a versão const de buscarVoo para verificar
        std::cout << "Erro: Voo com código " << voo.getCodigo() << " já existe." << std::endl;
        return;
    }

    voos.push_back(voo);
    std::cout << "Voo " << voo.getCodigo() << " criado com sucesso." << std::endl;
}

// Métodos de Associação
bool Sistema::embarcarPassageiro(const std::string& codigoVoo, const std::string& cpf) {
    Voo* voo = buscarVoo(codigoVoo); // Chama a versão não-const para poder modificar o voo
    Passageiro* passageiro = buscarPassageiro(cpf); // Chama a versão não-const

    if (!voo) {
        std::cout << "Erro: Voo com código " << codigoVoo << " não encontrado." << std::endl;
        return false;
    }
    if (!passageiro) {
        std::cout << "Erro: Passageiro com CPF " << cpf << " não encontrado." << std::endl;
        return false;
    }

    if (voo->adicionarPassageiro(passageiro)) {
        std::cout << "Passageiro " << passageiro->getNome() << " embarcado no voo " << voo->getCodigo() << " com sucesso." << std::endl;
        return true;
    } else {
        std::cout << "Erro: Não foi possível embarcar o passageiro no voo " << voo->getCodigo() << ". Capacidade máxima atingida ou outro erro." << std::endl;
        return false;
    }
}

// Métodos de Listagem
void Sistema::listarVoos() const {
    std::cout << "\n===== LISTAGEM DE VOOS =====" << std::endl;
    if (voos.empty()) {
        std::cout << "Nenhum voo cadastrado." << std::endl;
        return;
    }
    for (const auto& voo : voos) { // Itera sobre voos const
        std::cout << "Código do Voo: " << voo.getCodigo() << std::endl;
        if (voo.getAeronave()) {
            std::cout << "  Aeronave: " << voo.getAeronave()->getCodigo() << " (" << voo.getAeronave()->getModelo() << ")" << std::endl;
        } else {
            std::cout << "  Aeronave: N/A" << std::endl;
        }
        if (voo.getComandante()) {
            std::cout << "  Comandante: " << voo.getComandante()->getNome() << " (Matrícula: " << voo.getComandante()->getMatricula() << ")" << std::endl;
        } else {
            std::cout << "  Comandante: N/A" << std::endl;
        }
        std::cout << "  Origem: " << voo.getOrigem() << std::endl;
        std::cout << "  Destino: " << voo.getDestino() << std::endl;
        std::cout << "  Número de Passageiros: " << voo.getPassageiros().size() << std::endl;
        std::cout << "  Hora de Saída Prevista: " << voo.getHoraSaida() << std::endl;
        std::cout << "  Tempo Estimado de Voo: " << voo.getTempoEstimado() << " horas (incluindo " << voo.getNumeroEscalas() << " escalas)" << std::endl;
        std::cout << "------------------------------------" << std::endl;
    }
}

void Sistema::listarPassageirosDoVoo(const std::string& codigoVoo) const {
    const Voo* voo = buscarVoo(codigoVoo); // Chama a versão const de buscarVoo
    if (!voo) {
        std::cout << "Erro: Voo com código " << codigoVoo << " não encontrado." << std::endl;
        return;
    }
    voo->listarPassageiros(); // Delega a listagem para a classe Voo
}

// Métodos de Persistência
void Sistema::salvarDados() const {
    // Salvar aeronaves
    std::ofstream arqAeronaves("aeronaves.csv");
    if (arqAeronaves.is_open()) {
        for (const auto& a : aeronaves) {
            arqAeronaves << a.toCSV() << std::endl;
        }
        arqAeronaves.close();
        std::cout << "Aeronaves salvas em aeronaves.csv" << std::endl;
    } else {
        std::cerr << "Erro ao abrir aeronaves.csv para escrita." << std::endl;
    }

    // Salvar pessoas (pilotos e passageiros)
    std::ofstream arqPessoas("pessoas.csv");
    if (arqPessoas.is_open()) {
        for (const auto& p : pessoas) {
            arqPessoas << p->toCSV() << std::endl; // Polimorfismo aqui!
        }
        arqPessoas.close();
        std::cout << "Pessoas salvas em pessoas.csv" << std::endl;
    } else {
        std::cerr << "Erro ao abrir pessoas.csv para escrita." << std::endl;
    }

    // Salvar voos
    std::ofstream arqVoos("voos.csv");
    if (arqVoos.is_open()) {
        for (const auto& v : voos) {
            arqVoos << v.toCSV() << std::endl;
        }
        arqVoos.close();
        std::cout << "Voos salvos em voos.csv" << std::endl;
    } else {
        std::cerr << "Erro ao abrir voos.csv para escrita." << std::endl;
    }
}

void Sistema::carregarDados() {
    // Carregar aeronaves
    std::ifstream arqAeronaves("aeronaves.csv");
    if (arqAeronaves.is_open()) {
        std::string linha;
        while (std::getline(arqAeronaves, linha)) {
            aeronaves.push_back(Aeronave::fromCSV(linha));
        }
        arqAeronaves.close();
        std::cout << "Aeronaves carregadas de aeronaves.csv" << std::endl;
    } else {
        std::cerr << "Aviso: Nenhuma aeronaves.csv encontrada ou erro ao abrir. Criando nova." << std::endl;
    }

    // Carregar pessoas (pilotos e passageiros)
    std::ifstream arqPessoas("pessoas.csv");
    if (arqPessoas.is_open()) {
        std::string linha;
        while (std::getline(arqPessoas, linha)) {
            std::stringstream ss(linha); // Corrigido: Agora std::stringstream está visível
            std::string tipo;
            std::getline(ss, tipo, ',');
            if (tipo == "Piloto") {
                pessoas.push_back(new Piloto(Piloto::fromCSV(linha)));
            } else if (tipo == "Passageiro") {
                pessoas.push_back(new Passageiro(Passageiro::fromCSV(linha)));
            }
        }
        arqPessoas.close();
        std::cout << "Pessoas carregadas de pessoas.csv" << std::endl;
    } else {
        std::cerr << "Aviso: Nenhuma pessoas.csv encontrada ou erro ao abrir. Criando nova." << std::endl;
    }

    // Carregar voos
    std::ifstream arqVoos("voos.csv");
    if (arqVoos.is_open()) {
        std::string linha;
        while (std::getline(arqVoos, linha)) {
            std::stringstream ss(linha); // Corrigido: Agora std::stringstream está visível
            std::string codigo, origem, destino, horaSaida, sDistancia;
            std::string codAeronave, matComandante, matPrimeiroOficial;
            double distancia;

            std::getline(ss, codigo, ',');
            std::getline(ss, origem, ',');
            std::getline(ss, destino, ',');
            std::getline(ss, sDistancia, ',');
            distancia = std::stod(sDistancia);
            std::getline(ss, horaSaida, ',');
            std::getline(ss, codAeronave, ',');
            std::getline(ss, matComandante, ',');
            std::getline(ss, matPrimeiroOficial);

            Aeronave* a = buscarAeronave(codAeronave); // Chama a versão não-const
            Piloto* c = buscarPiloto(matComandante);   // Chama a versão não-const
            Piloto* po = buscarPiloto(matPrimeiroOficial); // Chama a versão não-const

            if (a && c && po) {
                voos.push_back(Voo(codigo, origem, destino, distancia, horaSaida, a, c, po));
            } else {
                std::cerr << "Aviso: Não foi possível carregar voo " << codigo << " devido a dados ausentes de aeronave (" << codAeronave << ") ou pilotos (" << matComandante << ", " << matPrimeiroOficial << ")." << std::endl;
            }
        }
        arqVoos.close();
        std::cout << "Voos carregados de voos.csv" << std::endl;
    } else {
        std::cerr << "Aviso: Nenhuma voos.csv encontrada ou erro ao abrir. Criando nova." << std::endl;
    }
}

// Métodos de Busca Interna (não-const)
Aeronave* Sistema::buscarAeronave(const std::string& codigo) {
    for (auto& a : aeronaves) {
        if (a.getCodigo() == codigo) {
            return &a;
        }
    }
    return nullptr;
}

Piloto* Sistema::buscarPiloto(const std::string& matricula) {
    for (auto& p : pessoas) {
        Piloto* piloto = dynamic_cast<Piloto*>(p);
        if (piloto && piloto->getMatricula() == matricula) {
            return piloto;
        }
    }
    return nullptr;
}

Passageiro* Sistema::buscarPassageiro(const std::string& cpf) {
    for (auto& p : pessoas) {
        Passageiro* passageiro = dynamic_cast<Passageiro*>(p);
        if (passageiro && passageiro->getCPF() == cpf) {
            return passageiro;
        }
    }
    return nullptr;
}

Voo* Sistema::buscarVoo(const std::string& codigo) {
    for (auto& v : voos) {
        if (v.getCodigo() == codigo) {
            return &v;
        }
    }
    return nullptr;
}

// Métodos de Busca Interna (const)
const Aeronave* Sistema::buscarAeronave(const std::string& codigo) const {
    for (const auto& a : aeronaves) { // Itera sobre Aeronaves const
        if (a.getCodigo() == codigo) {
            return &a;
        }
    }
    return nullptr;
}

const Piloto* Sistema::buscarPiloto(const std::string& matricula) const {
    for (const auto& p : pessoas) { // Itera sobre Pessoa* const
        const Piloto* piloto = dynamic_cast<const Piloto*>(p); // Downcast para const Piloto*
        if (piloto && piloto->getMatricula() == matricula) {
            return piloto;
        }
    }
    return nullptr;
}

const Passageiro* Sistema::buscarPassageiro(const std::string& cpf) const {
    for (const auto& p : pessoas) { // Itera sobre Pessoa* const
        const Passageiro* passageiro = dynamic_cast<const Passageiro*>(p); // Downcast para const Passageiro*
        if (passageiro && passageiro->getCPF() == cpf) {
            return passageiro;
        }
    }
    return nullptr;
}

const Voo* Sistema::buscarVoo(const std::string& codigo) const {
    for (const auto& v : voos) { // Itera sobre Voos const
        if (v.getCodigo() == codigo) {
            return &v;
        }
    }
    return nullptr;
}