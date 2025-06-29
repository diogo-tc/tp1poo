#include "utilidades.h"
#include <iostream>
#include <limits> // Para numeric_limits
using namespace std; 

// Implementações das funções auxiliares de entrada
void limparBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string obterString(const string& prompt) {
    string valor;
    cout << prompt;
    getline(cin, valor);
    return valor;
}

int obterInt(const string& prompt) {
    int valor;
    cout << prompt;
    while (!(cin >> valor)) {
        cout << "Entrada inválida. Por favor, digite um número inteiro: ";
        cin.clear();
        limparBuffer();
    }
    limparBuffer();
    return valor;
}

double obterDouble(const string& prompt) {
    double valor;
    cout << prompt;
    while (!(cin >> valor)) {
        cout << "Entrada inválida. Por favor, digite um número: ";
        cin.clear();
        limparBuffer();
    }
    limparBuffer();
    return valor;
}

// Implementação da função de menu
void exibirMenu() {
    cout << "\n======= SISTEMA DE CONTROLE DE VOOS =======" << endl;
    cout << "1. Cadastrar aeronave" << endl;
    cout << "2. Cadastrar piloto" << endl;
    cout << "3. Cadastrar passageiro" << endl;
    cout << "4. Criar voo" << endl;
    cout << "5. Embarcar passageiro em voo" << endl;
    cout << "6. Listar voos" << endl;
    cout << "7. Listar passageiros de um voo" << endl;
    cout << "8. Salvar dados e sair" << endl;
    cout << "===========================================" << endl;
    cout << "Escolha uma opção: ";
}

// Implementações das funções de processamento de menu
void processarCadastrarAeronave(Sistema& meuSistema) {
    cout << "--- CADASTRO DE AERONAVE ---" << endl;
    string codigo = obterString("Código: ");
    string modelo = obterString("Modelo: ");
    int capacidade = obterInt("Capacidade: ");
    double velocidadeMedia = obterDouble("Velocidade Média (milhas/hora): ");
    double autonomia = obterDouble("Autonomia de Voo (milhas): ");

    Aeronave novaAeronave(codigo, modelo, capacidade, velocidadeMedia, autonomia);
    meuSistema.cadastrarAeronave(novaAeronave);
    meuSistema.salvarDados();
}

void processarCadastrarPiloto(Sistema& meuSistema) {
    cout << "--- CADASTRO DE PILOTO ---" << endl;
    string nome = obterString("Nome: ");
    string matricula = obterString("Matrícula: ");
    string breve = obterString("Brevê: ");
    double horasVoo = obterDouble("Horas de Voo: ");

    Piloto novoPiloto(nome, matricula, breve, horasVoo);
    meuSistema.cadastrarPiloto(novoPiloto);
    meuSistema.salvarDados();
}

void processarCadastrarPassageiro(Sistema& meuSistema) {
    cout << "--- CADASTRO DE PASSAGEIRO ---" << endl;
    string nome = obterString("Nome: ");
    string cpf = obterString("CPF: ");
    string bilhete = obterString("Número do Bilhete: ");

    Passageiro novoPassageiro(nome, cpf, bilhete);
    meuSistema.cadastrarPassageiro(novoPassageiro);
    meuSistema.salvarDados();
}

void processarCriarVoo(Sistema& meuSistema) {
    cout << "--- CRIAÇÃO DE VOO ---" << endl;
    string codigoVoo = obterString("Código do Voo: ");
    string origem = obterString("Origem: ");
    string destino = obterString("Destino: ");
    double distancia = obterDouble("Distância da Viagem (milhas): ");
    string horaSaida = obterString("Hora de Saída Prevista (HH:MM): ");

    string codAeronave = obterString("Código da Aeronave (existente): ");
    const Aeronave* aeronaveAssociada = meuSistema.buscarAeronave(codAeronave);
    if (!aeronaveAssociada) {
        cout << "Aeronave com código " << codAeronave << " não encontrada. Voo não criado." << endl;
        return;
    }

    string matComandante = obterString("Matrícula do Comandante (existente): ");
    const Piloto* comandanteVoo = meuSistema.buscarPiloto(matComandante);
    if (!comandanteVoo) {
        cout << "Piloto com matrícula " << matComandante << " não encontrado. Voo não criado." << endl;
        return;
    }

    string matPrimeiroOficial = obterString("Matrícula do Primeiro Oficial (existente): ");
    const Piloto* primeiroOficialVoo = meuSistema.buscarPiloto(matPrimeiroOficial);
    if (!primeiroOficialVoo) {
        cout << "Piloto com matrícula " << matPrimeiroOficial << " não encontrado. Voo não criado." << endl;
        return;
    }

    Voo novoVoo(codigoVoo, origem, destino, distancia, horaSaida,
                codAeronave, matComandante, matPrimeiroOficial);

    novoVoo.calcularEscalasETempo(aeronaveAssociada->getAutonomia(), aeronaveAssociada->getVelocidadeMedia());

    meuSistema.criarVoo(novoVoo);
    meuSistema.salvarDados();
}

void processarEmbarcarPassageiro(Sistema& meuSistema) {
    cout << "--- EMBARCAR PASSAGEIRO ---" << endl;
    string codigoVoo = obterString("Código do Voo: ");
    string cpfPassageiro = obterString("CPF do Passageiro: ");

    if (meuSistema.embarcarPassageiro(codigoVoo, cpfPassageiro)) {
        meuSistema.salvarDados();
    }
}

void processarListarPassageirosDoVoo(Sistema& meuSistema) {
    cout << "--- LISTAR PASSAGEIROS DE VOO ---" << endl;
    string codigoVoo = obterString("Digite o código do voo: ");
    meuSistema.listarPassageirosDoVoo(codigoVoo);
}