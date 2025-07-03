/* TRABALHO PRATICO - BCC 221 - PROGRAMAÇÃO ORIENTADA À OBJETOS (POO)
    SISTEMA DE CONTROLE DE VOO EM AEROPORTO
    Diogo Tadeu Campos - 24.1.4003
    Thiago Henrique de Oliveira Gonçalves - 24.1.4036
    Wendel Cauã Silva de Oliveira - 24.1.4021
*/

#include <iostream>
#include "include/sistema.h"
#include "include/utilidades.h" 
using namespace std;

int main() {
    Sistema meuSistema;
    meuSistema.carregarDados(); // Tenta carregar dados ao iniciar

    int opcao;
    do {
        exibirMenu();
        opcao = obterInt(""); // A função já faz a validação e limpeza de buffer

        switch (opcao) {
            case 1: 
                processarCadastrarAeronave(meuSistema); 
                break;
            case 2: 
                processarCadastrarPiloto(meuSistema); 
                break;
            case 3: 
                processarCadastrarPassageiro(meuSistema); 
                break;
            case 4: 
                processarCriarVoo(meuSistema); 
                break;
            case 5: 
                processarEmbarcarPassageiro(meuSistema); 
                break;
            case 6: 
                meuSistema.listarVoos(); 
                break;
            case 7: 
                processarListarPassageirosDoVoo(meuSistema); 
                break;
            case 8:
                processarRelatoriosEstatisticas(meuSistema);
                break;
            case 9:
                meuSistema.salvarDados();
                cout << "Dados salvos. Encerrando o sistema." << endl;
                break;
            default:
                cout << "Opção inválida. Tente novamente." << endl;
                break;
        }
    } while (opcao != 9);

    return 0;
}