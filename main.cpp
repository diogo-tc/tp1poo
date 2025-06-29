#include <iostream>
#include "Sistema.h"
#include "utilidades.h" 
using namespace std;

int main() {
    Sistema meuSistema;
    meuSistema.carregarDados(); // Tenta carregar dados ao iniciar

    int opcao;
    do {
        exibirMenu();
        opcao = obterInt(""); // A função já faz a validação e limpeza de buffer

        switch (opcao) {
            case 1: processarCadastrarAeronave(meuSistema); break;
            case 2: processarCadastrarPiloto(meuSistema); break;
            case 3: processarCadastrarPassageiro(meuSistema); break;
            case 4: processarCriarVoo(meuSistema); break;
            case 5: processarEmbarcarPassageiro(meuSistema); break;
            case 6: meuSistema.listarVoos(); break;
            case 7: processarListarPassageirosDoVoo(meuSistema); break;
            case 8:
                meuSistema.salvarDados();
                cout << "Dados salvos. Encerrando o sistema." << endl;
                break;
            default:
                cout << "Opção inválida. Tente novamente." << endl;
                break;
        }
    } while (opcao != 8);

    return 0;
}