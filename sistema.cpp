#include "include/sistema.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <limits>
#include <map>
#include <iomanip>
#include <sstream>
using namespace std; 


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
        cout << "Erro: Aeronave com código " << aeronave.getCodigo() << " já existe." << endl;
        return;
    }
    aeronaves.push_back(aeronave);
    cout << "Aeronave " << aeronave.getCodigo() << " cadastrada com sucesso." << endl;
}

void Sistema::cadastrarPiloto(const Piloto& piloto) {
    if (buscarPiloto(piloto.getMatricula())) {
        cout << "Erro: Piloto com matrícula " << piloto.getMatricula() << " já existe." << endl;
        return;
    }
    pessoas.push_back(new Piloto(piloto));
    cout << "Piloto " << piloto.getNome() << " cadastrado com sucesso." << endl;
}

void Sistema::cadastrarPassageiro(const Passageiro& passageiro) {
    if (buscarPassageiro(passageiro.getCPF())) {
        cout << "Erro: Passageiro com CPF " << passageiro.getCPF() << " já existe." << endl;
        return;
    }
    pessoas.push_back(new Passageiro(passageiro));
    cout << "Passageiro " << passageiro.getNome() << " cadastrado com sucesso." << endl;
}

void Sistema::criarVoo(const Voo& voo) {
    if (buscarVoo(voo.getCodigo())) {
        cout << "Erro: Voo com código " << voo.getCodigo() << " já existe." << endl;
        return;
    }
    voos.push_back(voo); // Voo virá com os IDs da main
    cout << "Voo " << voo.getCodigo() << " criado com sucesso." << endl;
}

bool Sistema::embarcarPassageiro(const string& codigoVoo, const string& cpf) {
    Voo* voo = buscarVoo(codigoVoo); // Pega o Voo para modificá-lo
    Passageiro* passageiro = buscarPassageiro(cpf); // Pega o Passageiro para verificar existência

    if (!voo) {
        cout << "Erro: Voo com código " << codigoVoo << " não encontrado." << endl;
        return false;
    }
    if (!passageiro) { // Verifica se o passageiro existe no Sistema
        cout << "Erro: Passageiro com CPF " << cpf << " não encontrado." << endl;
        return false;
    }

    // Para adicionar o passageiro no Voo, precisamos da capacidade da aeronave.
    // Vamos buscar a aeronave associada ao voo.
    const Aeronave* aeronaveAssociada = buscarAeronave(voo->getCodigoAeronave());
    if (!aeronaveAssociada) {
        cout << "Erro interno: Aeronave associada ao voo " << codigoVoo << " não encontrada. Não é possível embarcar." << endl;
        return false;
    }

    //chamaa adicionarPassageiro do Voo com o CPF e a capacidade da aeronave
    if (voo->adicionarPassageiro(cpf, aeronaveAssociada->getCapacidade())) {
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

        const Aeronave* aeronave = buscarAeronave(voo.getCodigoAeronave());
        if (aeronave) {
            cout << "  Aeronave: " << aeronave->getCodigo() << " (" << aeronave->getModelo() << ")" << endl;
        } else {
            cout << "  Aeronave: N/A (Código: " << voo.getCodigoAeronave() << ")" << endl;
        }

        const Piloto* comandante = buscarPiloto(voo.getMatriculaComandante());
        if (comandante) {
            cout << "  Comandante: " << comandante->getNome() << " (Matrícula: " << comandante->getMatricula() << ")" << endl;
        } else {
            cout << "  Comandante: N/A (Matrícula: " << voo.getMatriculaComandante() << ")" << endl;
        }

        const Piloto* primeiroOficial = buscarPiloto(voo.getMatriculaPrimeiroOficial());
        if (primeiroOficial) {
            cout << "  Primeiro Oficial: " << primeiroOficial->getNome() << " (Matrícula: " << primeiroOficial->getMatricula() << ")" << endl;
        } else {
            cout << "  Primeiro Oficial: N/A (Matrícula: " << voo.getMatriculaPrimeiroOficial() << ")" << endl;
        }

        cout << "  Origem: " << voo.getOrigem() << endl;
        cout << "  Destino: " << voo.getDestino() << endl;
        cout << "  Número de Passageiros: " << voo.getCpfsPassageiros().size() << endl; // Agora pega do vetor de CPFs
        cout << "  Hora de Saída Prevista: " << voo.getHoraSaida() << endl;

        // Usa aeronave para listar o tempo e escalas
        if (aeronave) {
            // Chamando a função de Voo com os parâmetros necessários
            Voo tempVoo = voo; // Cria uma cópia temporária mutável se a função não for const
            tempVoo.calcularEscalasETempo(aeronave->getAutonomia(), aeronave->getVelocidadeMedia());
            cout << "  Tempo Estimado de Voo: " << fixed << setprecision(2) << tempVoo.getTempoEstimado() << " horas (incluindo " << tempVoo.getNumeroEscalas() << " escalas)" << endl;
        } else {
            cout << "  Tempo Estimado de Voo: N/A (Aeronave não encontrada)" << endl;
        }
        cout << "------------------------------------" << endl;
    }
}

