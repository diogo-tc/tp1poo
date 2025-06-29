#include "Sistema.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <limits>
#include <sstream>

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
    if (buscarAeronave(aeronave.getCodigo())) {
        std::cout << "Erro: Aeronave com código " << aeronave.getCodigo() << " já existe." << std::endl;
        return;
    }
    aeronaves.push_back(aeronave);
    std::cout << "Aeronave " << aeronave.getCodigo() << " cadastrada com sucesso." << std::endl;
}

void Sistema::cadastrarPiloto(const Piloto& piloto) {
    if (buscarPiloto(piloto.getMatricula())) {
        std::cout << "Erro: Piloto com matrícula " << piloto.getMatricula() << " já existe." << std::endl;
        return;
    }
    pessoas.push_back(new Piloto(piloto));
    std::cout << "Piloto " << piloto.getNome() << " cadastrado com sucesso." << std::endl;
}

void Sistema::cadastrarPassageiro(const Passageiro& passageiro) {
    if (buscarPassageiro(passageiro.getCPF())) {
        std::cout << "Erro: Passageiro com CPF " << passageiro.getCPF() << " já existe." << std::endl;
        return;
    }
    pessoas.push_back(new Passageiro(passageiro));
    std::cout << "Passageiro " << passageiro.getNome() << " cadastrado com sucesso." << std::endl;
}

void Sistema::criarVoo(const Voo& voo) {
    if (buscarVoo(voo.getCodigo())) {
        std::cout << "Erro: Voo com código " << voo.getCodigo() << " já existe." << std::endl;
        return;
    }
    voos.push_back(voo); // Voo já virá com os IDs da main
    std::cout << "Voo " << voo.getCodigo() << " criado com sucesso." << std::endl;
}

bool Sistema::embarcarPassageiro(const std::string& codigoVoo, const std::string& cpf) {
    Voo* voo = buscarVoo(codigoVoo); // Pega o Voo (não-const) para modificá-lo
    Passageiro* passageiro = buscarPassageiro(cpf); // Pega o Passageiro (não-const) para verificar existência

    if (!voo) {
        std::cout << "Erro: Voo com código " << codigoVoo << " não encontrado." << std::endl;
        return false;
    }
    if (!passageiro) { // Verifica se o passageiro existe no Sistema
        std::cout << "Erro: Passageiro com CPF " << cpf << " não encontrado." << std::endl;
        return false;
    }

    // Para adicionar o passageiro no Voo, precisamos da capacidade da aeronave.
    // Vamos buscar a aeronave associada ao voo.
    const Aeronave* aeronaveAssociada = buscarAeronave(voo->getCodigoAeronave());
    if (!aeronaveAssociada) {
        std::cout << "Erro interno: Aeronave associada ao voo " << codigoVoo << " não encontrada. Não é possível embarcar." << std::endl;
        return false;
    }

    // Agora, chamar adicionarPassageiro do Voo com o CPF e a capacidade da aeronave
    if (voo->adicionarPassageiro(cpf, aeronaveAssociada->getCapacidade())) {
        std::cout << "Passageiro " << passageiro->getNome() << " embarcado no voo " << voo->getCodigo() << " com sucesso." << std::endl;
        return true;
    } else {
        std::cout << "Erro: Não foi possível embarcar o passageiro no voo " << voo->getCodigo() << ". Capacidade máxima atingida ou passageiro já embarcado." << std::endl;
        return false;
    }
}

