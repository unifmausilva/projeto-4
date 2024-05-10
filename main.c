#include <stdio.h>
#include <stdlib.h>
#include "banco.h"

int main() {
    Cliente clientes[MAX_CLIENTES];
    int total_clientes = carregarClientes(clientes);

    int opcao;
    do {
        printf("\nMenu de Opcoes:\n");
        printf("1. Novo cliente\n");
        printf("2. Apagar cliente\n");
        printf("3. Listar clientes\n");
        printf("4. Débito\n");
        printf("5. Depósito\n");
        printf("6. Extrato\n");
        printf("7. Transferência Entre Contas\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                novoCliente(clientes, &total_clientes);
                break;
            case 2:
                apagarCliente(clientes, &total_clientes);
                break;
            case 3:
                listarClientes(clientes, total_clientes);
                break;
            case 4:
                debito(clientes, total_clientes);
                break;
            case 5:
                deposito(clientes, total_clientes);
                break;
            case 6:
                extrato(clientes, total_clientes);
                break;
            case 7:
                transferencia(clientes, total_clientes);
                break;
            case 0:
                printf("Saindo\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
