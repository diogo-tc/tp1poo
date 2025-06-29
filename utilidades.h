#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>
#include "Sistema.h" 
using namespace std; 

// Funções auxiliares para entrada de dados
void limparBuffer();
string obterString(const string& prompt);
int obterInt(const string& prompt);
double obterDouble(const string& prompt);

// Função para exibir o menu
void exibirMenu();

// Funções para processar as opções do menu
void processarCadastrarAeronave(Sistema& meuSistema);
void processarCadastrarPiloto(Sistema& meuSistema);
void processarCadastrarPassageiro(Sistema& meuSistema);
void processarCriarVoo(Sistema& meuSistema);
void processarEmbarcarPassageiro(Sistema& meuSistema);
void processarListarPassageirosDoVoo(Sistema& meuSistema);

#endif // UTILIDADES_H