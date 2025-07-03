# Sistema de Controle de Voos

Este projeto é um sistema de controle de voos desenvolvido em C++ para gerenciar aeronaves, pilotos, passageiros e voos.

## Estrutura do Projeto

- `main.cpp` — Arquivo principal do sistema.
- `sistema.cpp`, `sistema.h` — Implementação da lógica principal do sistema.
- `aeronave.cpp`, `aeronave.h` — Gerenciamento de aeronaves.
- `pessoa.cpp`, `pessoa.h` — Gerenciamento de pilotos e passageiros.
- `voo.cpp`, `voo.h` — Gerenciamento de voos.
- `utilidades.cpp`, `utilidades.h` — Funções auxiliares e de interface.
- Arquivos `.csv` — Persistência dos dados.

## Compilação

Para compilar o projeto, utilize um compilador C++ (exemplo: g++). Execute o comando abaixo no terminal, dentro da pasta do projeto:

$ g++ main.cpp sistema.cpp voo.cpp pessoa.cpp aeronave.cpp utilidades.cpp -o gerenciador_de_voos

Execução:

Após compilar, execute o sistema com: ./gerenciador _de_voos

ou no Windows: gerenciador _de_voos.exe

Funcionamento:

O sistema apresenta um menu interativo com as seguintes opções:

1. Cadastrar aeronave
2. Cadastrar piloto
3. Cadastrar passageiro
4. Criar voo
5. Embarcar passageiro em voo
6. Listar voos
7. Listar passageiros de um voo
8. Relatórios e Estatísticas
9. Salvar dados e sair

Os dados são salvos automaticamente nos arquivos .csv correspondentes.

Relatórios e Estatísticas: 
Informa diferentes tipos de relatórios com a possibilidade de salva-los em um arquivo .txt
Menu interativo:

1. Número total de voos cadastrados
2. Média de passageiros por voo
3. Lista de aeronaves mais utilizadas
4. Passageiros que participaram de mais de um voo
5. Voos que atingiram pelo menos 90% da capacidade máxima
6. Distância total percorrida por cada aeronave
7. Voltar ao menu principal


Observações:

O arquivo voos.csv não deve ser importado manualmente, pois depende da união dos dados contidos nos arquivos pessoas.csv e aeronaves.csv. Portanto, ele deve ser gerado dinamicamente durante a execução do programa.

Certifique-se de que os arquivos aeronaves.csv, pessoas.csv e voos.csv estejam na mesma pasta do executável para persistência dos dados.
O sistema carrega os dados automaticamente ao iniciar, se os arquivos existirem. 
