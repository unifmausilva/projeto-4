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
Cliente *buscar_cliente_por_cpf(Cliente clientes[], int num_clientes, const char *cpf);
int autenticar_cliente(Cliente *cliente);
void debitar(Cliente clientes[], int num_clientes);
void depositar(Cliente clientes[], int num_clientes);
void extrato(Cliente clientes[], int num_clientes);




#endif