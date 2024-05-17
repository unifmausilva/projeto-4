#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "banco.h"

int encontrarClientePorCPF(Cliente clientes[], int total_clientes, char cpf[]) {
    for (int i = 0; i < total_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            return i;
        }
    }
    return -1; // Cliente não encontrado
}

int main() {
    Cliente clientes[MAX_CLIENTES];
    int total_clientes = carregarClientes(clientes);

    int opcao;
    char cpf[12];
    int indice_cliente;

    do {
        printf("\nMenu de Opcoes:\n");
        printf("1. Novo cliente\n");
        printf("2. Apagar cliente\n");
        printf("3. Listar clientes\n");
        printf("4. Debito\n");
        printf("5. Deposito\n");
        printf("6. Extrato\n");
        printf("7. Transferencia Entre Contas\n");
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
                printf("Digite o CPF do cliente para debito: ");
                scanf("%s", cpf);
                indice_cliente = encontrarClientePorCPF(clientes, total_clientes, cpf);
                if (indice_cliente != -1) {
                    debito(&clientes[indice_cliente]);
                } else {
                    printf("Cliente não encontrado.\n");
                }
                break;
            case 5:
                printf("Digite o CPF do cliente para deposito: ");
                scanf("%s", cpf);
                indice_cliente = encontrarClientePorCPF(clientes, total_clientes, cpf);
                if (indice_cliente != -1) {
                    deposito(&clientes[indice_cliente]);
                } else {
                    printf("Cliente não encontrado.\n");
                }
                break;
            case 6:
                printf("Digite o CPF do cliente para extrato: ");
                scanf("%s", cpf);
                indice_cliente = encontrarClientePorCPF(clientes, total_clientes, cpf);
                if (indice_cliente != -1) {
                    extrato(&clientes[indice_cliente]);
                } else {
                    printf("Cliente não encontrado.\n");
                }
                break;
            case 7:
                transferencia(clientes, total_clientes);
                break;
            case 0:
                salvarClientes(clientes, total_clientes);
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
