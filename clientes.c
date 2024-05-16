void cadastrar_cliente(Cliente clientes[], int *num_clientes) {
  if (*num_clientes >= MAX_CLIENTES) {
      printf("Limite máximo de clientes atingido.\n");
      return;
  }

  Cliente novo_cliente;

  printf("Nome: ");
  scanf("%s", novo_cliente.nome);

  printf("CPF (apenas números): ");
  scanf("%s", novo_cliente.cpf);

  printf("Tipo de conta (0 para Comum, 1 para Plus): ");
  int tipo_conta;
  scanf("%d", &tipo_conta);
  novo_cliente.tipo_conta = (tipo_conta == 1) ? PLUS : COMUM;

  printf("Saldo inicial: ");
  scanf("%f", &novo_cliente.saldo);

  printf("Senha (4 dígitos): ");
  scanf("%s", novo_cliente.senha);

  clientes[*num_clientes] = novo_cliente;
  (*num_clientes)++;

  printf("Cliente cadastrado com sucesso.\n");
}

void apagar_cliente(Cliente clientes[], int *num_clientes) {
  char cpf[12];
  printf("Digite o CPF do cliente a ser removido: ");
  scanf("%s", cpf);

  int i;
  for (i = 0; i < *num_clientes; i++) {
      if (strcmp(clientes[i].cpf, cpf) == 0) {
          printf("Cliente encontrado: %s - %s\n", clientes[i].nome, clientes[i].cpf);
          printf("Confirma a remoção? (S/N): ");
          char confirmacao;
          scanf(" %c", &confirmacao);
          if (confirmacao == 'S' || confirmacao == 's') {
              // Remover cliente
              int j;
              for (j = i; j < (*num_clientes - 1); j++) {
                  clientes[j] = clientes[j + 1];
              }
              (*num_clientes)--;
              printf("Cliente removido com sucesso.\n");
          } else {
              printf("Remoção cancelada.\n");
          }
          return;
      }
  }

  printf("Cliente com CPF %s não encontrado.\n", cpf);
}

