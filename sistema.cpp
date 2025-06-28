#include "Sistema.h"
#include <fstream>     // Para ofstream, ifstream
#include <iostream>    // Para cout, cerr, endl
#include <algorithm>   // Para find_if
#include <string>      // Para string
#include <limits>      // Para numeric_limits
#include <sstream>     // Adicionado novamente explicitamente para stringstream
using namespace std;  

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
        cout << "Erro: Aeronave com código " << aeronave.getCodigo() << " já existe." << endl;
        return;
    }
    aeronaves.push_back(aeronave);
    cout << "Aeronave " << aeronave.getCodigo() << " cadastrada com sucesso." << endl;
}

void Sistema::cadastrarPiloto(const Piloto& piloto) {
    // Verifica se já existe um piloto com a mesma matrícula
    if (buscarPiloto(piloto.getMatricula())) { // Chama a versão const de buscarPiloto para verificar
        cout << "Erro: Piloto com matrícula " << piloto.getMatricula() << " já existe." << endl;
        return;
    }
    pessoas.push_back(new Piloto(piloto)); // Adiciona uma cópia dinâmica
    cout << "Piloto " << piloto.getNome() << " cadastrado com sucesso." << endl;
}

void Sistema::cadastrarPassageiro(const Passageiro& passageiro) {
    // Verifica se já existe um passageiro com o mesmo CPF
    if (buscarPassageiro(passageiro.getCPF())) { // Chama a versão const de buscarPassageiro para verificar
        cout << "Erro: Passageiro com CPF " << passageiro.getCPF() << " já existe." << endl;
        return;
    }
    pessoas.push_back(new Passageiro(passageiro)); // Adiciona uma cópia dinâmica
    cout << "Passageiro " << passageiro.getNome() << " cadastrado com sucesso." << endl;
}

void Sistema::criarVoo(const Voo& voo) {
    // Verifica se o voo já existe
    if (buscarVoo(voo.getCodigo())) { // Chama a versão const de buscarVoo para verificar
        cout << "Erro: Voo com código " << voo.getCodigo() << " já existe." << endl;
        return;
    }

    voos.push_back(voo);
    cout << "Voo " << voo.getCodigo() << " criado com sucesso." << endl;
}

// Métodos de Associação
bool Sistema::embarcarPassageiro(const string& codigoVoo, const string& cpf) {
    Voo* voo = buscarVoo(codigoVoo); // Chama a versão não-const para poder modificar o voo
    Passageiro* passageiro = buscarPassageiro(cpf); // Chama a versão não-const

    if (!voo) {
        cout << "Erro: Voo com código " << codigoVoo << " não encontrado." << endl;
        return false;
    }
    if (!passageiro) {
        cout << "Erro: Passageiro com CPF " << cpf << " não encontrado." << endl;
        return false;
    }

    if (voo->adicionarPassageiro(passageiro)) {
        cout << "Passageiro " << passageiro->getNome() << " embarcado no voo " << voo->getCodigo() << " com sucesso." << endl;
        return true;
    } else {
        cout << "Erro: Não foi possível embarcar o passageiro no voo " << voo->getCodigo() << ". Capacidade máxima atingida ou outro erro." << endl;
        return false;
    }
}

