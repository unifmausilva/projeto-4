#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "banco.h"

void salvarClientes(Cliente clientes[], int total_clientes) {
    FILE *arquivo;
    arquivo = fopen("clientes.dat", "wb");
    fwrite(clientes, sizeof(Cliente), total_clientes, arquivo);
    fclose(arquivo);
}

int carregarClientes(Cliente clientes[]) {
    FILE *arquivo;
    int total_clientes = 0;
    arquivo = fopen("clientes.dat", "rb");
    if (arquivo != NULL) {
        while (fread(&clientes[total_clientes], sizeof(Cliente), 1, arquivo) == 1) {
            total_clientes++;
        }
        fclose(arquivo);
    }
    return total_clientes;
}

void novoCliente(Cliente clientes[], int *total_clientes) {
    Cliente novo_cliente;
    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]", novo_cliente.nome);
    printf("Digite o CPF do cliente: ");
    scanf("%s", novo_cliente.cpf);
    printf("Digite o tipo de conta (comum ou plus): ");
    scanf("%s", novo_cliente.tipo_conta);
    printf("Digite o saldo inicial da conta: ");
    scanf("%f", &novo_cliente.saldo);
    printf("Digite a senha do cliente: ");
    scanf("%s", novo_cliente.senha);
    novo_cliente.saldo_negativo = strcmp(novo_cliente.tipo_conta, "comum") == 0 ? -1000.0 : -5000.0;
    novo_cliente.num_operacoes = 0;
    clientes[*total_clientes] = novo_cliente;
    (*total_clientes)++;
    salvarClientes(clientes, *total_clientes);
    printf("Cliente adicionado com sucesso!\n");
}

void apagarCliente(Cliente clientes[], int *total_clientes) {
    char cpf[12];
    printf("Digite o CPF do cliente que deseja apagar: ");
    scanf("%s", cpf);
    int i, encontrado = 0;
    for (i = 0; i < *total_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            encontrado = 1;
            break;
        }
    }
    if (encontrado) {
        for (; i < *total_clientes - 1; i++) {
            clientes[i] = clientes[i + 1];
        }
        (*total_clientes)--;
        salvarClientes(clientes, *total_clientes);
        printf("Cliente apagado com sucesso!\n");
    } else {
        printf("Cliente não encontrado.\n");
    }
}

void listarClientes(Cliente clientes[], int total_clientes) {
    printf("Lista de Clientes:\n");
    for (int i = 0; i < total_clientes; i++) {
        printf("Nome: %s, CPF: %s\n", clientes[i].nome, clientes[i].cpf);
    }
}

void debito(Cliente clientes[], int total_clientes) {
    // Implementar função de débito
}

void deposito(Cliente clientes[], int total_clientes) {
    // Implementar função de depósito
}

void extrato(Cliente clientes[], int total_clientes) {
    // Implementar função de extrato
}

void transferencia(Cliente clientes[], int total_clientes) {
    // Implementar função de transferência
}
