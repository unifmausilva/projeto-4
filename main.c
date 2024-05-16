#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"

int main() {
    int opcao;

    do {
        printf("\nMenu de opções:\n");
        printf("1. Novo cliente\n");
        printf("2. Apaga cliente\n");
        printf("3. Listar clientes\n");
        printf("4. Débito\n");
        printf("5. Depósito\n");
        printf("6. Extrato\n");
        printf("7. Transferência Entre Contas\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                novoCliente();
                break;
            case 2:
                apagaCliente();
                break;
            case 3:
                listarClientes();
                break;
            case 4:
                debito();
                break;
            case 5:
                deposito();
                break;
            case 6:
                extrato();
                break;
            case 7:
                transferencia();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 0);

    return 0;
}