// Métodos de Listagem
void Sistema::listarVoos() const {
    cout << "\n===== LISTAGEM DE VOOS =====" << endl;
    if (voos.empty()) {
        cout << "Nenhum voo cadastrado." << endl;
        return;
    }
    for (const auto& voo : voos) { // Itera sobre voos const
        cout << "Código do Voo: " << voo.getCodigo() << endl;
        if (voo.getAeronave()) {
            cout << "  Aeronave: " << voo.getAeronave()->getCodigo() << " (" << voo.getAeronave()->getModelo() << ")" << endl;
        } else {
            cout << "  Aeronave: N/A" << endl;
        }
        if (voo.getComandante()) {
            cout << "  Comandante: " << voo.getComandante()->getNome() << " (Matrícula: " << voo.getComandante()->getMatricula() << ")" << endl;
        } else {
            cout << "  Comandante: N/A" << endl;
        }
        cout << "  Origem: " << voo.getOrigem() << endl;
        cout << "  Destino: " << voo.getDestino() << endl;
        cout << "  Número de Passageiros: " << voo.getPassageiros().size() << endl;
        cout << "  Hora de Saída Prevista: " << voo.getHoraSaida() << endl;
        cout << "  Tempo Estimado de Voo: " << voo.getTempoEstimado() << " horas (incluindo " << voo.getNumeroEscalas() << " escalas)" << endl;
        cout << "------------------------------------" << endl;
    }
}

void Sistema::listarPassageirosDoVoo(const string& codigoVoo) const {
    const Voo* voo = buscarVoo(codigoVoo); // Chama a versão const de buscarVoo
    if (!voo) {
        cout << "Erro: Voo com código " << codigoVoo << " não encontrado." << endl;
        return;
    }
    voo->listarPassageiros(); // Delega a listagem para a classe Voo
}

// Métodos de Persistência
void Sistema::salvarDados() const {
    // Salvar aeronaves
    ofstream arqAeronaves("aeronaves.csv");
    if (arqAeronaves.is_open()) {
        for (const auto& a : aeronaves) {
            arqAeronaves << a.toCSV() << endl;
        }
        arqAeronaves.close();
        cout << "Aeronaves salvas em aeronaves.csv" << endl;
    } else {
        cerr << "Erro ao abrir aeronaves.csv para escrita." << endl;
    }

    // Salvar pessoas (pilotos e passageiros)
    ofstream arqPessoas("pessoas.csv");
    if (arqPessoas.is_open()) {
        for (const auto& p : pessoas) {
            arqPessoas << p->toCSV() << endl; // Polimorfismo aqui!
        }
        arqPessoas.close();
        cout << "Pessoas salvas em pessoas.csv" << endl;
    } else {
        cerr << "Erro ao abrir pessoas.csv para escrita." << endl;
    }

    // Salvar voos
    ofstream arqVoos("voos.csv");
    if (arqVoos.is_open()) {
        for (const auto& v : voos) {
            arqVoos << v.toCSV() << endl;
        }
        arqVoos.close();
        cout << "Voos salvos em voos.csv" << endl;
    } else {
        cerr << "Erro ao abrir voos.csv para escrita." << endl;
    }
}

