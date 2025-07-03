#include "include/voo.h"
#include <sstream>
#include <iostream>
#include <stdexcept> // Para stod
using namespace std;  

// Construtor padrão
Voo::Voo() : distancia(0.0), numeroEscalas(0), tempoEstimado(0.0) {}

// Construtor com parâmetros - agora recebe IDs como strings
Voo::Voo(const string& codigo, const string& origem, const string& destino, double distancia, const string& horaSaida,
         const string& codigoAeronave, const string& matriculaComandante, const string& matriculaPrimeiroOficial)
    : codigo(codigo), origem(origem), destino(destino), distancia(distancia), horaSaida(horaSaida),
      codigoAeronave(codigoAeronave), matriculaComandante(matriculaComandante), matriculaPrimeiroOficial(matriculaPrimeiroOficial),
      numeroEscalas(0), tempoEstimado(0.0) {
    // Note: calcularEscalasETempo não pode ser chamado aqui sem os dados da Aeronave
    // O Sistema terá que chamar isso após resolver a Aeronave
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
    // Recalcular ao mudar a distância, mas precisa de dados da aeronave via Sistema
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

// Novos getters para os IDs armazenados
const string& Voo::getCodigoAeronave() const {
    return codigoAeronave;
}

const string& Voo::getMatriculaComandante() const {
    return matriculaComandante;
}

const string& Voo::getMatriculaPrimeiroOficial() const {
    return matriculaPrimeiroOficial;
}

const vector<string>& Voo::getCpfsPassageiros() const {
    return cpfsPassageiros;
}

// Método adicionarPassageiro agora recebe apenas o CPF e a capacidade da aeronave
bool Voo::adicionarPassageiro(const string& cpfPassageiro, int capacidadeAeronave) {
    // Verificar se a aeronave tem capacidade para mais passageiros
    if (cpfsPassageiros.size() < static_cast<size_t>(capacidadeAeronave)) {
        // Verificar se o passageiro já está no voo
        for (const auto& cpf : cpfsPassageiros) {
            if (cpf == cpfPassageiro) {
                // cout << "Passageiro com CPF " << cpfPassageiro << " já está neste voo." << endl;
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
string Voo::toCSV() const {
    stringstream ss;
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
Voo Voo::fromCSV(const string& linha) {
    stringstream ss(linha);
    string codigo, origem, destino, horaSaida, sDistancia;
    string codAeronave, matComandante, matPrimeiroOficial, cpfsPassageirosStr;
    double distancia;

    getline(ss, codigo, ',');
    getline(ss, origem, ',');
    getline(ss, destino, ',');
    getline(ss, sDistancia, ',');
    distancia = stod(sDistancia);
    getline(ss, horaSaida, ',');
    getline(ss, codAeronave, ',');
    getline(ss, matComandante, ',');
    // A última leitura deve pegar todo o resto da linha, incluindo os CPFs (se houver)
    getline(ss, matPrimeiroOficial, ','); // Lê a matrícula do Primeiro Oficial
    getline(ss, cpfsPassageirosStr); // Lê o restante da linha, que são os CPFs

    // Cria o objeto Voo com os IDs. A lista de passageiros (cpfsPassageiros)
    // e o tempo/escalas serão preenchidos em Sistema::carregarDados().
    Voo v(codigo, origem, destino, distancia, horaSaida, codAeronave, matComandante, matPrimeiroOficial);

    // Preenche a lista de CPFs do voo durante o fromCSV (temporariamente, para o Sistema usar)
    if (!cpfsPassageirosStr.empty()) {
        stringstream ssCpfs(cpfsPassageirosStr);
        string cpfIndividual;
        while (getline(ssCpfs, cpfIndividual, ';')) {
            v.cpfsPassageiros.push_back(cpfIndividual); // Adiciona o CPF à lista interna do Voo
        }
    }

    return v;
}