void Sistema::listarVoos() const {
    std::cout << "\n===== LISTAGEM DE VOOS =====" << std::endl;
    if (voos.empty()) {
        std::cout << "Nenhum voo cadastrado." << std::endl;
        return;
    }
    for (const auto& voo : voos) {
        std::cout << "Código do Voo: " << voo.getCodigo() << std::endl;

        const Aeronave* aeronave = buscarAeronave(voo.getCodigoAeronave());
        if (aeronave) {
            std::cout << "  Aeronave: " << aeronave->getCodigo() << " (" << aeronave->getModelo() << ")" << std::endl;
        } else {
            std::cout << "  Aeronave: N/A (Código: " << voo.getCodigoAeronave() << ")" << std::endl;
        }

        const Piloto* comandante = buscarPiloto(voo.getMatriculaComandante());
        if (comandante) {
            std::cout << "  Comandante: " << comandante->getNome() << " (Matrícula: " << comandante->getMatricula() << ")" << std::endl;
        } else {
            std::cout << "  Comandante: N/A (Matrícula: " << voo.getMatriculaComandante() << ")" << std::endl;
        }

        const Piloto* primeiroOficial = buscarPiloto(voo.getMatriculaPrimeiroOficial());
        if (primeiroOficial) {
            std::cout << "  Primeiro Oficial: " << primeiroOficial->getNome() << " (Matrícula: " << primeiroOficial->getMatricula() << ")" << std::endl;
        } else {
            std::cout << "  Primeiro Oficial: N/A (Matrícula: " << voo.getMatriculaPrimeiroOficial() << ")" << std::endl;
        }

        std::cout << "  Origem: " << voo.getOrigem() << std::endl;
        std::cout << "  Destino: " << voo.getDestino() << std::endl;
        std::cout << "  Número de Passageiros: " << voo.getCpfsPassageiros().size() << std::endl; // Agora pega do vetor de CPFs
        std::cout << "  Hora de Saída Prevista: " << voo.getHoraSaida() << std::endl;

        // Para listar o tempo e escalas, precisamos da aeronave (const)
        if (aeronave) {
            // Chamando a função de Voo com os parâmetros necessários
            Voo tempVoo = voo; // Cria uma cópia temporária mutável se a função não for const
            tempVoo.calcularEscalasETempo(aeronave->getAutonomia(), aeronave->getVelocidadeMedia());
            std::cout << "  Tempo Estimado de Voo: " << tempVoo.getTempoEstimado() << " horas (incluindo " << tempVoo.getNumeroEscalas() << " escalas)" << std::endl;
        } else {
            std::cout << "  Tempo Estimado de Voo: N/A (Aeronave não encontrada)" << std::endl;
        }
        std::cout << "------------------------------------" << std::endl;
    }
}

void Sistema::listarPassageirosDoVoo(const std::string& codigoVoo) const {
    const Voo* voo = buscarVoo(codigoVoo); // Chama a versão const
    if (!voo) {
        std::cout << "Erro: Voo com código " << codigoVoo << " não encontrado." << std::endl;
        return;
    }

    std::cout << "Passageiros do Voo " << voo->getCodigo() << " (" << voo->getOrigem() << " -> " << voo->getDestino() << "):" << std::endl;
    const Aeronave* aeronave = buscarAeronave(voo->getCodigoAeronave());
    if (aeronave) {
        std::cout << "Aeronave: " << aeronave->getCodigo() << " (" << aeronave->getModelo() << ")" << std::endl;
    } else {
        std::cout << "Aeronave: N/A" << std::endl;
    }

    if (voo->getCpfsPassageiros().empty()) {
        std::cout << "Nenhum passageiro embarcado neste voo." << std::endl;
    } else {
        for (const auto& cpf : voo->getCpfsPassageiros()) {
            const Passageiro* p = buscarPassageiro(cpf);
            if (p) {
                std::cout << "- " << p->getNome() << " (CPF: " << p->getCPF() << ", Bilhete: " << p->getBilhete() << ")" << std::endl;
            } else {
                std::cout << "- Passageiro com CPF " << cpf << " não encontrado (pode ter sido removido)." << std::endl;
            }
        }
    }
}

void Sistema::salvarDados() const {
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

    std::ofstream arqPessoas("pessoas.csv");
    if (arqPessoas.is_open()) {
        for (const auto& p : pessoas) {
            arqPessoas << p->toCSV() << std::endl;
        }
        arqPessoas.close();
        std::cout << "Pessoas salvas em pessoas.csv" << std::endl;
    } else {
        std::cerr << "Erro ao abrir pessoas.csv para escrita." << std::endl;
    }

    // Salvando voos com seus passageiros associados na mesma linha
    std::ofstream arqVoos("voos.csv");
    if (arqVoos.is_open()) {
        for (const auto& v : voos) {
            arqVoos << v.toCSV() << std::endl; // O Voo::toCSV() agora inclui os CPFs
        }
        arqVoos.close();
        std::cout << "Voos (com passageiros) salvos em voos.csv" << std::endl;
    } else {
        std::cerr << "Erro ao abrir voos.csv para escrita." << std::endl;
    }
}

