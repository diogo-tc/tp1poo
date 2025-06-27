#include "Sistema.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <limits>
#include <sstream> // Adicionado novamente explicitamente para stringstream

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
    if (buscarAeronave(aeronave.getCodigo())) { // Chama a versão const de buscarAeronave para verificar
        cout << "Erro: Aeronave com código " << aeronave.getCodigo() << " já existe." << endl;
        return;
    }
    aeronaves.push_back(aeronave);
    cout << "Aeronave " << aeronave.getCodigo() << " cadastrada com sucesso." << endl;
}

void Sistema::cadastrarPiloto(const Piloto& piloto) {
    if (buscarPiloto(piloto.getMatricula())) { // Chama a versão const de buscarPiloto para verificar
        cout << "Erro: Piloto com matrícula " << piloto.getMatricula() << " já existe." << endl;
        return;
    }
    pessoas.push_back(new Piloto(piloto));
    cout << "Piloto " << piloto.getNome() << " cadastrado com sucesso." << endl;
}

void Sistema::cadastrarPassageiro(const Passageiro& passageiro) {
    if (buscarPassageiro(passageiro.getCPF())) { // Chama a versão const de buscarPassageiro para verificar
        cout << "Erro: Passageiro com CPF " << passageiro.getCPF() << " já existe." << endl;
        return;
    }
    pessoas.push_back(new Passageiro(passageiro));
    cout << "Passageiro " << passageiro.getNome() << " cadastrado com sucesso." << endl;
}

void Sistema::criarVoo(const Voo& voo) {
    if (buscarVoo(voo.getCodigo())) { // Chama a versão const de buscarVoo para verificar
        cout << "Erro: Voo com código " << voo.getCodigo() << " já existe." << endl;
        return;
    }
    voos.push_back(voo);
    cout << "Voo " << voo.getCodigo() << " criado com sucesso." << endl;
}

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
        cout << "Erro: Não foi possível embarcar o passageiro no voo " << voo->getCodigo() << ". Capacidade máxima atingida ou passageiro já embarcado." << endl;
        return false;
    }
}

void Sistema::listarVoos() const {
    cout << "\n===== LISTAGEM DE VOOS =====" << endl;
    if (voos.empty()) {
        cout << "Nenhum voo cadastrado." << endl;
        return;
    }
    for (const auto& voo : voos) {
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
    voo->listarPassageiros();
}

void Sistema::salvarDados() const {
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

    ofstream arqPessoas("pessoas.csv");
    if (arqPessoas.is_open()) {
        for (const auto& p : pessoas) {
            arqPessoas << p->toCSV() << endl;
        }
        arqPessoas.close();
        cout << "Pessoas salvas em pessoas.csv" << endl;
    } else {
        cerr << "Erro ao abrir pessoas.csv para escrita." << endl;
    }

    // Salvando voos com seus passageiros associados na mesma linha
    ofstream arqVoos("voos.csv");
    if (arqVoos.is_open()) {
        for (const auto& v : voos) {
            arqVoos << v.toCSV() << endl; // O Voo::toCSV() agora inclui os CPFs
        }
        arqVoos.close();
        cout << "Voos (com passageiros) salvos em voos.csv" << endl;
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
        cerr << "Aviso: Nenhuma aeronaves.csv encontrada ou erro ao abrir. Iniciando sem dados de aeronaves." << endl;
    }

    // Carregar pessoas (pilotos e passageiros)
    ifstream arqPessoas("pessoas.csv");
    if (arqPessoas.is_open()) {
        string linha;
        while (getline(arqPessoas, linha)) {
            stringstream ss(linha);
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
        cerr << "Aviso: Nenhuma pessoas.csv encontrada ou erro ao abrir. Iniciando sem dados de pessoas." << endl;
    }

    // Carregar voos e suas associações de passageiros
    ifstream arqVoos("voos.csv");
    if (arqVoos.is_open()) {
        string linha;
        while (getline(arqVoos, linha)) {
            stringstream ss(linha);
            string codigo, origem, destino, horaSaida, sDistancia;
            string codAeronave, matComandante, matPrimeiroOficial, cpfsPassageirosStr;
            double distancia;

            // Extrai os campos básicos do voo
            getline(ss, codigo, ',');
            getline(ss, origem, ',');
            getline(ss, destino, ',');
            getline(ss, sDistancia, ',');
            distancia = stod(sDistancia);
            getline(ss, horaSaida, ',');
            getline(ss, codAeronave, ',');
            getline(ss, matComandante, ',');
            getline(ss, matPrimeiroOficial, ',');
            getline(ss, cpfsPassageirosStr); // Captura a string de CPFs

            Aeronave* a = buscarAeronave(codAeronave); // Usa a versão não-const para pegar ponteiros modificáveis
            Piloto* c = buscarPiloto(matComandante);
            Piloto* po = buscarPiloto(matPrimeiroOficial);

            if (a && c && po) {
                Voo novoVoo(codigo, origem, destino, distancia, horaSaida, a, c, po);

                // Reassociar passageiros do voo
                if (!cpfsPassageirosStr.empty()) {
                    stringstream ssCpfs(cpfsPassageirosStr);
                    string cpfIndividual;
                    while (getline(ssCpfs, cpfIndividual, ';')) { // Delimita por ';'
                        Passageiro* p = buscarPassageiro(cpfIndividual);
                        if (p) {
                            novoVoo.adicionarPassageiro(p); // Adiciona o passageiro ao voo
                        } else {
                            cerr << "Aviso: Passageiro com CPF " << cpfIndividual << " para o voo " << codigo << " não encontrado durante o carregamento. (Pode ter sido removido do pessoas.csv)" << endl;
                        }
                    }
                }
                voos.push_back(novoVoo);
            } else {
                cerr << "Aviso: Não foi possível carregar voo " << codigo << " devido a dados ausentes de aeronave (" << codAeronave << ") ou pilotos (" << matComandante << ", " << matPrimeiroOficial << "). Este voo será ignorado." << endl;
            }
        }
        arqVoos.close();
        cout << "Voos (com passageiros) carregados de voos.csv" << endl;
    } else {
        cerr << "Aviso: Nenhuma voos.csv encontrada ou erro ao abrir. Iniciando sem dados de voos." << endl;
    }
}

// Métodos de Busca Interna (não-const) - para modificação
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

// Métodos de Busca Interna (const) - para acesso somente leitura
const Aeronave* Sistema::buscarAeronave(const string& codigo) const {
    for (const auto& a : aeronaves) {
        if (a.getCodigo() == codigo) {
            return &a;
        }
    }
    return nullptr;
}

const Piloto* Sistema::buscarPiloto(const string& matricula) const {
    for (const auto& p : pessoas) {
        const Piloto* piloto = dynamic_cast<const Piloto*>(p);
        if (piloto && piloto->getMatricula() == matricula) {
            return piloto;
        }
    }
    return nullptr;
}

const Passageiro* Sistema::buscarPassageiro(const string& cpf) const {
    for (const auto& p : pessoas) {
        const Passageiro* passageiro = dynamic_cast<const Passageiro*>(p);
        if (passageiro && passageiro->getCPF() == cpf) {
            return passageiro;
        }
    }
    return nullptr;
}

const Voo* Sistema::buscarVoo(const string& codigo) const {
    for (const auto& v : voos) {
        if (v.getCodigo() == codigo) {
            return &v;
        }
    }
    return nullptr;
}