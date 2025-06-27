#include "Voo.h"
#include <sstream>     // Para std::stringstream
#include <iostream>    // Para std::cout, std::endl

// Construtor padrão
Voo::Voo() : distancia(0.0), aeronave(nullptr), comandante(nullptr), primeiroOficial(nullptr), numeroEscalas(0), tempoEstimado(0.0) {}

// Construtor com parâmetros
Voo::Voo(const std::string& codigo, const std::string& origem, const std::string& destino, double distancia, const std::string& horaSaida,
         Aeronave* aeronave, Piloto* comandante, Piloto* primeiroOficial)
    : codigo(codigo), origem(origem), destino(destino), distancia(distancia), horaSaida(horaSaida),
      aeronave(aeronave), comandante(comandante), primeiroOficial(primeiroOficial) {
    calcularEscalasETempo();
}

// Getters e Setters
std::string Voo::getCodigo() const {
    return codigo;
}

void Voo::setCodigo(const std::string& codigo) {
    this->codigo = codigo;
}

std::string Voo::getOrigem() const {
    return origem;
}

void Voo::setOrigem(const std::string& origem) {
    this->origem = origem;
}

std::string Voo::getDestino() const {
    return destino;
}

void Voo::setDestino(const std::string& destino) {
    this->destino = destino;
}

double Voo::getDistancia() const {
    return distancia;
}

void Voo::setDistancia(double distancia) {
    this->distancia = distancia;
    calcularEscalasETempo(); // Recalcular ao mudar a distância
}

std::string Voo::getHoraSaida() const {
    return horaSaida;
}

void Voo::setHoraSaida(const std::string& hora) {
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

const std::vector<Passageiro*>& Voo::getPassageiros() const {
    return passageiros;
}

bool Voo::adicionarPassageiro(Passageiro* passageiro) {
    // Verificar se a aeronave tem capacidade para mais passageiros [: 16]
    if (aeronave && passageiros.size() < aeronave->getCapacidade()) {
        passageiros.push_back(passageiro);
        return true;
    }
    return false;
}

void Voo::calcularEscalasETempo() {
    if (aeronave) {
        // Calcular número de escalas com base na distância do voo e na autonomia da Aeronave [: 14]
        if (aeronave->getAutonomia() > 0) { // Alterado para getAutonomia()
            numeroEscalas = static_cast<int>(distancia / aeronave->getAutonomia());
        } else {
            numeroEscalas = 0;
        }

        // Calcular tempo estimado de voo com base na distância e na velocidade da Aeronave [: 15]
        if (aeronave->getVelocidadeMedia() > 0) {
            tempoEstimado = distancia / aeronave->getVelocidadeMedia();
        } else {
            tempoEstimado = 0.0;
        }
        tempoEstimado += (numeroEscalas * 1.0); // cada escala leva 1 hora [: 15]
    } else {
        numeroEscalas = 0;
        tempoEstimado = 0.0;
    }
}

std::string Voo::toCSV() const {
    std::stringstream ss;
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

Voo Voo::fromCSV(const std::string& linha) {
    // Esta função precisaria de um mecanismo para buscar Aeronaves e Pilotos existentes
    // pelo código/matrícula. Por simplicidade, este é um esqueleto.
    // A implementação completa dependeria da classe Sistema ou de um gerenciador de dados.
    std::stringstream ss(linha);
    std::string codigo, origem, destino, horaSaida, sDistancia;
    std::string codAeronave, matComandante, matPrimeiroOficial;
    double distancia;

    std::getline(ss, codigo, ',');
    std::getline(ss, origem, ',');
    std::getline(ss, destino, ',');
    std::getline(ss, sDistancia, ',');
    distancia = std::stod(sDistancia);
    std::getline(ss, horaSaida, ',');
    std::getline(ss, codAeronave, ',');
    std::getline(ss, matComandante, ',');
    std::getline(ss, matPrimeiroOficial); // Lê até o final da linha

    // No contexto real, você precisaria de uma forma de obter ponteiros para
    // Aeronave, Piloto e Passageiro a partir dos códigos/matrículas.
    // Isso é feito na classe Sistema. Para o fromCSV de Voo, estamos criando
    // um Voo "vazio" no que diz respeito aos ponteiros reais,
    // e o Sistema os preencherá.
    Aeronave* a = nullptr; // Placeholder
    Piloto* c = nullptr;   // Placeholder
    Piloto* po = nullptr;  // Placeholder

    Voo v(codigo, origem, destino, distancia, horaSaida, a, c, po);
    v.calcularEscalasETempo(); // Garante que escalas e tempo sejam calculados ao carregar
    return v;
}

void Voo::listarPassageiros() const {
    std::cout << "Passageiros do Voo " << codigo << " (" << origem << " -> " << destino << "):" << std::endl;
    if (aeronave) {
        std::cout << "Aeronave: " << aeronave->getCodigo() << " (" << aeronave->getModelo() << ")" << std::endl; // [: 17]
    } else {
        std::cout << "Aeronave: N/A" << std::endl;
    }

    if (passageiros.empty()) {
        std::cout << "Nenhum passageiro embarcado neste voo." << std::endl;
    } else {
        for (const auto& p : passageiros) {
            // Ao informar o código do voo, exibir o código e o modelo da aeronave, o nome de cada passageiro no voo. [: 17]
            std::cout << "- " << p->getNome() << " (CPF: " << p->getCPF() << ", Bilhete: " << p->getBilhete() << ")" << std::endl; // Corrigido para getBilhete()
        }
    }
}