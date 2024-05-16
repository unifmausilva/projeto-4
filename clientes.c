// clientes.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"

void novoCliente(Cliente listaClientes[], int *quantidadeClientes) {
    if (*quantidadeClientes < MAX_CLIENTES) {
        Cliente novoCliente;
        printf("Nome: ");
        scanf("%s", novoCliente.nome);
        printf("CPF: ");
        scanf("%s", novoCliente.cpf);
        printf("Tipo de conta (Comum/Plus): ");
        scanf("%s", novoCliente.tipoConta);
        printf("Saldo inicial: ");
        scanf("%f", &novoCliente.saldo);
        printf("Senha: ");
        scanf("%s", novoCliente.senha);

        listaClientes[*quantidadeClientes] = novoCliente;
        (*quantidadeClientes)++;

        printf("Cliente adicionado com sucesso!\n");
    } else {
        printf("Limite de clientes atingido!\n");
    }
}

void apagaCliente(Cliente listaClientes[], int *quantidadeClientes) {
    char cpfApagar[12];
    printf("Digite o CPF do cliente a ser apagado: ");
    scanf("%s", cpfApagar);

    int indiceApagar = -1;
    for (int i = 0; i < *quantidadeClientes; i++) {
        if (strcmp(listaClientes[i].cpf, cpfApagar) == 0) {
            indiceApagar = i;
            break;
        }
    }

    if (indiceApagar != -1) {
        for (int i = indiceApagar; i < *quantidadeClientes - 1; i++) {
            listaClientes[i] = listaClientes[i + 1];
        }
        (*quantidadeClientes)--;
        printf("Cliente apagado com sucesso!\n");
    } else {
        printf("Cliente não encontrado!\n");
    }
}

void listarClientes(Cliente listaClientes[], int quantidadeClientes) {
    printf("Lista de Clientes:\n");
    for (int i = 0; i < quantidadeClientes; i++) {
        printf("Cliente %d:\n", i + 1);
        printf("Nome: %s\n", listaClientes[i].nome);
        printf("CPF: %s\n", listaClientes[i].cpf);
        printf("Tipo de conta: %s\n", listaClientes[i].tipoConta);
        printf("Saldo: %.2f\n", listaClientes[i].saldo);
        printf("\n");
    }
}

void debito(Cliente listaClientes[], int quantidadeClientes, Operacao listaOperacoes[], int *quantidadeOperacoes) {
    char cpf[12];
    char senha[20];
    float valor;
    printf("CPF: ");
    scanf("%s", cpf);
    printf("Senha: ");
    scanf("%s", senha);
    printf("Valor a debitar: ");
    scanf("%f", &valor);

    int indiceCliente = -1;
    for (int i = 0; i < quantidadeClientes; i++) {
        if (strcmp(listaClientes[i].cpf, cpf) == 0 && strcmp(listaClientes[i].senha, senha) == 0) {
            indiceCliente = i;
            break;
        }
    }

    if (indiceCliente != -1) {
        if (valor <= listaClientes[indiceCliente].saldo) {
            listaClientes[indiceCliente].saldo -= valor;
            printf("Débito realizado com sucesso!\n");

            // Registrar a operação
            strcpy(listaOperacoes[*quantidadeOperacoes].cpf, cpf);
            strcpy(listaOperacoes[*quantidadeOperacoes].tipoOperacao, "Débito");
            listaOperacoes[*quantidadeOperacoes].valorOperacao = valor;
            listaOperacoes[*quantidadeOperacoes].saldoAtual = listaClientes[indiceCliente].saldo;
            (*quantidadeOperacoes)++;
        } else {
            printf("Saldo insuficiente!\n");
        }
    } else {
        printf("CPF ou senha incorretos!\n");
    }
}void deposito(Cliente listaClientes[], int quantidadeClientes, Operacao listaOperacoes[], int *quantidadeOperacoes) {
    char cpf[12];
    float valor;
    printf("CPF: ");
    scanf("%s", cpf);
    printf("Valor a depositar: ");
    scanf("%f", &valor);

    int indiceCliente = -1;
    for (int i = 0; i < quantidadeClientes; i++) {
        if (strcmp(listaClientes[i].cpf, cpf) == 0) {
            indiceCliente = i;
            break;
        }
    }

    if (indiceCliente != -1) {
        listaClientes[indiceCliente].saldo += valor;
        printf("Depósito realizado com sucesso!\n");

        // Registrar a operação
        strcpy(listaOperacoes[*quantidadeOperacoes].cpf, cpf);
        strcpy(listaOperacoes[*quantidadeOperacoes].tipoOperacao, "Depósito");
        listaOperacoes[*quantidadeOperacoes].valorOperacao = valor;
        listaOperacoes[*quantidadeOperacoes].saldoAtual = listaClientes[indiceCliente].saldo;
        (*quantidadeOperacoes)++;
    } else {
        printf("Cliente não encontrado!\n");
    }
}

