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

    if (strcmp(novo_cliente.tipo_conta, "comum") == 0) {
        novo_cliente.saldo_negativo = -1000.0;
    } else if (strcmp(novo_cliente.tipo_conta, "plus") == 0) {
        novo_cliente.saldo_negativo = -5000.0;
    } else {
        printf("Tipo de conta inválido!\n");
        return;
    }

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
    char cpf[12];
    char senha[20];
    float valor;

    printf("Digite o CPF do cliente: ");
    scanf("%s", cpf);
    printf("Digite a senha: ");
    scanf("%s", senha);
    printf("Digite o valor a ser debitado: ");
    scanf("%f", &valor);

    int cliente_encontrado = 0;
    for (int i = 0; i < total_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0 && strcmp(clientes[i].senha, senha) == 0) {
            cliente_encontrado = 1;
            if (clientes[i].saldo - valor >= clientes[i].saldo_negativo) {
                clientes[i].saldo -= valor;
                printf("Débito realizado com sucesso. Novo saldo: %.2f\n", clientes[i].saldo);
            } else {
                printf("Saldo insuficiente para realizar o débito.\n");
            }
            break;
        }
    }
    if (!cliente_encontrado) {
        printf("CPF ou senha incorretos.\n");
    }
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
