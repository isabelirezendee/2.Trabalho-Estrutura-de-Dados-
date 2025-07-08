#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bdpaciente.h"
#include "util.h"

BDPaciente* criarBD() {
    BDPaciente *bd = malloc(sizeof(BDPaciente));
    bd->head = NULL;
    bd->tamanho = 0;
    bd->ultimoId = 0;
    return bd;
}

void liberarBD(BDPaciente *bd) {
    Node *atual = bd->head;
    while (atual) {
        Node *temp = atual;
        atual = atual->next;
        free(temp);
    }
    free(bd);
}

int carregarCSV(BDPaciente *bd, const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return 0;

    char linha[256];
    fgets(linha, sizeof(linha), f); // pula cabeçalho

    while (fgets(linha, sizeof(linha), f)) {
        Paciente p;
        sscanf(linha, "%d,%14[^,],%99[^,],%d,%10[^\n]",
               &p.id, p.cpf, p.nome, &p.idade, p.data_cadastro);
        Node *novo = malloc(sizeof(Node));
        novo->paciente = p;
        novo->next = bd->head;
        bd->head = novo;
        if (p.id > bd->ultimoId) bd->ultimoId = p.id;
        bd->tamanho++;
    }

    fclose(f);
    return 1;
}

int salvarCSV(BDPaciente *bd, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) return 0;

    fprintf(f, "ID,CPF,Nome,Idade,Data_Cadastro\n");
    Node *atual = bd->head;
    while (atual) {
        Paciente *p = &atual->paciente;
        fprintf(f, "%d,%s,%s,%d,%s\n", p->id, p->cpf, p->nome, p->idade, p->data_cadastro);
        atual = atual->next;
    }

    fclose(f);
    return 1;
}

void listarPacientes(BDPaciente *bd) {
    printf("ID CPF Nome Idade Data_Cadastro\n");
    Node *atual = bd->head;
    while (atual) {
        imprimirPaciente(&atual->paciente);
        atual = atual->next;
    }
}

void inserirPaciente(BDPaciente *bd) {
    Paciente p;
    printf("CPF (somente números): ");
    scanf("%s", p.cpf);
    formatarCPF(p.cpf);

    printf("Nome: ");
    getchar(); // limpa o buffer
    fgets(p.nome, NOME_SIZE, stdin);
    p.nome[strcspn(p.nome, "\n")] = 0;

    printf("Idade: ");
    scanf("%d", &p.idade);

    printf("Data de cadastro (AAAA-MM-DD): ");
    scanf("%s", p.data_cadastro);

    p.id = ++bd->ultimoId;

    printf("\nConfirma inserção? (S/N)\n");
    imprimirPaciente(&p);
    char confirm;
    scanf(" %c", &confirm);

    if (toupper(confirm) == 'S') {
        Node *novo = malloc(sizeof(Node));
        novo->paciente = p;
        novo->next = bd->head;
        bd->head = novo;
        bd->tamanho++;
        printf("Paciente inserido com sucesso!\n");
    } else {
        bd->ultimoId--; // desfaz ID
        printf("Inserção cancelada.\n");
    }
}

void consultarPaciente(BDPaciente *bd) {
    int modo;
    char busca[100];

    printf("1 - Por nome\n2 - Por CPF\n3 - Voltar\nEscolha: ");
    scanf("%d", &modo);
    if (modo == 3) return;

    printf("Digite o prefixo: ");
    getchar(); // limpar buffer
    fgets(busca, 100, stdin);
    busca[strcspn(busca, "\n")] = 0;

    Node *atual = bd->head;
    int encontrados = 0;

    printf("ID CPF Nome Idade Data_Cadastro\n");
    while (atual) {
        if ((modo == 1 && strncmp(atual->paciente.nome, busca, strlen(busca)) == 0) ||
            (modo == 2 && strncmp(atual->paciente.cpf, busca, strlen(busca)) == 0)) {
            imprimirPaciente(&atual->paciente);
            encontrados++;
        }
        atual = atual->next;
    }

    if (!encontrados)
        printf("Nenhum paciente encontrado.\n");
}

void atualizarPaciente(BDPaciente *bd) {
    listarPacientes(bd);
    printf("Digite o ID do paciente a atualizar: ");
    int id;
    scanf("%d", &id);

    Node *atual = bd->head;
    while (atual && atual->paciente.id != id)
        atual = atual->next;

    if (!atual) {
        printf("Paciente não encontrado.\n");
        return;
    }

    Paciente *p = &atual->paciente;
    char novoCPF[CPF_SIZE], novoNome[NOME_SIZE], novaData[DATA_SIZE];
    // int novaIdade;

    printf("Digite novos dados (ou '-' para manter):\n");

    printf("CPF: ");
    scanf("%s", novoCPF);
    if (strcmp(novoCPF, "-") != 0) {
        formatarCPF(novoCPF);
        strcpy(p->cpf, novoCPF);
    }

    printf("Nome: ");
    getchar();
    fgets(novoNome, NOME_SIZE, stdin);
    novoNome[strcspn(novoNome, "\n")] = 0;
    if (strcmp(novoNome, "-") != 0)
        strcpy(p->nome, novoNome);

    printf("Idade: ");
    scanf("%s", novoCPF);  // reutilizando
    if (strcmp(novoCPF, "-") != 0)
        p->idade = atoi(novoCPF);

    printf("Data de cadastro: ");
    scanf("%s", novaData);
    if (strcmp(novaData, "-") != 0)
        strcpy(p->data_cadastro, novaData);

    printf("Confirma atualização? (S/N)\n");
    imprimirPaciente(p);
    char conf;
    scanf(" %c", &conf);
    if (toupper(conf) == 'S') {
        printf("Atualização realizada.\n");
    } else {
        printf("Atualização cancelada.\n");
    }
}

void removerPaciente(BDPaciente *bd) {
    listarPacientes(bd);
    printf("Digite o ID do paciente a remover: ");
    int id;
    scanf("%d", &id);

    Node *atual = bd->head, *anterior = NULL;

    while (atual && atual->paciente.id != id) {
        anterior = atual;
        atual = atual->next;
    }

    if (!atual) {
        printf("Paciente não encontrado.\n");
        return;
    }

    printf("Confirma exclusão? (S/N)\n");
    imprimirPaciente(&atual->paciente);
    char conf;
    scanf(" %c", &conf);

    if (toupper(conf) == 'S') {
        if (!anterior)
            bd->head = atual->next;
        else
            anterior->next = atual->next;

        free(atual);
        bd->tamanho--;
        printf("Paciente removido.\n");
    } else {
        printf("Remoção cancelada.\n");
    }
}