void listar_clientes(Cliente clientes[], int num_clientes) {
  if (num_clientes == 0) {
      printf("Nenhum cliente cadastrado.\n");
      return;
  }

  printf("Lista de clientes:\n");
  int i;
  for (i = 0; i < num_clientes; i++) {
      printf("%d. %s - %s - Saldo: %.2f\n", i + 1, clientes[i].nome, clientes[i].cpf, clientes[i].saldo);
  }
  void debitar(Cliente clientes[], int num_clientes) {
    char cpf[12];
    printf("Digite o CPF do cliente: ");
    scanf("%s", cpf);

    Cliente *cliente = buscar_cliente_por_cpf(clientes, num_clientes, cpf);
    if (cliente == NULL) {
        printf("Cliente não encontrado.\n");
        return;
    }

    printf("Senha: ");
    char senha[5];
    scanf("%s", senha);

    if (strcmp(cliente->senha, senha) != 0) {
        printf("Senha incorreta.\n");
        return;
    }

    float valor;
    printf("Valor do débito: ");
    scanf("%f", &valor);

    if (cliente->tipo_conta == COMUM) {
        // Verifica saldo negativo máximo permitido
        if (cliente->saldo - valor < -1000) {
            printf("Saldo negativo máximo excedido.\n");
            return;
        }
        // Aplica taxa de débito
        valor *= 1.05; // 5% de taxa
    } else if (cliente->tipo_conta == PLUS) {
        // Verifica saldo negativo máximo permitido
        if (cliente->saldo - valor < -5000) {
            printf("Saldo negativo máximo excedido.\n");
            return;
        }
        // Aplica taxa de débito
        valor *= 1.03; // 3% de taxa
    }

    // Atualiza o saldo do cliente
    cliente->saldo -= valor;

    // Registra a operação
    Operacao op = {SAQUE, "", valor, valor * 0.05}; // Tarifa de 5% em todos os saques
    strcpy(op.cpf_cliente, cpf);
    operacoes[num_operacoes++] = op;

    printf("Débito realizado com sucesso.\n");
  }

  void depositar(Cliente clientes[], int num_clientes) {
    char cpf[12];
    printf("Digite o CPF do cliente: ");
    scanf("%s", cpf);

    Cliente *cliente = buscar_cliente_por_cpf(clientes, num_clientes, cpf);
    if (cliente == NULL) {
        printf("Cliente não encontrado.\n");
        return;
    }

    float valor;
    printf("Valor do depósito: ");
    scanf("%f", &valor);

    // Atualiza o saldo do cliente
    cliente->saldo += valor;

    // Registra a operação
    Operacao op = {DEPOSITO, "", valor, 0}; // Depósito não possui tarifa
    strcpy(op.cpf_cliente, cpf);
    operacoes[num_operacoes++] = op;

    printf("Depósito realizado com sucesso.\n");
  }
  void extrato(Cliente clientes[], int num_clientes) {
      char cpf[12];
      printf("Digite o CPF do cliente: ");
      scanf("%s", cpf);

      Cliente *cliente = buscar_cliente_por_cpf(clientes, num_clientes, cpf);
      if (cliente == NULL) {
          printf("Cliente não encontrado.\n");
          return;
      }

      printf("Senha: ");
      char senha[5];
      scanf("%s", senha);

      if (strcmp(cliente->senha, senha) != 0) {
          printf("Senha incorreta.\n");
          return;
      }

      printf("Extrato do cliente %s:\n", cliente->nome);
      printf("Saldo atual: R$%.2f\n", cliente->saldo);
      printf("Operações realizadas:\n");

      int i;
      for (i = 0; i < num_operacoes; i++) {
          if (strcmp(operacoes[i].cpf_cliente, cpf) == 0) {
              printf("- Tipo: ");
              switch (operacoes[i].tipo) {
                  case DEPOSITO:
                      printf("Depósito\n");
                      break;
                  case SAQUE:
                      printf("Débito\n");
                      break;
                  case TRANSFERENCIA:
                      printf("Transferência\n");
                      break;
              }
              printf("  Valor: R$%.2f\n", operacoes[i].valor);
              printf("  Tarifa: R$%.2f\n", operacoes[i].tarifa);
          }
      }
  }

  void transferencia(Cliente clientes[], int num_clientes) {
      char cpf_origem[12];
      printf("Digite o CPF do cliente de origem: ");
      scanf("%s", cpf_origem);

      Cliente *cliente_origem = buscar_cliente_por_cpf(clientes, num_clientes, cpf_origem);
      if (cliente_origem == NULL) {
          printf("Cliente de origem não encontrado.\n");
          return;
      }

      printf("Senha: ");
      char senha[5];
      scanf("%s", senha);

      if (strcmp(cliente_origem->senha, senha) != 0) {
          printf("Senha incorreta.\n");
          return;
      }

      char cpf_destino[12];
      printf("Digite o CPF do cliente de destino: ");
      scanf("%s", cpf_destino);

      Cliente *cliente_destino = buscar_cliente_por_cpf(clientes, num_clientes, cpf_destino);
      if (cliente_destino == NULL) {
          printf("Cliente de destino não encontrado.\n");
          return;
      }

      float valor;
      printf("Valor da transferência: ");
      scanf("%f", &valor);

      // Verifica se há saldo suficiente na conta de origem
      if (cliente_origem->saldo < valor) {
          printf("Saldo insuficiente para realizar a transferência.\n");
          return;
      }

      // Atualiza o saldo das contas de origem e destino
      cliente_origem->saldo -= valor;
      cliente_destino->saldo += valor;

      // Registra as operações
      Operacao op_origem = {TRANSFERENCIA, "", valor, 0}; // Transferência não possui tarifa
      Operacao op_destino = {TRANSFERENCIA, "", valor, 0};
      strcpy(op_origem.cpf_cliente, cpf_origem);
      strcpy(op_destino.cpf_cliente, cpf_destino);
      operacoes[num_operacoes++] = op_origem;
      operacoes[num_operacoes++] = op_destino;

      printf("Transferência realizada com sucesso.\n");
  }
  void salvar_clientes(Cliente clientes[], int num_clientes) {
    FILE *arquivo = fopen("clientes.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fwrite(&num_clientes, sizeof(int), 1, arquivo);
    fwrite(clientes, sizeof(Cliente), num_clientes, arquivo);

    fclose(arquivo);
  }

  void carregar_clientes(Cliente clientes[], int *num_clientes) {
    FILE *arquivo = fopen("clientes.bin", "rb");
    if (arquivo ==    NULL) {
        printf("Arquivo de clientes não encontrado.\n");
        return;
      }

      fread(num_clientes, sizeof(int), 1, arquivo);
      fread(clientes, sizeof(Cliente), *num_clientes, arquivo);

      fclose(arquivo);
      }

      void salvar_operacoes(Operacao operacoes[], int num_operacoes) {
      FILE *arquivo = fopen("operacoes.bin", "wb");
      if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
      }

      fwrite(&num_operacoes, sizeof(int), 1, arquivo);
      fwrite(operacoes, sizeof(Operacao), num_operacoes, arquivo);

      fclose(arquivo);
      }

      void carregar_operacoes(Operacao operacoes[], int *num_operacoes) {
      FILE *arquivo = fopen("operacoes.bin", "rb");
      if (arquivo == NULL) {
        printf("Arquivo de operações não encontrado.\n");
        return;
      }

      fread(num_operacoes, sizeof(int), 1, arquivo);
      fread(operacoes, sizeof(Operacao), *num_operacoes, arquivo);

      fclose(arquivo);
      }






  
}