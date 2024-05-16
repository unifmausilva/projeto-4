#include <stdio.h>
#include "clientes.h"

int main() {
    Cliente clientes[MAX_CLIENTES];
    Operacao operacoes[MAX_OPERACOES];
    int num_clientes = 0;
    int num_operacoes = 0;
    int opcao;

    // Carregar clientes e operações do arquivo
    carregar_clientes(clientes, &num_clientes);
    carregar_operacoes(operacoes, &num_operacoes);

    // Loop principal do programa
    do {
        printf("\n===== Menu =====\n");
        printf("1. Novo Cliente\n");
        printf("2. Apagar Cliente\n");
        printf("3. Listar Clientes\n");
        printf("4. Débito\n");
        printf("5. Depósito\n");
        printf("6. Extrato\n");
        printf("7. Transferência Entre Contas\n");
        printf("0. Sair\n");
        printf("===============\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_cliente(clientes, &num_clientes);
                break;
            case 2:
                apagar_cliente(clientes, &num_clientes);
                break;
            case 3:
                listar_clientes(clientes, num_clientes);
                break;
          case 4:
              debitar(clientes, num_clientes);
              break;
          case 5:
              depositar(clientes, num_clientes);
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