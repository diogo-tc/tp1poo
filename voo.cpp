#include "Voo.h"
#include <sstream>
#include <iostream>
#include <stdexcept> // Para stod
using namespace std;

// Construtor padrão
Voo::Voo() : distancia(0.0), aeronave(nullptr), comandante(nullptr), primeiroOficial(nullptr), numeroEscalas(0), tempoEstimado(0.0) {}

// Construtor com parâmetros
Voo::Voo(const string& codigo, const string& origem, const string& destino, double distancia, const string& horaSaida,
         Aeronave* aeronave, Piloto* comandante, Piloto* primeiroOficial)
    : codigo(codigo), origem(origem), destino(destino), distancia(distancia), horaSaida(horaSaida),
      aeronave(aeronave), comandante(comandante), primeiroOficial(primeiroOficial) {
    calcularEscalasETempo();
}

// Getters e Setters
string Voo::getCodigo() const {
    return codigo;
}

void Voo::setCodigo(const string& codigo) {
    this->codigo = codigo;
}

string Voo::getOrigem() const {
    return origem;
}

void Voo::setOrigem(const string& origem) {
    this->origem = origem;
}

string Voo::getDestino() const {
    return destino;
}

void Voo::setDestino(const string& destino) {
    this->destino = destino;
}

double Voo::getDistancia() const {
    return distancia;
}

void Voo::setDistancia(double distancia) {
    this->distancia = distancia;
    calcularEscalasETempo(); // Recalcular ao mudar a distância
}

string Voo::getHoraSaida() const {
    return horaSaida;
}

void Voo::setHoraSaida(const string& hora) {
    this->horaSaida = hora;
}

int Voo::getNumeroEscalas() const {
    return numeroEscalas;
}

double Voo::getTempoEstimado() const {
    return tempoEstimado;
}

Aeronave* Voo::getAeronave() const {
    return aeronave;
}

void Voo::setAeronave(Aeronave* aeronave) {
    this->aeronave = aeronave;
    calcularEscalasETempo(); // Recalcular ao mudar a aeronave
}

Piloto* Voo::getComandante() const {
    return comandante;
}

void Voo::setComandante(Piloto* comandante) {
    this->comandante = comandante;
}

Piloto* Voo::getPrimeiroOficial() const {
    return primeiroOficial;
}

void Voo::setPrimeiroOficial(Piloto* oficial) {
    this->primeiroOficial = oficial;
}

const vector<Passageiro*>& Voo::getPassageiros() const {
    return passageiros;
}

bool Voo::adicionarPassageiro(Passageiro* passageiro) {
    if (aeronave && passageiros.size() < aeronave->getCapacidade()) {
        // Verificar se o passageiro já está no voo para evitar duplicatas
        for (const auto& p : passageiros) {
            if (p && passageiro && p->getCPF() == passageiro->getCPF()) {
                cout << "Passageiro com CPF " << passageiro->getCPF() << " já está neste voo." << endl;
                return false;
            }
        }
        passageiros.push_back(passageiro);
        return true;
    }
    return false;
}

void Voo::calcularEscalasETempo() {
    if (aeronave) {
        if (aeronave->getAutonomia() > 0) {
            numeroEscalas = static_cast<int>(distancia / aeronave->getAutonomia());
        } else {
            numeroEscalas = 0;
        }

        if (aeronave->getVelocidadeMedia() > 0) {
            tempoEstimado = distancia / aeronave->getVelocidadeMedia();
        } else {
            tempoEstimado = 0.0;
        }
        tempoEstimado += (numeroEscalas * 1.0); 
    } else {
        numeroEscalas = 0;
        tempoEstimado = 0.0;
    }
}

// MODIFICADO: Adiciona CPFs dos passageiros ao final da linha CSV
string Voo::toCSV() const {
    stringstream ss;
    ss << codigo << ","
       << origem << ","
       << destino << ","
       << distancia << ","
       << horaSaida << ",";
    if (aeronave) {
        ss << aeronave->getCodigo();
    } else {
        ss << "N/A";
    }
    ss << ",";
    if (comandante) {
        ss << comandante->getMatricula();
    } else {
        ss << "N/A";
    }
    ss << ",";
    if (primeiroOficial) {
        ss << primeiroOficial->getMatricula();
    } else {
        ss << "N/A";
    }

    // Adicionar CPFs dos passageiros, separados por ponto e vírgula
    ss << ","; // Separador para a lista de passageiros
    for (size_t i = 0; i < passageiros.size(); ++i) {
        if (passageiros[i]) {
            ss << passageiros[i]->getCPF();
            if (i < passageiros.size() - 1) {
                ss << ";"; // Usar ponto e vírgula como delimitador entre CPFs
            }
        }
    }
    return ss.str();
}

// fromCSV de Voo é um parser BÁSICO, Sistema fará as associações reais.
Voo Voo::fromCSV(const string& linha) {
    stringstream ss(linha);
    string codigo, origem, destino, horaSaida, sDistancia;
    string codAeronave, matComandante, matPrimeiroOficial, cpfsPassageirosStr; // cpfsPassageirosStr para capturar a parte dos CPFs
    double distancia;

    getline(ss, codigo, ',');
    getline(ss, origem, ',');
    getline(ss, destino, ',');
    getline(ss, sDistancia, ',');
    distancia = stod(sDistancia);
    getline(ss, horaSaida, ',');
    getline(ss, codAeronave, ',');
    getline(ss, matComandante, ',');
    getline(ss, matPrimeiroOficial, ','); // Lê até a vírgula antes dos CPFs
    getline(ss, cpfsPassageirosStr); // Lê o restante da linha para os CPFs

    // Voo::fromCSV não tem acesso ao Sistema para buscar objetos reais.
    // Ele apenas cria um objeto Voo com as informações básicas.
    // A associação dos ponteiros de Aeronave/Piloto e passageiros será feita
    // posteriormente na função Sistema::carregarDados().
    Aeronave* a = nullptr;
    Piloto* c = nullptr;
    Piloto* po = nullptr;

    Voo v(codigo, origem, destino, distancia, horaSaida, a, c, po);
    v.calcularEscalasETempo();
    return v;
}

void Voo::listarPassageiros() const {
    cout << "Passageiros do Voo " << codigo << " (" << origem << " -> " << destino << "):" << endl;
    if (aeronave) {
        cout << "Aeronave: " << aeronave->getCodigo() << " (" << aeronave->getModelo() << ")" << endl;
    } else {
        cout << "Aeronave: N/A" << endl;
    }

    if (passageiros.empty()) {
        cout << "Nenhum passageiro embarcado neste voo." << endl;
    } else {
        for (const auto& p : passageiros) {
            cout << "- " << p->getNome() << " (CPF: " << p->getCPF() << ", Bilhete: " << p->getBilhete() << ")" << endl;
        }
    }
}