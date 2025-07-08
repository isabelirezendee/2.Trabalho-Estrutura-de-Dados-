#include <stdio.h>
#include "bdpaciente.h"

int main() {
    BDPaciente *bd = criarBD();
    carregarCSV(bd, "bd_paciente.csv");

    int opcao;
    do {
        printf("\n1 - Inserir\n2 - Listar\n3 - Consultar\n4 - Atualizar\n5 - Remover\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirPaciente(bd);
                salvarCSV(bd, "bd_paciente.csv");
                break;
            case 2:
                listarPacientes(bd);
                break;
            case 3:
                consultarPaciente(bd);
                break;
            case 4:
                atualizarPaciente(bd);
                salvarCSV(bd, "bd_paciente.csv");
                break;
            case 5:
                removerPaciente(bd);
                salvarCSV(bd, "bd_paciente.csv");
                break;
        }
    } while (opcao != 0);

    salvarCSV(bd, "bd_paciente.csv");
    liberarBD(bd);
    return 0;
}
