#include <stdio.h>
#include <stdlib.h>
#include "banco.h"

int main() {
    Cliente clientes[MAX_CLIENTES];
    int total_clientes = carregarClientes(clientes);

    int opcao;
    do {
        printf("\nMenu de Opcoes:\n");
        printf("1. Novo cliente\n");
        printf("2. Apagar cliente\n");
        printf("3. Listar clientes\n");
        // Adicione aqui as outras opções do menu...
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

<<<<<<< HEAD
  switch (opcao){
    case 1:
    cadastrar_cliente();
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
=======
        switch (opcao) {
            case 1:
                novoCliente(clientes, &total_clientes);
                break;
            case 2:
                apagarCliente(clientes, &total_clientes);
                break;
            case 3:
                listarClientes(clientes, total_clientes);
                break;
            // Implemente aqui os casos das outras opções do menu...
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
>>>>>>> refs/remotes/origin/Maurilio

    return 0;
}