void extrato(Cliente listaClientes[], int quantidadeClientes, Operacao listaOperacoes[], int quantidadeOperacoes) {
    char cpf[12];
    char senha[20];
    printf("CPF: ");
    scanf("%s", cpf);
    printf("Senha: ");
    scanf("%s", senha);

    int indiceCliente = -1;
    for (int i = 0; i < quantidadeClientes; i++) {
        if (strcmp(listaClientes[i].cpf, cpf) == 0 && strcmp(listaClientes[i].senha, senha) == 0) {
            indiceCliente = i;
            break;
        }
    }

    if (indiceCliente != -1) {
        char nomeArquivo[50];
        sprintf(nomeArquivo, "extrato_%s.txt", cpf);
        FILE *arquivo = fopen(nomeArquivo, "w");
        if (arquivo != NULL) {
            fprintf(arquivo, "Extrato para o cliente %s:\n\n", listaClientes[indiceCliente].nome);
            for (int i = 0; i < quantidadeOperacoes; i++) {
                if (strcmp(listaOperacoes[i].cpf, cpf) == 0) {
                    fprintf(arquivo, "Operação: %s\n", listaOperacoes[i].tipoOperacao);
                    fprintf(arquivo, "Valor: %.2f\n", listaOperacoes[i].valorOperacao);
                    fprintf(arquivo, "Saldo atual: %.2f\n", listaOperacoes[i].saldoAtual);
                    fprintf(arquivo, "\n");
                }
            }
            printf("Extrato gerado com sucesso!\n");
            fclose(arquivo);
        } else {
            printf("Erro ao abrir o arquivo para escrita!\n");
        }
    } else {
        printf("CPF ou senha incorretos!\n");
    }
}

void transferencia(Cliente listaClientes[], int quantidadeClientes, Operacao listaOperacoes[], int *quantidadeOperacoes) {
    char cpfOrigem[12];
    char senhaOrigem[20];
    char cpfDestino[12];
    float valor;
    printf("CPF (Origem): ");
    scanf("%s", cpfOrigem);
    printf("Senha (Origem): ");
    scanf("%s", senhaOrigem);
    printf("CPF (Destino): ");
    scanf("%s", cpfDestino);
    printf("Valor a transferir: ");
    scanf("%f", &valor);

    int indiceOrigem = -1;
    int indiceDestino = -1;
    for (int i = 0; i < quantidadeClientes; i++) {
        if (strcmp(listaClientes[i].cpf, cpfOrigem) == 0 && strcmp(listaClientes[i].senha, senhaOrigem) == 0) {
            indiceOrigem = i;
        }
        if (strcmp(listaClientes[i].cpf, cpfDestino) == 0) {
            indiceDestino = i;
        }
    }

    if (indiceOrigem != -1 && indiceDestino != -1) {
        if (valor <= listaClientes[indiceOrigem].saldo) {
            listaClientes[indiceOrigem].saldo -= valor;
            listaClientes[indiceDestino].saldo += valor;
            printf("Transferência realizada com sucesso!\n");

            // Registrar a operação na conta de origem
            strcpy(listaOperacoes[*quantidadeOperacoes].cpf, cpfOrigem);
            strcpy(listaOperacoes[*quantidadeOperacoes].tipoOperacao, "Transferência (Saída)");
            listaOperacoes[*quantidadeOperacoes].valorOperacao = valor;
            listaOperacoes[*quantidadeOperacoes].saldoAtual = listaClientes[indiceOrigem].saldo;
            (*quantidadeOperacoes)++;

            // Registrar a operação na conta de destino
            strcpy(listaOperacoes[*quantidadeOperacoes].cpf, cpfDestino);
            strcpy(listaOperacoes[*quantidadeOperacoes].tipoOperacao, "Transferência (Entrada)");
            listaOperacoes[*quantidadeOperacoes].valorOperacao = valor;
            listaOperacoes[*quantidadeOperacoes].saldoAtual = listaClientes[indiceDestino].saldo;
            (*quantidadeOperacoes)++;
        } else {
            printf("Saldo insuficiente na conta de origem!\n");
        }
    } else {
        printf("CPF(s) ou senha(s) incorretos!\n");
    }
}
