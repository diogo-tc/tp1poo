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

Cadastrar aeronave
Cadastrar piloto
Cadastrar passageiro
Criar voo
Embarcar passageiro em voo
Listar voos
Listar passageiros de um voo
Salvar dados e sair
Os dados são salvos automaticamente nos arquivos .csv correspondentes.

Observações:

Certifique-se de que os arquivos aeronaves.csv, pessoas.csv e voos.csv estejam na mesma pasta do executável para persistência dos dados.
O sistema carrega os dados automaticamente ao iniciar, se os arquivos existirem.
