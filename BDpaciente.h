#ifndef BDPACIENTE_H
#define BDPACIENTE_H

#include "paciente.h"

typedef struct Node {
    Paciente paciente;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int tamanho;
    int ultimoId;
} BDPaciente;

BDPaciente* criarBD();
void liberarBD(BDPaciente *bd);
int carregarCSV(BDPaciente *bd, const char *filename);
int salvarCSV(BDPaciente *bd, const char *filename);

void inserirPaciente(BDPaciente *bd);
void listarPacientes(BDPaciente *bd);
void consultarPaciente(BDPaciente *bd);
void atualizarPaciente(BDPaciente *bd);
void removerPaciente(BDPaciente *bd);

#endif
