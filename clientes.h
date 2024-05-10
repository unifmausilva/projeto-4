#ifndef CLIENTES_H
#define CLIENTES_H

#define MAX_CLIENTES 200
#define MAX_OPERACOES 100

typedef struct{
  char nome[50];
  char cpf[20];
  char tipo_conta[20];
  char senha[4];
  float pdeposito;
  float valornegativo;
  
} Conta;

typer struct{
  char cpf[20];
  char senha[4];
  char tipo_conta[20];
  float tarifa;

  

}



void escolhaconta();
void cadastrar_cliente();
void deposito_inicial();





#endif