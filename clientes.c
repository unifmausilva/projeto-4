        // Arquivo: clientes.c

        #include "clientes.h"
        #include <stdio.h>
        #include <string.h>

        void novoCliente(Cliente clientes[], int *num_clientes) {
            if (*num_clientes >= MAX_CLIENTES) {
                printf("Limite de clientes alcançado!\n");
                return;
            }

            printf("Digite o nome do cliente: ");
            scanf("%s", clientes[*num_clientes].nome);
            printf("Digite o CPF do cliente: ");
            scanf("%s", clientes[*num_clientes].cpf);
            printf("Digite o tipo de conta (COMUM = 0, PLUS = 1): ");
            scanf("%d", (int *)&clientes[*num_clientes].tipo_conta);
            printf("Digite o saldo inicial da conta: ");
            scanf("%f", &clientes[*num_clientes].saldo);
            printf("Digite a senha do cliente: ");
            scanf("%s", clientes[*num_clientes].senha);
            (*num_clientes)++;
        }

        void apagaCliente(Cliente clientes[], int *num_clientes) {
            char cpf[12];
            printf("Digite o CPF do cliente a ser apagado: ");
            scanf("%s", cpf);
            for (int i = 0; i < *num_clientes; i++) {
                if (strcmp(clientes[i].cpf, cpf) == 0) {
                    for (int j = i; j < *num_clientes - 1; j++) {
                        clientes[j] = clientes[j + 1];
                    }
                    (*num_clientes)--;
                    printf("Cliente apagado com sucesso!\n");
                    return;
                }
            }
            printf("Cliente não encontrado!\n");
        }

        void listarClientes(Cliente clientes[], int num_clientes) {
            if (num_clientes == 0) {
                printf("Nenhum cliente cadastrado!\n");
                return;
            }

            printf("Lista de Clientes:\n");
            for (int i = 0; i < num_clientes; i++) {
                printf("Nome: %s\n", clientes[i].nome);
                printf("CPF: %s\n", clientes[i].cpf);
                printf("Tipo de Conta: %s\n", clientes[i].tipo_conta == COMUM ? "Comum" : "Plus");
                printf("Saldo: %.2f\n", clientes[i].saldo);
                printf("\n");
            }
        }

        void debito(Cliente clientes[], int num_clientes) {
            char cpf[12], senha[20];
            float valor;
            printf("Digite o CPF do cliente: ");
            scanf("%s", cpf);
            printf("Digite a senha do cliente: ");
            scanf("%s", senha);
            printf("Digite o valor a ser debitado: ");
            scanf("%f", &valor);
            for (int i = 0; i < num_clientes; i++) {
                if (strcmp(clientes[i].cpf, cpf) == 0 && strcmp(clientes[i].senha, senha) == 0) {
                    clientes[i].saldo -= valor;
                    printf("Débito realizado com sucesso!\n");
                    return;
                }
            }
            printf("Cliente não encontrado ou senha incorreta!\n");
        }

        void deposito(Cliente clientes[], int num_clientes) {
            char cpf[12];
            float valor;
            printf("Digite o CPF do cliente: ");
            scanf("%s", cpf);
            printf("Digite o valor a ser depositado: ");
            scanf("%f", &valor);
            for (int i = 0; i < num_clientes; i++) {
                if (strcmp(clientes[i].cpf, cpf) == 0) {
                    clientes[i].saldo += valor;
                    printf("Depósito realizado com sucesso!\n");
                    return;
                }
            }
            printf("Cliente não encontrado!\n");
        }

        void extrato(Cliente clientes[], int num_clientes) {
            char cpf[12], senha[20];
            printf("Digite o CPF do cliente: ");
            scanf("%s", cpf);
            printf("Digite a senha do cliente: ");
            scanf("%s", senha);
            for (int i = 0; i < num_clientes; i++) {
                if (strcmp(clientes[i].cpf, cpf) == 0 && strcmp(clientes[i].senha, senha) == 0) {
                    printf("Saldo: %.2f\n", clientes[i].saldo);
                    return;
                }
            }
            printf("Cliente não encontrado ou senha incorreta!\n");
        }

        void transferencia(Cliente clientes[], int num_clientes) {
            char cpfOrigem[12], senha[20], cpfDestino[12];
            float valor;
            printf("Digite o CPF da conta de origem: ");
            scanf("%s", cpfOrigem);
            printf("Digite a senha da conta de origem: ");
            scanf("%s", senha);
            printf("Digite o CPF da conta de destino: ");
            scanf("%s", cpfDestino);
            printf("Digite o valor a ser transferido: ");
            scanf("%f", &valor);
            int indiceOrigem = -1, indiceDestino = -1;
            for (int i = 0; i < num_clientes; i++) {
                if (strcmp(clientes[i].cpf, cpfOrigem) == 0 && strcmp(clientes[i].senha, senha) == 0) {
                    indiceOrigem = i;
                }
                if (strcmp(clientes[i].cpf, cpfDestino) == 0) {
                    indiceDestino = i;
                }
            }
            if (indiceOrigem != -1 && indiceDestino != -1) {
                clientes[indiceOrigem].saldo -= valor;
                clientes[indiceDestino].saldo += valor;
                printf("Transferência realizada com sucesso!\n");
            } else {
                printf("Conta de origem ou de destino não encontrada, ou senha incorreta!\n");
            }
        }
