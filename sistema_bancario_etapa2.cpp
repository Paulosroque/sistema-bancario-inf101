#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    // Paulo Sergio Roque de Sa - Matricula 28612
    // INF101 - Sistema Bancario - Etapa 2

    const int MAX_CONTAS = 100;
    const int MAX_MOVIMENTACOES = 500;

    int numeroConta[MAX_CONTAS];
    string nomeCliente[MAX_CONTAS];
    string cpf[MAX_CONTAS];
    int tipoConta[MAX_CONTAS];
    double saldo[MAX_CONTAS];
    bool contaAtiva[MAX_CONTAS];

    int contaMovimentacao[MAX_MOVIMENTACOES];
    char tipoMovimentacao[MAX_MOVIMENTACOES];
    double valorMovimentacao[MAX_MOVIMENTACOES];

    int quantidadeContas = 0;
    int quantidadeMovimentacoes = 0;
    int opcao = 0;

    cout << fixed << setprecision(2);

    do {
        cout << "\n---------------------------------\n";
        cout << "          BANCO PAULO\n";
        cout << "---------------------------------\n";
        cout << "1 - Cadastrar conta\n";
        cout << "2 - Listar contas\n";
        cout << "3 - Consultar conta\n";
        cout << "4 - Depositar\n";
        cout << "5 - Sacar\n";
        cout << "6 - Transferir\n";
        cout << "7 - Exibir extrato\n";
        cout << "8 - Alterar tipo da conta\n";
        cout << "9 - Ativar ou desativar conta\n";
        cout << "0 - Sair\n";
        cout << "Escolha: ";

        if (!(cin >> opcao)) {
            cout << "\nEntrada encerrada ou invalida.\n";
            return 0;
        }

        switch (opcao) {
            case 1: {
                if (quantidadeContas >= MAX_CONTAS) {
                    cout << "Limite de contas atingido.\n";
                    break;
                }

                int numero;
                bool repetido = false;

                cout << "\nNumero da conta: ";
                if (!(cin >> numero)) return 0;

                if (numero <= 0) {
                    cout << "O numero deve ser maior que zero.\n";
                    break;
                }

                // Impede duas contas com o mesmo numero.
                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numero) {
                        repetido = true;
                        break;
                    }
                }

                if (repetido) {
                    cout << "Ja existe uma conta com esse numero.\n";
                    break;
                }

                int posicao = quantidadeContas;

                cout << "Nome do cliente: ";
                getline(cin >> ws, nomeCliente[posicao]);

                cout << "CPF: ";
                getline(cin, cpf[posicao]);

                if (nomeCliente[posicao].empty() ||
                    cpf[posicao].empty()) {
                    cout << "Nome e CPF devem ser preenchidos.\n";
                    break;
                }

                cout << "Tipo (1 - Corrente / 2 - Poupanca): ";
                if (!(cin >> tipoConta[posicao])) return 0;

                if (tipoConta[posicao] != 1 &&
                    tipoConta[posicao] != 2) {
                    cout << "Tipo invalido. Cadastro cancelado.\n";
                    break;
                }

                cout << "Saldo inicial: ";
                if (!(cin >> saldo[posicao])) return 0;

                if (saldo[posicao] < 0) {
                    cout << "O saldo nao pode ser negativo.\n";
                    break;
                }

                numeroConta[posicao] = numero;
                contaAtiva[posicao] = true;
                quantidadeContas++;

                cout << "Conta cadastrada com sucesso.\n";
                break;
            }

            case 2: {
                if (quantidadeContas == 0) {
                    cout << "Nenhuma conta cadastrada.\n";
                    break;
                }

                cout << "\n--- CONTAS CADASTRADAS ---\n";

                for (int i = 0; i < quantidadeContas; i++) {
                    cout << "\nConta: " << numeroConta[i] << "\n";
                    cout << "Cliente: " << nomeCliente[i] << "\n";
                    cout << "Saldo: R$ " << saldo[i] << "\n";
                    cout << "Situacao: "
                         << (contaAtiva[i] ? "Ativa" : "Inativa")
                         << "\n";
                }

                cout << "\nTotal de contas: "
                     << quantidadeContas << "\n";
                break;
            }

            case 3:
            case 4:
            case 5:
            case 7:
            case 8:
            case 9: {
                if (quantidadeContas == 0) {
                    cout << "Nenhuma conta cadastrada.\n";
                    break;
                }

                int numero;
                int posicao = -1;

                cout << "\nNumero da conta: ";
                if (!(cin >> numero)) return 0;

                // As operacoes usam a mesma busca da conta.
                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numero) {
                        posicao = i;
                        break;
                    }
                }

                if (posicao == -1) {
                    cout << "Conta nao encontrada.\n";
                    break;
                }

                if (opcao == 3) {
                    cout << "\n--- DADOS DA CONTA ---\n";
                    cout << "Numero: " << numeroConta[posicao] << "\n";
                    cout << "Nome: " << nomeCliente[posicao] << "\n";
                    cout << "CPF: " << cpf[posicao] << "\n";
                    cout << "Tipo: "
                         << (tipoConta[posicao] == 1
                             ? "Corrente" : "Poupanca")
                         << "\n";
                    cout << "Saldo: R$ " << saldo[posicao] << "\n";
                    cout << "Situacao: "
                         << (contaAtiva[posicao]
                             ? "Ativa" : "Inativa")
                         << "\n";

                } else if (opcao == 4 || opcao == 5) {
                    if (!contaAtiva[posicao]) {
                        cout << "A conta esta inativa.\n";
                        break;
                    }

                    if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES) {
                        cout << "Historico cheio. Operacao cancelada.\n";
                        break;
                    }

                    double valor;

                    cout << "Valor: ";
                    if (!(cin >> valor)) return 0;

                    if (valor <= 0) {
                        cout << "O valor deve ser maior que zero.\n";
                        break;
                    }

                    if (opcao == 5 && valor > saldo[posicao]) {
                        cout << "Saldo insuficiente.\n";
                        break;
                    }

                    int registro = quantidadeMovimentacoes;

                    if (opcao == 4) {
                        saldo[posicao] += valor;
                        tipoMovimentacao[registro] = 'D';
                    } else {
                        saldo[posicao] -= valor;
                        tipoMovimentacao[registro] = 'S';
                    }

                    contaMovimentacao[registro] = numeroConta[posicao];
                    valorMovimentacao[registro] = valor;
                    quantidadeMovimentacoes++;

                    cout << "Operacao realizada com sucesso.\n";
                    cout << "Saldo atual: R$ " << saldo[posicao] << "\n";

                } else if (opcao == 7) {
                    bool encontrou = false;

                    cout << "\n--- EXTRATO ---\n";
                    cout << "Conta: " << numeroConta[posicao] << "\n";
                    cout << "Cliente: " << nomeCliente[posicao] << "\n";

                    for (int i = 0; i < quantidadeMovimentacoes; i++) {
                        if (contaMovimentacao[i] == numeroConta[posicao]) {
                            encontrou = true;

                            if (tipoMovimentacao[i] == 'D') {
                                cout << "Entrada (deposito/transferencia): R$ ";
                            } else {
                                cout << "Saida (saque/transferencia): R$ ";
                            }

                            cout << valorMovimentacao[i] << "\n";
                        }
                    }

                    if (!encontrou) {
                        cout << "Nenhuma movimentacao registrada.\n";
                    }

                    cout << "Saldo atual: R$ " << saldo[posicao] << "\n";

                } else if (opcao == 8) {
                    if (!contaAtiva[posicao]) {
                        cout << "Ative a conta antes de alterar o tipo.\n";
                        break;
                    }

                    int novoTipo;

                    cout << "Novo tipo (1 - Corrente / 2 - Poupanca): ";
                    if (!(cin >> novoTipo)) return 0;

                    if (novoTipo != 1 && novoTipo != 2) {
                        cout << "Tipo invalido.\n";
                        break;
                    }

                    tipoConta[posicao] = novoTipo;
                    cout << "Tipo alterado com sucesso.\n";

                } else if (opcao == 9) {
                    contaAtiva[posicao] = !contaAtiva[posicao];

                    cout << (contaAtiva[posicao]
                             ? "Conta ativada.\n"
                             : "Conta desativada.\n");
                }

                break;
            }

            case 6: {
                if (quantidadeContas < 2) {
                    cout << "Cadastre pelo menos duas contas.\n";
                    break;
                }

                int numeroOrigem;
                int numeroDestino;
                int origem = -1;
                int destino = -1;
                double valor;

                cout << "\nConta de origem: ";
                if (!(cin >> numeroOrigem)) return 0;

                cout << "Conta de destino: ";
                if (!(cin >> numeroDestino)) return 0;

                if (numeroOrigem == numeroDestino) {
                    cout << "As contas devem ser diferentes.\n";
                    break;
                }

                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numeroOrigem) {
                        origem = i;
                    }

                    if (numeroConta[i] == numeroDestino) {
                        destino = i;
                    }
                }

                if (origem == -1 || destino == -1) {
                    cout << "Conta de origem ou destino nao encontrada.\n";
                    break;
                }

                if (!contaAtiva[origem] || !contaAtiva[destino]) {
                    cout << "As duas contas precisam estar ativas.\n";
                    break;
                }

                // A transferencia precisa de dois registros livres.
                if (quantidadeMovimentacoes + 2 > MAX_MOVIMENTACOES) {
                    cout << "Sem espaco no historico para transferir.\n";
                    break;
                }

                cout << "Valor da transferencia: ";
                if (!(cin >> valor)) return 0;

                if (valor <= 0) {
                    cout << "O valor deve ser maior que zero.\n";
                    break;
                }

                if (valor > saldo[origem]) {
                    cout << "Saldo insuficiente.\n";
                    break;
                }

                saldo[origem] -= valor;
                saldo[destino] += valor;

                // Registra a saida da conta de origem.
                contaMovimentacao[quantidadeMovimentacoes] =
                    numeroConta[origem];
                tipoMovimentacao[quantidadeMovimentacoes] = 'S';
                valorMovimentacao[quantidadeMovimentacoes] = valor;
                quantidadeMovimentacoes++;

                // Registra a entrada na conta de destino.
                contaMovimentacao[quantidadeMovimentacoes] =
                    numeroConta[destino];
                tipoMovimentacao[quantidadeMovimentacoes] = 'D';
                valorMovimentacao[quantidadeMovimentacoes] = valor;
                quantidadeMovimentacoes++;

                cout << "Transferencia realizada com sucesso.\n";
                cout << "Saldo da origem: R$ " << saldo[origem] << "\n";
                cout << "Saldo do destino: R$ " << saldo[destino] << "\n";
                break;
            }

            case 0:
                cout << "\nPrograma encerrado.\n";
                break;

            default:
                cout << "Opcao invalida.\n";
        }

    } while (opcao != 0);

    return 0;
}