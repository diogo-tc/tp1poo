#include "Voo.h"
#include <sstream> // Para toCSV e fromCSV
#include <iostream> // Para listarPassageiros

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
    [cite_start]// Verificar se a aeronave tem capacidade para mais passageiros [cite: 16]
    if (aeronave && passageiros.size() < aeronave->getCapacidade()) {
        passageiros.push_back(passageiro);
        return true;
    }
    return false;
}

void Voo::calcularEscalasETempo() {
    if (aeronave) {
        [cite_start]// Calcular número de escalas [cite: 14]
        if (aeronave->getAutonomiaVoo() > 0) {
            numeroEscalas = static_cast<int>(distancia / aeronave->getAutonomiaVoo());
        } else {
            numeroEscalas = 0; // Se autonomia for 0, não há escalas (ou erro)
        }

        [cite_start]// Calcular tempo estimado de voo [cite: 15]
        if (aeronave->getVelocidadeMedia() > 0) {
            tempoEstimado = distancia / aeronave->getVelocidadeMedia();
        } else {
            tempoEstimado = 0.0; // Se velocidade for 0, tempo é indefinido (ou erro)
        }
        tempoEstimado += (numeroEscalas * 1.0); [cite_start]// Cada escala leva 1 hora [cite: 15]
    } else {
        numeroEscalas = 0;
        tempoEstimado = 0.0;
    }
}

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
    return ss.str();
}

Voo Voo::fromCSV(const string& linha) {
    // Esta função precisaria de um mecanismo para buscar Aeronaves e Pilotos existentes
    // pelo código/matrícula. Por simplicidade, este é um esqueleto.
    // A implementação completa dependeria da classe Sistema ou de um gerenciador de dados.
    stringstream ss(linha);
    string codigo, origem, destino, horaSaida, codAeronave, matComandante, matPrimeiroOficial, sDistancia;
    double distancia;

    getline(ss, codigo, ',');
    getline(ss, origem, ',');
    getline(ss, destino, ',');
    getline(ss, sDistancia, ',');
    distancia = stod(sDistancia);
    getline(ss, horaSaida, ',');
    getline(ss, codAeronave, ',');
    getline(ss, matComandante, ',');
    getline(ss, matPrimeiroOficial, ',');

    // No contexto real, você precisaria de uma forma de obter ponteiros para
    // Aeronave, Piloto e Passageiro a partir dos códigos/matrículas.
    // Isso geralmente é feito através de um "repositório" ou mapa na classe Sistema.
    Aeronave* a = nullptr; // Placeholder
    Piloto* c = nullptr;   // Placeholder
    Piloto* po = nullptr;  // Placeholder

    Voo v(codigo, origem, destino, distancia, horaSaida, a, c, po);
    v.calcularEscalasETempo(); // Garante que escalas e tempo sejam calculados ao carregar
    return v;
}

void Voo::listarPassageiros() const {
    cout << "Passageiros do Voo " << codigo << " (" << origem << " -> " << destino << "):" << endl;
    if (passageiros.empty()) {
        cout << "Nenhum passageiro embarcado neste voo." << endl;
    } else {
        for (const auto& p : passageiros) {
            cout << "- " << p->getNome() << " (CPF: " << p->getCPF() << ", Bilhete: " << p->getNumeroBilhete() << ")" << endl; // Adapte para os getters de Passageiro
        }
    }
}