void Sistema::listarPassageirosDoVoo(const string& codigoVoo) const {
    const Voo* voo = buscarVoo(codigoVoo); // Chama a versão const
    if (!voo) {
        cout << "Erro: Voo com código " << codigoVoo << " não encontrado." << endl;
        return;
    }

    cout << "Passageiros do Voo " << voo->getCodigo() << " (" << voo->getOrigem() << " -> " << voo->getDestino() << "):" << endl;
    const Aeronave* aeronave = buscarAeronave(voo->getCodigoAeronave());
    if (aeronave) {
        cout << "Aeronave: " << aeronave->getCodigo() << " (" << aeronave->getModelo() << ")" << endl;
    } else {
        cout << "Aeronave: N/A" << endl;
    }

    if (voo->getCpfsPassageiros().empty()) {
        cout << "Nenhum passageiro embarcado neste voo." << endl;
    } else {
        for (const auto& cpf : voo->getCpfsPassageiros()) {
            const Passageiro* p = buscarPassageiro(cpf);
            if (p) {
                cout << "- " << p->getNome() << " (CPF: " << p->getCPF() << ", Bilhete: " << p->getBilhete() << ")" << endl;
            } else {
                cout << "- Passageiro com CPF " << cpf << " não encontrado (pode ter sido removido)." << endl;
            }
        }
    }
}

void Sistema::salvarDados() const {
    ofstream arqAeronaves("aeronaves.csv");
    if (arqAeronaves.is_open()) {
        for (const auto& a : aeronaves) {
            arqAeronaves << a.toCSV() << endl;
        }
        arqAeronaves.close();
        } else {
        cerr << "Erro ao abrir aeronaves.csv para escrita." << endl;
    }

    ofstream arqPessoas("pessoas.csv");
    if (arqPessoas.is_open()) {
        for (const auto& p : pessoas) {
            arqPessoas << p->toCSV() << endl;
        }
        arqPessoas.close();
    } else {
        cerr << "Erro ao abrir pessoas.csv para escrita." << endl; 
    }

    // Salvando voos com seus passageiros associados na mesma linha
    ofstream arqVoos("voos.csv");
    if (arqVoos.is_open()) {
        for (const auto& v : voos) {
            arqVoos << v.toCSV() << endl; // O Voo::toCSV() inclui os CPFs
        }
        arqVoos.close();
       } else {
        cerr << "Erro ao abrir voos.csv para escrita." << endl;
    }
}

