#include <stdio.h>

int main (){
  int opcao;
  printf("Digite uma opção\n");
  printf("====================\n");
  printf("1 - Cadastrar cliente\n");
  printf("\n");
  printf("2 - Apagar cliente\n ");
  printf("\n");
  printf("3 - Listar clientes\n");
  printf("\n");
  printf("4 - Débito\n");
  printf("\n");
  printf("5 - Depósito\n");
  printf("\n");
  printf("6 - Extrato\n");
  printf("\n");
  printf("7 - Transferência entre contas");
  printf("\n");
  printf("8 - Sair\n");
  printf("=====================\n");
  
  if(scanf("%d", &opcao) != 1){
    printf("Erro ao ler a opção\n");
    return 1;
  }

  switch (opcao){
    case 1:
    printf("Cadastrar cliente");
    break;
    case 2:
    printf("Apagar cliente");
    break;
    case 3:
    printf("Listar clientes");
    break;
    case 4:
    printf("Débito");
    break;
    case 5:
    printf("Depósito");
    break;
    case 6:
    printf("Extrato");
    break;
    case 7:
    printf("Transferência entre contas");
    break;
    case 8:
    printf("Sair");
    break;
    default:
    printf("Opção inválida");
    break;  
    
  }while(opcao  != 8);
  return 0;

  
}