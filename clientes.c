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





  
}