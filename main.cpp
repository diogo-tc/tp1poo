#include <iostream>
#include <limits>
#include <string>
#include "Sistema.h"
#include "Aeronave.h"
#include "Pessoa.h"
#include "Voo.h"

// Função auxiliar para limpar o buffer de entrada
void limparBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Função para exibir o menu
void exibirMenu() {
    std::cout << "\n======= SISTEMA DE CONTROLE DE VOOS =======" << std::endl;
    std::cout << "1. Cadastrar aeronave" << std::endl;
    std::cout << "2. Cadastrar piloto" << std::endl;
    std::cout << "3. Cadastrar passageiro" << std::endl;
    std::cout << "4. Criar voo" << std::endl;
    std::cout << "5. Embarcar passageiro em voo" << std::endl;
    std::cout << "6. Listar voos" << std::endl;
    std::cout << "7. Listar passageiros de um voo" << std::endl;
    std::cout << "8. Salvar dados e sair" << std::endl;
    std::cout << "===========================================" << std::endl;
    std::cout << "Escolha uma opção: ";
}

int main() {
    Sistema meuSistema;
    meuSistema.carregarDados(); // Tenta carregar dados ao iniciar

    int opcao;
    do {
        exibirMenu();
        // Verifica se a entrada é um número inteiro
        while (!(std::cin >> opcao)) {
            std::cout << "Entrada inválida. Por favor, digite um número: ";
            std::cin.clear(); // Limpa o estado de erro
            limparBuffer();   // Descarta a entrada incorreta
        }
        limparBuffer(); // Limpa o buffer após ler o número

        switch (opcao) {
            case 1: { // Cadastrar aeronave
                std::string codigo, modelo;
                int capacidade;
                double velocidadeMedia, autonomia;

                std::cout << "--- CADASTRO DE AERONAVE ---" << std::endl;
                std::cout << "Código: ";
                std::getline(std::cin, codigo);
                std::cout << "Modelo: ";
                std::getline(std::cin, modelo);
                std::cout << "Capacidade: ";
                while (!(std::cin >> capacidade)) {
                    std::cout << "Entrada inválida. Digite um número inteiro para capacidade: ";
                    std::cin.clear();
                    limparBuffer();
                }
                std::cout << "Velocidade Média (milhas/hora): ";
                while (!(std::cin >> velocidadeMedia)) {
                    std::cout << "Entrada inválida. Digite um número para velocidade média: ";
                    std::cin.clear();
                    limparBuffer();
                }
                std::cout << "Autonomia de Voo (milhas): ";
                while (!(std::cin >> autonomia)) {
                    std::cout << "Entrada inválida. Digite um número para autonomia: ";
                    std::cin.clear();
                    limparBuffer();
                }
                limparBuffer();

                Aeronave novaAeronave(codigo, modelo, capacidade, velocidadeMedia, autonomia);
                meuSistema.cadastrarAeronave(novaAeronave);
                meuSistema.salvarDados(); // Salva após o cadastro
                break;
            }
            case 2: { // Cadastrar piloto
                std::string nome, matricula, breve;
                double horasVoo;

                std::cout << "--- CADASTRO DE PILOTO ---" << std::endl;
                std::cout << "Nome: ";
                std::getline(std::cin, nome);
                std::cout << "Matrícula: ";
                std::getline(std::cin, matricula);
                std::cout << "Brevê: ";
                std::getline(std::cin, breve);
                std::cout << "Horas de Voo: ";
                while (!(std::cin >> horasVoo)) {
                    std::cout << "Entrada inválida. Digite um número para horas de voo: ";
                    std::cin.clear();
                    limparBuffer();
                }
                limparBuffer();

                Piloto novoPiloto(nome, matricula, breve, horasVoo);
                meuSistema.cadastrarPiloto(novoPiloto);
                meuSistema.salvarDados(); // Salva após o cadastro
                break;
            }
            case 3: { // Cadastrar passageiro
                std::string nome, cpf, bilhete;

                std::cout << "--- CADASTRO DE PASSAGEIRO ---" << std::endl;
                std::cout << "Nome: ";
                std::getline(std::cin, nome);
                std::cout << "CPF: ";
                std::getline(std::cin, cpf);
                std::cout << "Número do Bilhete: ";
                std::getline(std::cin, bilhete);

                Passageiro novoPassageiro(nome, cpf, bilhete);
                meuSistema.cadastrarPassageiro(novoPassageiro);
                meuSistema.salvarDados(); // Salva após o cadastro
                break;
            }
            case 4: { // Criar voo
                std::string codigoVoo, origem, destino, horaSaida, codAeronave, matComandante, matPrimeiroOficial;
                double distancia;

                std::cout << "--- CRIAÇÃO DE VOO ---" << std::endl;
                std::cout << "Código do Voo: ";
                std::getline(std::cin, codigoVoo);
                std::cout << "Origem: ";
                std::getline(std::cin, origem);
                std::cout << "Destino: ";
                std::getline(std::cin, destino);
                std::cout << "Distância da Viagem (milhas): ";
                while (!(std::cin >> distancia)) {
                    std::cout << "Entrada inválida. Digite um número para a distância: ";
                    std::cin.clear();
                    limparBuffer();
                }
                limparBuffer();
                std::cout << "Hora de Saída Prevista (HH:MM): ";
                std::getline(std::cin, horaSaida);

                std::cout << "Código da Aeronave (existente): ";
                std::getline(std::cin, codAeronave);
                // Buscar Aeronave, Comandante e Primeiro Oficial apenas para VERIFICAR existência
                const Aeronave* aeronaveAssociada = meuSistema.buscarAeronave(codAeronave);
                if (!aeronaveAssociada) {
                    std::cout << "Aeronave com código " << codAeronave << " não encontrada. Voo não criado." << std::endl;
                    break;
                }

                std::cout << "Matrícula do Comandante (existente): ";
                std::getline(std::cin, matComandante);
                const Piloto* comandanteVoo = meuSistema.buscarPiloto(matComandante);
                if (!comandanteVoo) {
                    std::cout << "Piloto com matrícula " << matComandante << " não encontrado. Voo não criado." << std::endl;
                    break;
                }

                std::cout << "Matrícula do Primeiro Oficial (existente): ";
                std::getline(std::cin, matPrimeiroOficial);
                const Piloto* primeiroOficialVoo = meuSistema.buscarPiloto(matPrimeiroOficial);
                if (!primeiroOficialVoo) {
                    std::cout << "Piloto com matrícula " << matPrimeiroOficial << " não encontrado. Voo não criado." << std::endl;
                    break;
                }
                // Criação do Voo com IDs (strings)
                Voo novoVoo(codigoVoo, origem, destino, distancia, horaSaida, codAeronave, matComandante, matPrimeiroOficial);

                // IMPORTANTE: Chamar calcularEscalasETempo aqui, passando os dados da aeronave
                novoVoo.calcularEscalasETempo(aeronaveAssociada->getAutonomia(), aeronaveAssociada->getVelocidadeMedia());

                meuSistema.criarVoo(novoVoo);
                meuSistema.salvarDados(); // Salva após o cadastro
                break;
            }
            case 5: { // Embarcar passageiro em voo
                std::string codigoVoo, cpfPassageiro;

                std::cout << "--- EMBARCAR PASSAGEIRO ---" << std::endl;
                std::cout << "Código do Voo: ";
                std::getline(std::cin, codigoVoo);
                std::cout << "CPF do Passageiro: ";
                std::getline(std::cin, cpfPassageiro);

                if (meuSistema.embarcarPassageiro(codigoVoo, cpfPassageiro)) {
                    meuSistema.salvarDados(); // Salva após o embarque bem-sucedido
                }
                break;
            }
            case 6: { // Listar voos
                meuSistema.listarVoos();
                break;
            }
            case 7: { // Listar passageiros de um voo
                std::string codigoVoo;
                std::cout << "--- LISTAR PASSAGEIROS DE VOO ---" << std::endl;
                std::cout << "Digite o código do voo: ";
                std::getline(std::cin, codigoVoo);
                meuSistema.listarPassageirosDoVoo(codigoVoo);
                break;
            }
            case 8: { // Salvar dados e sair
                meuSistema.salvarDados();
                std::cout << "Dados salvos. Encerrando o sistema." << std::endl;
                break;
            }
            default: {
                std::cout << "Opção inválida. Tente novamente." << std::endl;
                break;
            }
        }
    } while (opcao != 8);

    return 0;
}