void Sistema::carregarDados() {
    // Limpa dados existentes antes de carregar
    aeronaves.clear();
    for (Pessoa* p : pessoas) { delete p; } // Libera memória antes de limpar
    pessoas.clear();
    voos.clear();

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
            Voo carregadoVoo = Voo::fromCSV(linha); // fromCSV de Voo retorna um Voo com IDs e CPFs preenchidos

            //Resolve os IDs para ponteiros reais e calcular escalas/tempo
            Aeronave* a = buscarAeronave(carregadoVoo.getCodigoAeronave());
            Piloto* c = buscarPiloto(carregadoVoo.getMatriculaComandante());
            Piloto* po = buscarPiloto(carregadoVoo.getMatriculaPrimeiroOficial());

            if (a && c && po) {
                // Calcula as escalas e tempo aqui, pois precisamos da Aeronave real
                carregadoVoo.calcularEscalasETempo(a->getAutonomia(), a->getVelocidadeMedia());

                // Adiciona os CPFs dos passageiros ao voo, usando buscarPassageiro
                // e a função adicionarPassageiro que espera CPF e capacidade
                for (const string& cpf : carregadoVoo.getCpfsPassageiros()) {
                    Passageiro* p = buscarPassageiro(cpf);
                    if (p) {
                        carregadoVoo.adicionarPassageiro(cpf, a->getCapacidade()); // Adiciona o CPF ao voo
                    } else {
                        cerr << "Aviso: Passageiro com CPF " << cpf << " para o voo " << carregadoVoo.getCodigo() << " não encontrado durante o carregamento (pode ter sido removido do pessoas.csv)." << endl;
                    }
                }
                voos.push_back(carregadoVoo); // Adiciona o Voo completo ao vetor do Sistema
            } else {
                cerr << "Aviso: Não foi possível carregar voo " << carregadoVoo.getCodigo() << " devido a dados ausentes de aeronave (" << carregadoVoo.getCodigoAeronave() << ") ou pilotos (" << carregadoVoo.getMatriculaComandante() << ", " << carregadoVoo.getMatriculaPrimeiroOficial() << "). Este voo será ignorado." << endl;
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

// Número total de voos cadastrados
string Sistema::relatorioTotalVoos() const {
    stringstream ss;
    ss << "Número total de voos cadastrados: " << voos.size() << endl;
    return ss.str();
}

// Média de passageiros por voo
string Sistema::relatorioMediaPassageirosPorVoo() const {
    stringstream ss;
    if (voos.empty()) {
        ss << "Nenhum voo cadastrado.\n";
        return ss.str();
    }
    size_t total = 0;
    for (const auto& v : voos) total += v.getCpfsPassageiros().size();
    double media = static_cast<double>(total) / voos.size();
    ss << fixed << setprecision(2);
    ss << "Média de passageiros por voo: " << media << endl;
    return ss.str();
}

// Lista de aeronaves mais utilizadas
string Sistema::relatorioAeronavesMaisUtilizadas() const {
    stringstream ss;
    map<string, int> uso;
    for (const auto& v : voos) uso[v.getCodigoAeronave()]++;
    int maxUso = 0;
    for (const auto& par : uso) if (par.second > maxUso) maxUso = par.second;
    ss << "Aeronaves mais utilizadas:\n";
    for (const auto& par : uso) {
        if (par.second == maxUso) {
            const Aeronave* a = buscarAeronave(par.first);
            ss << "- " << (a ? a->getModelo() : "Desconhecida") << " (Código: " << par.first << "), " << par.second << " voos\n";
        }
    }
    return ss.str();
}

// Passageiros que participaram de mais de um voo
string Sistema::relatorioPassageirosMaisDeUmVoo() const {
    stringstream ss;
    map<string, int> contagem;
    for (const auto& v : voos)
        for (const auto& cpf : v.getCpfsPassageiros())
            contagem[cpf]++;
    ss << "Passageiros que participaram de mais de um voo:\n";
    bool achou = false;
    for (const auto& par : contagem) {
        if (par.second > 1) {
            const Passageiro* p = buscarPassageiro(par.first);
            ss << "- " << (p ? p->getNome() : "Desconhecido") << " (CPF: " << par.first << "), " << par.second << " voos\n";
            achou = true;
        }
    }
    if (!achou) ss << "Nenhum passageiro participou de mais de um voo.\n";
    return ss.str();
}

// Voos que atingiram pelo menos 90% da capacidade máxima
string Sistema::relatorioVoos90PorcentoCapacidade() const {
    stringstream ss;
    ss << "Voos que atingiram pelo menos 90% da capacidade máxima:\n";
    bool achou = false;
    for (const auto& v : voos) {
        const Aeronave* a = buscarAeronave(v.getCodigoAeronave());
        if (a && a->getCapacidade() > 0) {
            double ocup = (double)v.getCpfsPassageiros().size() / a->getCapacidade();
            if (ocup >= 0.9) {
                ss << "- Voo " << v.getCodigo() << " (" << v.getCpfsPassageiros().size() << "/" << a->getCapacidade() << ")\n";
                achou = true;
            }
        }
    }
    if (!achou) ss << "Nenhum voo atingiu 90% da capacidade.\n";
    return ss.str();
}

// Distância total percorrida por cada aeronave
string Sistema::relatorioDistanciaPorAeronave() const {
    stringstream ss;
    map<string, double> dist;
    for (const auto& v : voos)
        dist[v.getCodigoAeronave()] += v.getDistancia();
    ss << "Distância total percorrida por cada aeronave:\n";
    for (const auto& par : dist) {
        const Aeronave* a = buscarAeronave(par.first);
        ss << "- " << (a ? a->getModelo() : "Desconhecida") << " (Código: " << par.first << "): " << fixed << setprecision(2) << par.second << " milhas\n";
    }
    return ss.str();
}
