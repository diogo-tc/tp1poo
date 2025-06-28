#include <iostream>    // Para cout, cin, endl
#include <limits>      // Para numeric_limits
#include <string>      // Para string
#include "Sistema.h"
#include "Aeronave.h"  // Embora Sistema.h já inclua, é bom para clareza
#include "Pessoa.h"    // Embora Sistema.h já inclua, é bom para clareza
#include "Voo.h"       // Embora Sistema.h já inclua, é bom para clareza

using namespace std;

// Função auxiliar para limpar o buffer de entrada
void limparBuffer() {
    // Ignora caracteres restantes no buffer de entrada até o próximo '\n'
    // ou até que o limite máximo de caracteres seja atingido.
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Função para exibir o menu
void exibirMenu() {
    cout << "\n======= SISTEMA DE CONTROLE DE VOOS =======" << endl;
    cout << "1. Cadastrar aeronave" << endl; 
    cout << "2. Cadastrar piloto" << endl; 
    cout << "3. Cadastrar passageiro" << endl;
    cout << "4. Criar voo" << endl; 
    cout << "5. Embarcar passageiro em voo" << endl;
    cout << "6. Listar voos" << endl; 
    cout << "7. Listar passageiros de um voo" << endl;
    cout << "8. Salvar dados e sair" << endl; // (Adaptado de "Gerar relatórios e estatísticas" para "Salvar dados e sair" para o caso de uso básico)
    cout << "===========================================" << endl;
    cout << "Escolha uma opção: ";
}

int main() {
    Sistema meuSistema;
    meuSistema.carregarDados(); // Tenta carregar dados ao iniciar o programa

    int opcao;
    do {
        exibirMenu();
        cin >> opcao;
        limparBuffer(); // Limpa o buffer após ler o número para evitar problemas com getline()

        switch (opcao) {
            case 1: { // Cadastrar aeronave [: 16]
                string codigo, modelo;
                int capacidade;
                double velocidadeMedia, autonomia;

                cout << "--- CADASTRO DE AERONAVE ---" << endl;
                cout << "Código: ";
                getline(cin, codigo);
                cout << "Modelo: ";
                getline(cin, modelo);
                cout << "Capacidade: ";
                cin >> capacidade;
                cout << "Velocidade Média (milhas/hora): ";
                cin >> velocidadeMedia;
                cout << "Autonomia de Voo (milhas): ";
                cin >> autonomia;
                limparBuffer(); // Limpa novamente após a última leitura numérica

                Aeronave novaAeronave(codigo, modelo, capacidade, velocidadeMedia, autonomia);
                meuSistema.cadastrarAeronave(novaAeronave);
                break;
            }
            case 2: { // Cadastrar piloto
                string nome, matricula, breve;
                double horasVoo;

                cout << "--- CADASTRO DE PILOTO ---" << endl;
                cout << "Nome: ";
                getline(cin, nome);
                cout << "Matrícula: ";
                getline(cin, matricula);
                cout << "Brevê: ";
                getline(cin, breve);
                cout << "Horas de Voo: ";
                cin >> horasVoo;
                limparBuffer();

                Piloto novoPiloto(nome, matricula, breve, horasVoo);
                meuSistema.cadastrarPiloto(novoPiloto);
                break;
            }
            case 3: { // Cadastrar passageiro
                string nome, cpf, bilhete;

                cout << "--- CADASTRO DE PASSAGEIRO ---" << endl;
                cout << "Nome: ";
                getline(cin, nome);
                cout << "CPF: ";
                getline(cin, cpf);
                cout << "Número do Bilhete: ";
                getline(cin, bilhete);

                Passageiro novoPassageiro(nome, cpf, bilhete);
                meuSistema.cadastrarPassageiro(novoPassageiro);
                break;
            }
            case 4: { // Criar voo
                string codigoVoo, origem, destino, horaSaida, codAeronave, matComandante, matPrimeiroOficial;
                double distancia;

                cout << "--- CRIAÇÃO DE VOO ---" << endl;
                cout << "Código do Voo: ";
                getline(cin, codigoVoo);
                cout << "Origem: ";
                getline(cin, origem);
                cout << "Destino: ";
                getline(cin, destino);
                cout << "Distância da Viagem (milhas): ";
                cin >> distancia;
                limparBuffer(); // Limpa após ler double
                cout << "Hora de Saída Prevista (HH:MM): ";
                getline(cin, horaSaida);

                cout << "Código da Aeronave (existente): ";
                getline(cin, codAeronave);
                Aeronave* aeronaveAssociada = meuSistema.buscarAeronave(codAeronave);
                if (!aeronaveAssociada) {
                    cout << "Aeronave com código " << codAeronave << " não encontrada. Voo não criado." << endl;
                    break;
                }

                cout << "Matrícula do Comandante (existente): ";
                getline(cin, matComandante);
                Piloto* comandanteVoo = meuSistema.buscarPiloto(matComandante);
                if (!comandanteVoo) {
                    cout << "Piloto com matrícula " << matComandante << " não encontrado. Voo não criado." << endl;
                    break;
                }

                cout << "Matrícula do Primeiro Oficial (existente): ";
                getline(cin, matPrimeiroOficial);
                Piloto* primeiroOficialVoo = meuSistema.buscarPiloto(matPrimeiroOficial);
                if (!primeiroOficialVoo) {
                    cout << "Piloto com matrícula " << matPrimeiroOficial << " não encontrado. Voo não criado." << endl;
                    break;
                }
                // Criação do Voo com ponteiros válidos
                Voo novoVoo(codigoVoo, origem, destino, distancia, horaSaida, aeronaveAssociada, comandanteVoo, primeiroOficialVoo);
                meuSistema.criarVoo(novoVoo);
                break;
            }
            case 5: { // Embarcar passageiro em voo
                string codigoVoo, cpfPassageiro;

                cout << "--- EMBARCAR PASSAGEIRO ---" << endl;
                cout << "Código do Voo: ";
                getline(cin, codigoVoo);
                cout << "CPF do Passageiro: ";
                getline(cin, cpfPassageiro);

                meuSistema.embarcarPassageiro(codigoVoo, cpfPassageiro);
                break;
            }
            case 6: { // Listar voos
                meuSistema.listarVoos();
                break;
            }
            case 7: { // Listar passageiros de um voo
                string codigoVoo;
                cout << "--- LISTAR PASSAGEIROS DE VOO ---" << endl;
                cout << "Digite o código do voo: ";
                getline(cin, codigoVoo);
                meuSistema.listarPassageirosDoVoo(codigoVoo);
                break;
            }
            case 8: { // Salvar dados e sair
                meuSistema.salvarDados();
                cout << "Dados salvos. Encerrando o sistema." << endl;
                break;
            }
            default: {
                cout << "Opção inválida. Tente novamente." << endl;
                break;
            }
        }
    } while (opcao != 8);

    return 0;
}
//