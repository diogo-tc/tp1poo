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
    cout << "8. Relatórios e Estatísticas" << endl; 
    cout << "9. Salvar dados e sair" << endl;
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

#include <fstream>

void exibirSubmenuRelatorios() {
    cout << "\n======= RELATÓRIOS E ESTATÍSTICAS =======" << endl;
    cout << "1. Número total de voos cadastrados" << endl;
    cout << "2. Média de passageiros por voo" << endl;
    cout << "3. Lista de aeronaves mais utilizadas" << endl;
    cout << "4. Passageiros que participaram de mais de um voo" << endl;
    cout << "5. Voos que atingiram pelo menos 90% da capacidade máxima" << endl;
    cout << "6. Distância total percorrida por cada aeronave" << endl;
    cout << "7. Voltar ao menu principal" << endl;
    cout << "=========================================" << endl;
    cout << "Escolha uma opção: ";
}

void salvarRelatorio(const string& conteudo, const string& nomeArquivo) {
    ofstream arq(nomeArquivo);
    if (arq.is_open()) {
        arq << conteudo;
        arq.close();
        cout << "Relatório salvo em " << nomeArquivo << endl;
    } else {
        cout << "Erro ao salvar o relatório." << endl;
    }
}

void processarRelatoriosEstatisticas(Sistema& meuSistema) {
    int opcao;
    do {
        exibirSubmenuRelatorios();
        opcao = obterInt("");
        string relatorio;
        switch (opcao) {
            case 1:
                relatorio = meuSistema.relatorioTotalVoos();
                cout << relatorio;
                break;
            case 2:
                relatorio = meuSistema.relatorioMediaPassageirosPorVoo();
                cout << relatorio;
                break;
            case 3:
                relatorio = meuSistema.relatorioAeronavesMaisUtilizadas();
                cout << relatorio;
                break;
            case 4:
                relatorio = meuSistema.relatorioPassageirosMaisDeUmVoo();
                cout << relatorio;
                break;
            case 5:
                relatorio = meuSistema.relatorioVoos90PorcentoCapacidade();
                cout << relatorio;
                break;
            case 6:
                relatorio = meuSistema.relatorioDistanciaPorAeronave();
                cout << relatorio;
                break;
            case 7:
                break;
        }
        if (opcao >= 1 && opcao <= 6) {
            string salvar = obterString("Deseja salvar este relatório em um arquivo .txt? (s/n): ");
            if (salvar == "s" || salvar == "S") {
                string nomeArquivo = obterString("Nome do arquivo (ex: relatorio.txt): ");
                salvarRelatorio(relatorio, nomeArquivo);
            }
        }
    } while (opcao != 7);
}
