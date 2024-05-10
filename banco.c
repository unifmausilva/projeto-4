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
        printf("Cliente não encontrado.\n");
    }
}

void listarClientes(Cliente clientes[], int total_clientes) {
    printf("Lista de Clientes:\n");
    printf("%d\n",total_clientes);
    for (int i = 0; i < total_clientes; i++) {
        printf("Nome: %s , CPF: %s, Saldo: %f, Tipo de conta: %s", clientes[i].nome, clientes[i].cpf,  clientes[i].saldo,  clientes[i].tipo_conta);
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
            float taxa = strcmp(clientes[i].tipo_conta, "comum") == 0 ? 0.05 * valor : 0.03 * valor;
            if (clientes[i].saldo - valor - taxa >= clientes[i].saldo_negativo) {
                clientes[i].saldo -= (valor + taxa);
                printf("Débito realizado %.2f\n", clientes[i].saldo);
            } else {
                printf("Saldo insuficiente\n");
            }
            break;
        }
    }
    if (!cliente_encontrado) {
        printf("CPF ou senha incorretos.\n");
    }
}

void deposito(Cliente clientes[], int total_clientes) {
    char cpf[12];
    float valor;

    printf("Digite o CPF do cliente: ");
    scanf("%s", cpf);

    printf("Digite o valor que sera depositado: ");

    scanf("%f", &valor);

    int cliente_encontrado = 0;
    for (int i = 0; i < total_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            cliente_encontrado = 1;
            clientes[i].saldo += valor;
            printf("Depósito realizado. %.2f\n", clientes[i].saldo);

            printf("Depósito realizado com sucesso. Novo saldo: %.2f\n", clientes[i].saldo);

            break;
        }
    }
    if (!cliente_encontrado) {
        printf("CPF não encontrado.\n");
    }
}

void extrato(Cliente clientes[], int total_clientes) {
    char cpf[12];
    char senha[20];
    FILE *arquivo;
    float taxa;
    float valor;
    int cliente_encontrado = 0;

    printf("Digite o CPF do cliente: ");
    scanf("%s", cpf);
    printf("Digite a senha: ");
    scanf("%s", senha);

    for (int i = 0; i < total_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0 && strcmp(clientes[i].senha, senha) == 0) {
            cliente_encontrado = 1;
            arquivo = fopen("extrato.txt", "w");
            if (arquivo == NULL) {
                printf("Erro ao abrir o arquivo.\n");
                return;
            }
            fprintf(arquivo, "Extrato do cliente %s\n", clientes[i].nome);
            fprintf(arquivo, "CPF: %s\n", clientes[i].cpf);
            for (int j = 0; j < clientes[i].num_operacoes; j++) {
                valor = clientes[i].operacoes[j];
                taxa = strcmp(clientes[i].tipo_conta, "comum") == 0 ? 0.05 * valor : 0.03 * valor;
                if (valor < 0) {
                    fprintf(arquivo, "Débito: %.2f\n", valor);
                    fprintf(arquivo, "Tarifa: %.2f\n", taxa);
                } else {
                    fprintf(arquivo, "Depósito: %.2f\n", valor);
                }
            }
            fclose(arquivo);
            printf("Extrato gerado com sucesso. Verifique o arquivo extrato.txt.\n");
            break;
        }
    }
    if (!cliente_encontrado) {
        printf("CPF ou senha incorretos.\n");
    }
}

void transferencia(Cliente clientes[], int total_clientes) {
    char cpf_origem[12];
    char senha_origem[20];
    char cpf_destino[12];
    float valor;

    printf("Digite o CPF de origem: ");
    scanf("%s", cpf_origem);
    printf("Digite a senha: ");
    scanf("%s", senha_origem);
    printf("Digite o CPF de destino: ");
    scanf("%s", cpf_destino);
    printf("Digite o valor: ");
    scanf("%f", &valor);

    int cliente_origem_encontrado = 0;
    int cliente_destino_encontrado = 0;

    for (int i = 0; i < total_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf_origem) == 0 && strcmp(clientes[i].senha, senha_origem) == 0) {
            cliente_origem_encontrado = 1;
            if (clientes[i].saldo - valor >= clientes[i].saldo_negativo) {
                for (int j = 0; j < total_clientes; j++) {
                    if (strcmp(clientes[j].cpf, cpf_destino) == 0) {
                        cliente_destino_encontrado = 1;
                        clientes[i].saldo -= valor;
                        clientes[j].saldo += valor;
                        printf("Transferência realizada com sucesso.\n");
                        salvarClientes(clientes, total_clientes);
                        break;
                    }
                }
                if (!cliente_destino_encontrado) {
                    printf("Conta de destino não encontrada.\n");
                }
            } else {
                printf("Saldo insuficiente para realizar a transferência.\n");
            }
            break;
        }
    }

    if (!cliente_origem_encontrado) {
        printf("CPF ou senha da conta de origem incorretos.\n");
    }
}


void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

