#include <stdio.h>
#include <string.h>
#include "paciente.h"

void imprimirPaciente(const Paciente *p) {
    printf("%d %s %s %d %s\n", p->id, p->cpf, p->nome, p->idade, p->data_cadastro);
}

void formatarCPF(char *cpf) {
    char temp[CPF_SIZE];
    if (strlen(cpf) == 11) {
        snprintf(temp, CPF_SIZE, "%.3s.%.3s.%.3s-%.2s", cpf, cpf + 3, cpf + 6, cpf + 9);
        strcpy(cpf, temp);
    }
}
