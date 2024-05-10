#ifndef BANCO_H_
#define BANCO_H_

#define MAX_CLIENTES 1000
#define MAX_OPERACOES 100

typedef struct {
    char nome[50];
    char cpf[12];
    char tipo_conta[6];
    float saldo;
    float saldo_negativo;
    char senha[20];
    float operacoes[MAX_OPERACOES];
} Cliente;

void salvarClientes(Cliente clientes[], int total_clientes);
int carregarClientes(Cliente clientes[]);
void novoCliente(Cliente clientes[], int *total_clientes);
void apagarCliente(Cliente clientes[], int *total_clientes);
void listarClientes(Cliente clientes[], int total_clientes);


#endif 