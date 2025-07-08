# Trabalho de estrutura de dados- Parte 2
- **Heloísa Borghardt Hand**
- **Isabeli Rocha de Rezende**

## Sistema de Gerenciamento de Pacientes – Estrutura de Dados em C

Este projeto é a segunda parte do trabalho de Estrutura de Dados que consiste em um sistema simples para gerenciamento de pacientes de uma clínica, feito em linguagem C. Ele utiliza uma lista encadeada como estrutura principal (TAD) e armazena os dados de forma persistente em um arquivo CSV. O sistema permite inserir, consultar, atualizar, remover e listar pacientes.

---

## Estrutura do Repositório


Projeto:
- bdpaciente.c          :Implementação do TAD da lista encadeada
- bdpaciente.h          :Cabeçalho do TAD
- paciente.h            :Definição da struct Paciente
- main.c                :Menu e interação com o usuário
- bd_paciente.csv       :Banco de dados em formato CSV
- Makefile              :Compilação automática do projeto


---

## Principais TADs

- *Paciente:* representa cada paciente com campos como ID, CPF, nome, idade e data de cadastro.
- *Node:* representa o nó da lista encadeada contendo um Paciente.
- *BDPaciente:* estrutura que guarda a cabeça da lista, o tamanho total e o último ID gerado. Essa estrutura abstrai toda a manipulação do banco de dados em memória.

---

## Como compilar e executar o sistema

### Pré-requisitos
- Sistema Linux com GCC instalado.

### Passo-a-passo
1. Clone o repositório:
   bash
   git clone <link-do-repo>
   cd projeto
   
2. Compile com make:
   bash
   make
   
3. Execute o programa:
   bash
   ./sistema
   
4. Para limpar os arquivos .o e o executável:
   bash
   make clean
   

---

## Decisões de implementação

- *Modularização:* Dividimos o código em 4 arquivos principais para organizar as responsabilidades.
- *ID automático:* O ID do paciente é gerado com base no maior ID já presente no CSV.
- *Busca por prefixo:* A consulta permite buscar por parte do nome ou CPF, retornando todos os correspondentes.
- *Formatação do CPF:* O CPF inserido é formatado automaticamente para facilitar a leitura.
- *Confirmações:* Para ações críticas como inserção, remoção e atualização, o sistema pede confirmação ao usuário.
- *Persistência:* Os dados são sempre carregados do arquivo bd_paciente.csv na inicialização e salvos na finalização do programa.

---

## Funcionalidades disponíveis

Inserir paciente  
Consultar paciente (por nome ou CPF – com prefixo)  
Atualizar registro existente  
Remover paciente com confirmação  
Listar todos os pacientes de forma organizada  

---

## Comentários e Manutenção

As funções e estruturas estão comentadas para facilitar futuras modificações. Qualquer melhoria como paginação, validações de dados mais rígidas ou ordenação da listagem pode ser adicionada sem alterar muito a estrutura principal.

---