void Sistema::carregarDados() {
    // Carregar aeronaves
    ifstream arqAeronaves("aeronaves.csv");
    if (arqAeronaves.is_open()) {
        string linha;
        while (getline(arqAeronaves, linha)) {
            aeronaves.push_back(Aeronave::fromCSV(linha));
        }
        arqAeronaves.close();
        cout << "Aeronaves carregadas de aeronaves.csv" << endl;
    } else {
        cerr << "Aviso: Nenhuma aeronaves.csv encontrada ou erro ao abrir. Criando nova." << endl;
    }

    // Carregar pessoas (pilotos e passageiros)
    ifstream arqPessoas("pessoas.csv");
    if (arqPessoas.is_open()) {
        string linha;
        while (getline(arqPessoas, linha)) {
            stringstream ss(linha); // Corrigido: Agora stringstream está visível
            string tipo;
            getline(ss, tipo, ',');
            if (tipo == "Piloto") {
                pessoas.push_back(new Piloto(Piloto::fromCSV(linha)));
            } else if (tipo == "Passageiro") {
                pessoas.push_back(new Passageiro(Passageiro::fromCSV(linha)));
            }
        }
        arqPessoas.close();
        cout << "Pessoas carregadas de pessoas.csv" << endl;
    } else {
        cerr << "Aviso: Nenhuma pessoas.csv encontrada ou erro ao abrir. Criando nova." << endl;
    }

    // Carregar voos
    ifstream arqVoos("voos.csv");
    if (arqVoos.is_open()) {
        string linha;
        while (getline(arqVoos, linha)) {
            stringstream ss(linha); // Corrigido: Agora stringstream está visível
            string codigo, origem, destino, horaSaida, sDistancia;
            string codAeronave, matComandante, matPrimeiroOficial;
            double distancia;

            getline(ss, codigo, ',');
            getline(ss, origem, ',');
            getline(ss, destino, ',');
            getline(ss, sDistancia, ',');
            distancia = stod(sDistancia);
            getline(ss, horaSaida, ',');
            getline(ss, codAeronave, ',');
            getline(ss, matComandante, ',');
            getline(ss, matPrimeiroOficial);

            Aeronave* a = buscarAeronave(codAeronave); // Chama a versão não-const
            Piloto* c = buscarPiloto(matComandante);   // Chama a versão não-const
            Piloto* po = buscarPiloto(matPrimeiroOficial); // Chama a versão não-const

            if (a && c && po) {
                voos.push_back(Voo(codigo, origem, destino, distancia, horaSaida, a, c, po));
            } else {
                cerr << "Aviso: Não foi possível carregar voo " << codigo << " devido a dados ausentes de aeronave (" << codAeronave << ") ou pilotos (" << matComandante << ", " << matPrimeiroOficial << ")." << endl;
            }
        }
        arqVoos.close();
        cout << "Voos carregados de voos.csv" << endl;
    } else {
        cerr << "Aviso: Nenhuma voos.csv encontrada ou erro ao abrir. Criando nova." << endl;
    }
}

// Métodos de Busca Interna (não-const)
Aeronave* Sistema::buscarAeronave(const string& codigo) {
    for (auto& a : aeronaves) {
        if (a.getCodigo() == codigo) {
            return &a;
        }
    }
    return nullptr;
}

Piloto* Sistema::buscarPiloto(const string& matricula) {
    for (auto& p : pessoas) {
        Piloto* piloto = dynamic_cast<Piloto*>(p);
        if (piloto && piloto->getMatricula() == matricula) {
            return piloto;
        }
    }
    return nullptr;
}

Passageiro* Sistema::buscarPassageiro(const string& cpf) {
    for (auto& p : pessoas) {
        Passageiro* passageiro = dynamic_cast<Passageiro*>(p);
        if (passageiro && passageiro->getCPF() == cpf) {
            return passageiro;
        }
    }
    return nullptr;
}

Voo* Sistema::buscarVoo(const string& codigo) {
    for (auto& v : voos) {
        if (v.getCodigo() == codigo) {
            return &v;
        }
    }
    return nullptr;
}

// Métodos de Busca Interna (const)
const Aeronave* Sistema::buscarAeronave(const string& codigo) const {
    for (const auto& a : aeronaves) { // Itera sobre Aeronaves const
        if (a.getCodigo() == codigo) {
            return &a;
        }
    }
    return nullptr;
}

const Piloto* Sistema::buscarPiloto(const string& matricula) const {
    for (const auto& p : pessoas) { // Itera sobre Pessoa* const
        const Piloto* piloto = dynamic_cast<const Piloto*>(p); // Downcast para const Piloto*
        if (piloto && piloto->getMatricula() == matricula) {
            return piloto;
        }
    }
    return nullptr;
}

const Passageiro* Sistema::buscarPassageiro(const string& cpf) const {
    for (const auto& p : pessoas) { // Itera sobre Pessoa* const
        const Passageiro* passageiro = dynamic_cast<const Passageiro*>(p); // Downcast para const Passageiro*
        if (passageiro && passageiro->getCPF() == cpf) {
            return passageiro;
        }
    }
    return nullptr;
}

const Voo* Sistema::buscarVoo(const string& codigo) const {
    for (const auto& v : voos) { // Itera sobre Voos const
        if (v.getCodigo() == codigo) {
            return &v;
        }
    }
    return nullptr;
}