void Sistema::carregarDados() {
    // Limpa dados existentes antes de carregar
    aeronaves.clear();
    for (Pessoa* p : pessoas) { delete p; } // Libera memória antes de limpar
    pessoas.clear();
    voos.clear();

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
        std::cerr << "Aviso: Nenhuma aeronaves.csv encontrada ou erro ao abrir. Iniciando sem dados de aeronaves." << std::endl;
    }

    // Carregar pessoas (pilotos e passageiros)
    std::ifstream arqPessoas("pessoas.csv");
    if (arqPessoas.is_open()) {
        std::string linha;
        while (std::getline(arqPessoas, linha)) {
            std::stringstream ss(linha);
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
        std::cerr << "Aviso: Nenhuma pessoas.csv encontrada ou erro ao abrir. Iniciando sem dados de pessoas." << std::endl;
    }

    // Carregar voos e suas associações de passageiros
    std::ifstream arqVoos("voos.csv");
    if (arqVoos.is_open()) {
        std::string linha;
        while (std::getline(arqVoos, linha)) {
            Voo carregadoVoo = Voo::fromCSV(linha); // fromCSV de Voo agora retorna um Voo com IDs e CPFs preenchidos

            // Agora, vamos resolver os IDs para ponteiros reais e calcular escalas/tempo
            Aeronave* a = buscarAeronave(carregadoVoo.getCodigoAeronave());
            Piloto* c = buscarPiloto(carregadoVoo.getMatriculaComandante());
            Piloto* po = buscarPiloto(carregadoVoo.getMatriculaPrimeiroOficial());

            if (a && c && po) {
                // Se o Voo::fromCSV retornasse ponteiros (como antes),
                // teríamos que setar aqui: carregadoVoo.setAeronave(a); etc.
                // Mas como ele não armazena mais ponteiros, os dados já estão ali.

                // Calculamos as escalas e tempo AQUI, pois precisamos da Aeronave real
                carregadoVoo.calcularEscalasETempo(a->getAutonomia(), a->getVelocidadeMedia());

                // Adicionamos os CPFs dos passageiros ao voo, usando buscarPassageiro
                // e a função adicionarPassageiro que espera CPF e capacidade
                for (const std::string& cpf : carregadoVoo.getCpfsPassageiros()) {
                    Passageiro* p = buscarPassageiro(cpf);
                    if (p) {
                        carregadoVoo.adicionarPassageiro(cpf, a->getCapacidade()); // Adiciona o CPF ao voo
                    } else {
                        std::cerr << "Aviso: Passageiro com CPF " << cpf << " para o voo " << carregadoVoo.getCodigo() << " não encontrado durante o carregamento (pode ter sido removido do pessoas.csv)." << std::endl;
                    }
                }
                voos.push_back(carregadoVoo); // Adiciona o Voo completo ao vetor do Sistema
            } else {
                std::cerr << "Aviso: Não foi possível carregar voo " << carregadoVoo.getCodigo() << " devido a dados ausentes de aeronave (" << carregadoVoo.getCodigoAeronave() << ") ou pilotos (" << carregadoVoo.getMatriculaComandante() << ", " << carregadoVoo.getMatriculaPrimeiroOficial() << "). Este voo será ignorado." << std::endl;
            }
        }
        arqVoos.close();
        std::cout << "Voos (com passageiros) carregados de voos.csv" << std::endl;
    } else {
        std::cerr << "Aviso: Nenhuma voos.csv encontrada ou erro ao abrir. Iniciando sem dados de voos." << std::endl;
    }
}

// Métodos de Busca Interna (não-const) - para modificação
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

// Métodos de Busca Interna (const) - para acesso somente leitura
const Aeronave* Sistema::buscarAeronave(const std::string& codigo) const {
    for (const auto& a : aeronaves) {
        if (a.getCodigo() == codigo) {
            return &a;
        }
    }
    return nullptr;
}

const Piloto* Sistema::buscarPiloto(const std::string& matricula) const {
    for (const auto& p : pessoas) {
        const Piloto* piloto = dynamic_cast<const Piloto*>(p);
        if (piloto && piloto->getMatricula() == matricula) {
            return piloto;
        }
    }
    return nullptr;
}

const Passageiro* Sistema::buscarPassageiro(const std::string& cpf) const {
    for (const auto& p : pessoas) {
        const Passageiro* passageiro = dynamic_cast<const Passageiro*>(p);
        if (passageiro && passageiro->getCPF() == cpf) {
            return passageiro;
        }
    }
    return nullptr;
}

const Voo* Sistema::buscarVoo(const std::string& codigo) const {
    for (const auto& v : voos) {
        if (v.getCodigo() == codigo) {
            return &v;
        }
    }
    return nullptr;
}