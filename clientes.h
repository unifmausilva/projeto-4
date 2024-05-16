// clientes.h
#ifndef CLIENTES_H
#define CLIENTES_H

#define MAX_CLIENTES 1000
#define MAX_OPERACOES 100

typedef struct {
    char nome[50];
    char cpf[12];
    char tipoConta[6];
    float saldo;
    char senha[20];
} Cliente;

typedef struct {
    char cpf[12];
    char tipoOperacao[15];
    float valorOperacao;
    float saldoAtual;
} Operacao;

void novoCliente(Cliente listaClientes[], int *quantidadeClientes);
void apagaCliente(Cliente listaClientes[], int *quantidadeClientes);
void listarClientes(Cliente listaClientes[], int quantidadeClientes);
void debito(Cliente listaClientes[], int quantidadeClientes, Operacao listaOperacoes[], int *quantidadeOperacoes);
void deposito(Cliente listaClientes[], int quantidadeClientes, Operacao listaOperacoes[], int *quantidadeOperacoes);
void extrato(Cliente listaClientes[], int quantidadeClientes, Operacao listaOperacoes[], int quantidadeOperacoes);
void transferencia(Cliente listaClientes[], int quantidadeClientes, Operacao listaOperacoes[], int *quantidadeOperacoes);

#endif // CLIENTES_H
