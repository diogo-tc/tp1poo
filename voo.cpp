#include "Voo.h"
#include <sstream>
#include <iostream>
#include <stdexcept> // Para std::stod

// Construtor padrão
Voo::Voo() : distancia(0.0), numeroEscalas(0), tempoEstimado(0.0) {}

// Construtor com parâmetros - agora recebe IDs como strings
Voo::Voo(const std::string& codigo, const std::string& origem, const std::string& destino, double distancia, const std::string& horaSaida,
         const std::string& codigoAeronave, const std::string& matriculaComandante, const std::string& matriculaPrimeiroOficial)
    : codigo(codigo), origem(origem), destino(destino), distancia(distancia), horaSaida(horaSaida),
      codigoAeronave(codigoAeronave), matriculaComandante(matriculaComandante), matriculaPrimeiroOficial(matriculaPrimeiroOficial),
      numeroEscalas(0), tempoEstimado(0.0) {
    // Note: calcularEscalasETempo não pode ser chamado aqui sem os dados da Aeronave
    // O Sistema terá que chamar isso após resolver a Aeronave
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
    // Recalcular ao mudar a distância, mas precisa de dados da aeronave via Sistema
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

// Novos getters para os IDs armazenados
const std::string& Voo::getCodigoAeronave() const {
    return codigoAeronave;
}

const std::string& Voo::getMatriculaComandante() const {
    return matriculaComandante;
}

const std::string& Voo::getMatriculaPrimeiroOficial() const {
    return matriculaPrimeiroOficial;
}

const std::vector<std::string>& Voo::getCpfsPassageiros() const {
    return cpfsPassageiros;
}

// Método adicionarPassageiro agora recebe apenas o CPF e a capacidade da aeronave
bool Voo::adicionarPassageiro(const std::string& cpfPassageiro, int capacidadeAeronave) {
    // Verificar se a aeronave tem capacidade para mais passageiros
    if (cpfsPassageiros.size() < static_cast<size_t>(capacidadeAeronave)) {
        // Verificar se o passageiro já está no voo
        for (const auto& cpf : cpfsPassageiros) {
            if (cpf == cpfPassageiro) {
                // std::cout << "Passageiro com CPF " << cpfPassageiro << " já está neste voo." << std::endl;
                return false; // Passageiro já está na lista
            }
        }
        cpfsPassageiros.push_back(cpfPassageiro);
        return true;
    }
    return false; // Capacidade máxima atingida
}

// Lógica de cálculo de tempo e escalas, agora com parâmetros da aeronave
void Voo::calcularEscalasETempo(double autonomiaAeronave, double velocidadeMediaAeronave) {
    // Calcular número de escalas com base na distância do voo e na autonomia da Aeronave
    if (autonomiaAeronave > 0) {
        numeroEscalas = static_cast<int>(distancia / autonomiaAeronave);
    } else {
        numeroEscalas = 0;
    }

    // Calcular tempo estimado de voo com base na distância e na velocidade da Aeronave
    if (velocidadeMediaAeronave > 0) {
        tempoEstimado = distancia / velocidadeMediaAeronave;
    } else {
        tempoEstimado = 0.0;
    }
    tempoEstimado += (numeroEscalas * 1.0); // cada escala leva 1 hora
}

// toCSV: Agora serializa IDs para aeronave e pilotos, e CPFs para passageiros
std::string Voo::toCSV() const {
    std::stringstream ss;
    ss << codigo << ","
       << origem << ","
       << destino << ","
       << distancia << ","
       << horaSaida << ","
       << codigoAeronave << "," // ID da Aeronave
       << matriculaComandante << "," // ID do Comandante
       << matriculaPrimeiroOficial; // ID do Primeiro Oficial

    // Adicionar CPFs dos passageiros, separados por ponto e vírgula
    ss << ","; // Separador para a lista de passageiros (pode ser vazio se não houver passageiros)
    for (size_t i = 0; i < cpfsPassageiros.size(); ++i) {
        ss << cpfsPassageiros[i];
        if (i < cpfsPassageiros.size() - 1) {
            ss << ";"; // Usar ponto e vírgula como delimitador entre CPFs
        }
    }
    return ss.str();
}

// fromCSV: Apenas extrai as strings da linha CSV. A resolução para objetos reais será no Sistema.
Voo Voo::fromCSV(const std::string& linha) {
    std::stringstream ss(linha);
    std::string codigo, origem, destino, horaSaida, sDistancia;
    std::string codAeronave, matComandante, matPrimeiroOficial, cpfsPassageirosStr;
    double distancia;

    std::getline(ss, codigo, ',');
    std::getline(ss, origem, ',');
    std::getline(ss, destino, ',');
    std::getline(ss, sDistancia, ',');
    distancia = std::stod(sDistancia);
    std::getline(ss, horaSaida, ',');
    std::getline(ss, codAeronave, ',');
    std::getline(ss, matComandante, ',');
    // A última leitura deve pegar todo o resto da linha, incluindo os CPFs (se houver)
    std::getline(ss, matPrimeiroOficial, ','); // Lê a matrícula do Primeiro Oficial
    std::getline(ss, cpfsPassageirosStr); // Lê o restante da linha, que são os CPFs

    // Cria o objeto Voo com os IDs. A lista de passageiros (cpfsPassageiros)
    // e o tempo/escalas serão preenchidos em Sistema::carregarDados().
    Voo v(codigo, origem, destino, distancia, horaSaida, codAeronave, matComandante, matPrimeiroOficial);

    // Preenche a lista de CPFs do voo durante o fromCSV (temporariamente, para o Sistema usar)
    if (!cpfsPassageirosStr.empty()) {
        std::stringstream ssCpfs(cpfsPassageirosStr);
        std::string cpfIndividual;
        while (std::getline(ssCpfs, cpfIndividual, ';')) {
            v.cpfsPassageiros.push_back(cpfIndividual); // Adiciona o CPF à lista interna do Voo
        }
    }

    return v;
}