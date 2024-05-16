#ifndef CLIENTES_H
#define CLIENTES_H

#define MAX_CLIENTES 1000
#define MAX_OPERACOES 100

typedef enum {
    COMUM,
    PLUS
} TipoConta;

typedef struct {
    char nome[50];
    char cpf[12]; // CPF sem caracteres especiais
    TipoConta tipo_conta;
    float saldo;
    char senha[5]; // Senha de 4 dígitos
} Cliente;

typedef enum {
    DEPOSITO,
    SAQUE,
    TRANSFERENCIA
} TipoOperacao;

typedef struct {
    TipoOperacao tipo;
    char cpf_cliente[12]; // CPF do cliente relacionado à operação
    float valor;
    float tarifa;
} Operacao;

// Protótipos das funções
void cadastrar_cliente(Cliente clientes[], int *num_clientes);
void apagar_cliente(Cliente clientes[], int *num_clientes);
void listar_clientes(Cliente clientes[], int num_clientes);





#endif