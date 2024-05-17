// main.c
#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"

int main() {
    Cliente listaClientes[MAX_CLIENTES];
    Operacao listaOperacoes[MAX_OPERACOES];
    int quantidadeClientes = 0;
    int quantidadeOperacoes = 0;
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Novo cliente\n");
        printf("2. Apagar cliente\n");
        printf("3. Listar clientes\n");
        printf("4. Débito\n");
        printf("5. Depósito\n");
        printf("6. Extrato\n");
        printf("7. Transferência\n");
        printf("0. Sair\n");

        printf("Escolha uma opção: ");
        if(scanf("%d", &opcao) != 1){
            printf("Erro ao ler a opção.\n");
            return 1;
        }

switch (opcao) {
    case 1:
        novoCliente(listaClientes, &quantidadeClientes);
        break;
    case 2:
        apagaCliente(listaClientes, &quantidadeClientes);
        break;
    case 3:
        listarClientes(listaClientes, quantidadeClientes);
        break;
    case 4:
        debito(listaClientes, quantidadeClientes, listaOperacoes, &quantidadeOperacoes);
        break;
    case 5:
        deposito(listaClientes, quantidadeClientes, listaOperacoes, &quantidadeOperacoes);
        break;
    case 6:
        extrato(listaClientes, quantidadeClientes, listaOperacoes, quantidadeOperacoes);
        break;
    case 7:
        transferencia(listaClientes, quantidadeClientes, listaOperacoes, &quantidadeOperacoes);
        break;
    case 0:
        printf("Encerrando o programa...\n");
        break;
    default:
        printf("Opção inválida!\n");
}

} while (opcao != 0);

return 0;
}
