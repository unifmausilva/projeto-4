#include <stdio.h>
#include "clientes.h"


void escolhaconta(){
 int escolha;
  printf("-----TIPOS DE CONTA-----\n");
  printf("1 - Conta Comum ");
  printf("\n");
  printf("2 - Conta Plus ");
  if(scanf("%d", &escolha) != 1){
    printf("Erro ao ler a opção\n");
    
  }
  if (escolha == 1){
    printf("Você escolheu a conta comum\n");
  }else if(escolha == 2){
    printf("Você escolheu a conta plus\n");
  }else{
    printf("Opção inválida, tente novamente\n");
  }
  
  
}
void deposito_inicial(){
  int pdeposito;

   while(1){
     
     printf("OBS: O valor minimo de deposito é de R$100,00\n");
     printf("VALOR:");
     if(scanf("%d", &pdeposito) != 1){
     printf("Erro ao ler a opção\n");
      }
     
     if(pdeposito < 100){
      printf("Valor minimo de deposito é de R$100,00\n");
        
      } else if(pdeposito >= 100){
       printf("Valor depositado com sucesso\n");
      }
    }
}

void cadastrar_cliente(){
  printf("===========================");
  printf("CADASTRAR NOVO CLIENTE\n");
  printf("Digite o seu nome:\n");
  printf("Digite seu CPF:\n");
  printf("Digite qual conta você deseja abrir:\n");
  escolhaconta();
  printf("---Faca um depósito inicial--- \n");
  deposito_inicial();
  printf("Digite uma senha de 4 digitos: \n");
  printf("===========================");

  if(scanf("%d" , &deposito ))
  
  
}
