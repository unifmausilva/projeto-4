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

void cadastrar_cliente(){
  printf("===========================");
  printf("CADASTRAR NOVO CLIENTE\n");
  printf("Digite sua razão social:\n");
  printf("Digite seu CNPJ:\n");
  printf("Digite qual conta você deseja abrir:\n");
  escolhaconta();
  
}