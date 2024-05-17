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
    novo_cliente.total_operacoes = 0;  // Inicializando total_operacoes
    clientes[*total_clientes] = novo_cliente;
    (*total_clientes)++;
    salvarClientes(clientes, *total_clientes);
    printf("Cliente adicionado\n");
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
        printf("Cliente apagado\n");
    } else {
        printf("Cliente não encontrado\n");
    }
}

void listarClientes(Cliente clientes[], int total_clientes) {
    printf("Lista de Clientes:\n");
    for (int i = 0; i < total_clientes; i++) {
        printf("Nome: %s, CPF: %s, Tipo de conta: %s, Saldo: %.2f\n", clientes[i].nome, clientes[i].cpf, clientes[i].tipo_conta, clientes[i].saldo);
    }
}

void debito(Cliente *cliente) {
    float valor;
    float taxa = strcmp(cliente->tipo_conta, "comum") == 0 ? 0.05 : 0.03;
    printf("Digite o valor do débito: ");
    scanf("%f", &valor);
    float valor_com_taxa = valor + (valor * taxa);
    if (cliente->saldo - valor_com_taxa >= cliente->saldo_negativo) {
        cliente->saldo -= valor_com_taxa;
        printf("Débito realizado\n");
        cliente->operacoes[cliente->total_operacoes++] = -valor;
    } else {
        printf("Saldo insuficiente\n");
    }
}

void deposito(Cliente *cliente) {
    float valor;
    printf("Digite o valor do depósito: ");
    scanf("%f", &valor);
    cliente->saldo += valor;
    printf("Depósito realizado\n");
    cliente->operacoes[cliente->total_operacoes++] = valor;
}

void extrato(Cliente *cliente) {
    printf("Extrato\n");
    for (int i = 0; i < cliente->total_operacoes; i++) {
        if (cliente->operacoes[i] < 0) {
            printf("Débito: %.2f\n", -cliente->operacoes[i]);
        } else {
            printf("Depósito: %.2f\n", cliente->operacoes[i]);
        }
    }
    printf("Saldo atual: %.2f\n", cliente->saldo);
}

void transferencia(Cliente clientes[], int total_clientes) {
    char cpf_origem[12], cpf_destino[12];
    float valor;
    printf("Digite o CPF de origem: ");
    scanf("%s", cpf_origem);
    printf("Digite o CPF de destino: ");
    scanf("%s", cpf_destino);
    printf("Digite o valor da transferência: ");
    scanf("%f", &valor);

    int indice_origem = -1, indice_destino = -1;
    for (int i = 0; i < total_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf_origem) == 0) {
            indice_origem = i;
        }
        if (strcmp(clientes[i].cpf, cpf_destino) == 0) {
            indice_destino = i;
        }
    }

    if (indice_origem != -1 && indice_destino != -1) {
        Cliente *origem = &clientes[indice_origem];
        Cliente *destino = &clientes[indice_destino];
        float taxa = strcmp(origem->tipo_conta, "comum") == 0 ? 0.05 : 0.03;
        float valor_com_taxa = valor + (valor * taxa);

        if (origem->saldo - valor_com_taxa >= origem->saldo_negativo) {
            origem->saldo -= valor_com_taxa;
            destino->saldo += valor;
            origem->operacoes[origem->total_operacoes++] = -valor;
            destino->operacoes[destino->total_operacoes++] = valor;
            printf("Transferência realizada\n");
        } else {
            printf("Saldo insuficiente\n");
        }
    } else {
        printf("Conta não encntrada\n");
    }
}
