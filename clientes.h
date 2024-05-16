#ifndef CLIENTES_H
#define CLIENTES_H

#define MAX_CLIENTES 1000

typedef enum {
    COMUM,
    PLUS
} TipoConta;

typedef struct {
    char nome[50];
    char cpf[12];
    TipoConta tipo_conta;
    float saldo;
    float limite_negativo;
    char senha[20];
} Cliente;

void novoCliente();
void apagaCliente();
void listarClientes();
void debito();
void deposito();
void extrato();
void transferencia();

#endif // CLIENTES_H
