//   gcc *.c & ./a.out
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "banco.h"

int encontrarCliente(Cliente clientes[], int total_clientes, char cpf[]) {
    for (int i = 0; i < total_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            return i;
        }
    }
    return -1; 
}

int main() {
    Cliente clientes[MAX_CLIENTES];
    int total_clientes = carregarClientes(clientes);


    int opcao;
    char cpf[12];
    int indice_cliente;
    printf("aaa%d\n",total_clientes);
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

        if (scanf("%d", &opcao) != 1) {
            printf("Erro\n");
            continue;
        }

        switch (opcao) {
            case 1:
                novoCliente(clientes, &total_clientes);
                break;
            case 2:
                apagarCliente(clientes, &total_clientes);
                break;
            case 3: 
                printf("%d\n",total_clientes);
                listarClientes(clientes, total_clientes);
                break;
            case 4:
                printf("Digite o CPF do cliente para fazer o debito: ");
                if (scanf("%s", cpf) != 1) {
                    printf("CPF inválido\n");
                    continue;
                }
                indice_cliente = encontrarCliente(clientes, total_clientes, cpf);
                if (indice_cliente != -1) {
                    debito(clientes, total_clientes);
                } else {
                    printf("Cliente não encontrado.\n");
                }
                break;
            case 5:
                printf("Digite o CPF do cliente para fazer o deposito: ");
                if (scanf("%s", cpf) != 1) {
                    printf("CPF inválido.\n");
                    continue;
                }
                indice_cliente = encontrarCliente(clientes, total_clientes, cpf);
                if (indice_cliente != -1) {
                    deposito(clientes, total_clientes);
                } else {
                    printf("Cliente não encontrado.\n");
                }
                break;
            case 6:
                    extrato(clientes, total_clientes); 
                break;
            case 7:
                transferencia(clientes, total_clientes);
                break;
            case 0:
                salvarClientes(clientes, total_clientes);
                printf("Saindo\n");
                break;
            default:
                printf("Opção invalida\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
