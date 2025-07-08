#ifndef PACIENTE_H
#define PACIENTE_H

#define CPF_SIZE 15
#define NOME_SIZE 100
#define DATA_SIZE 11

typedef struct {
    int id;
    char cpf[CPF_SIZE];
    char nome[NOME_SIZE];
    int idade;
    char data_cadastro[DATA_SIZE];
} Paciente;

void imprimirPaciente(const Paciente *p);
void formatarCPF(char *cpf);

#endif
