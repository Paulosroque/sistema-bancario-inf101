#include <iostream>
#include <string>

using namespace std;

const int MAX_CONTAS = 5;

int main() {
    int numeroConta[MAX_CONTAS];
    string nomeCliente[MAX_CONTAS];
    string cpf[MAX_CONTAS];
    int tipoConta[MAX_CONTAS];
    double saldo[MAX_CONTAS];
    bool contaAtiva[MAX_CONTAS];

    int quantidadeContas = 0;
    int opcao;

    do {
        cout << "\n---------------------------------\n";
        cout << "          BANCO PAULO\n";
        cout << "---------------------------------\n";
        cout << "1 - Cadastrar conta\n";
        cout << "2 - Consultar conta\n";
        cout << "3 - Verificar saldo\n";
        cout << "4 - Alterar tipo da conta\n";
        cout << "5 - Ativar ou desativar conta\n";
        cout << "6 - Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1: {
                if (quantidadeContas == MAX_CONTAS) {
                    cout << "\nLimite de 5 contas atingido.\n";
                    break;
                }

                int posicao = quantidadeContas;

                cout << "\n--- CADASTRO DE CONTA ---\n";

                cout << "Numero da conta: ";
                cin >> numeroConta[posicao];

                while (numeroConta[posicao] <= 0) {
                    cout << "Numero invalido. Digite um numero maior que zero: ";
                    cin >> numeroConta[posicao];
                }

                cin.ignore();

                cout << "Nome do cliente: ";
                getline(cin, nomeCliente[posicao]);

                cout << "CPF: ";
                getline(cin, cpf[posicao]);

                cout << "Tipo da conta\n";
                cout << "1 - Corrente\n";
                cout << "2 - Poupanca\n";
                cout << "Escolha: ";
                cin >> tipoConta[posicao];

                while (tipoConta[posicao] != 1 && tipoConta[posicao] != 2) {
                    cout << "Tipo invalido. Digite 1 ou 2: ";
                    cin >> tipoConta[posicao];
                }

                cout << "Saldo inicial: ";
                cin >> saldo[posicao];

                while (saldo[posicao] < 0) {
                    cout << "Saldo invalido. Digite um valor maior ou igual a zero: ";
                    cin >> saldo[posicao];
                }

                contaAtiva[posicao] = true;
                quantidadeContas++;

                cout << "\nConta cadastrada com sucesso.\n";
                break;
            }

            case 2: {
                int numero;
                int posicao = -1;

                if (quantidadeContas == 0) {
                    cout << "\nNenhuma conta cadastrada.\n";
                    break;
                }

                cout << "\nDigite o numero da conta: ";
                cin >> numero;

                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numero) {
                        posicao = i;
                    }
                }

                if (posicao == -1) {
                    cout << "Conta nao encontrada.\n";
                } else {
                    cout << "\n--- DADOS DA CONTA ---\n";
                    cout << "Numero: " << numeroConta[posicao] << endl;
                    cout << "Nome: " << nomeCliente[posicao] << endl;
                    cout << "CPF: " << cpf[posicao] << endl;

                    if (tipoConta[posicao] == 1) {
                        cout << "Tipo: Corrente\n";
                    } else {
                        cout << "Tipo: Poupanca\n";
                    }

                    cout << "Saldo: R$ " << saldo[posicao] << endl;

                    if (contaAtiva[posicao]) {
                        cout << "Situacao: Ativa\n";
                    } else {
                        cout << "Situacao: Inativa\n";
                    }
                }

                break;
            }

            case 3: {
                int numero;
                int posicao = -1;

                if (quantidadeContas == 0) {
                    cout << "\nNenhuma conta cadastrada.\n";
                    break;
                }

                cout << "\nDigite o numero da conta: ";
                cin >> numero;

                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numero) {
                        posicao = i;
                    }
                }

                if (posicao == -1) {
                    cout << "Conta nao encontrada.\n";
                } else if (!contaAtiva[posicao]) {
                    cout << "A conta esta inativa.\n";
                } else {
                    cout << "Saldo atual: R$ " << saldo[posicao] << endl;
                }

                break;
            }

            case 4: {
                int numero;
                int posicao = -1;
                int novoTipo;

                if (quantidadeContas == 0) {
                    cout << "\nNenhuma conta cadastrada.\n";
                    break;
                }

                cout << "\nDigite o numero da conta: ";
                cin >> numero;

                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numero) {
                        posicao = i;
                    }
                }

                if (posicao == -1) {
                    cout << "Conta nao encontrada.\n";
                } else if (!contaAtiva[posicao]) {
                    cout << "A conta esta inativa. Ative-a para alterar o tipo.\n";
                } else {
                    cout << "Novo tipo da conta:\n";
                    cout << "1 - Corrente\n";
                    cout << "2 - Poupanca\n";
                    cout << "Escolha: ";
                    cin >> novoTipo;

                    while (novoTipo != 1 && novoTipo != 2) {
                        cout << "Tipo invalido. Digite 1 ou 2: ";
                        cin >> novoTipo;
                    }

                    tipoConta[posicao] = novoTipo;
                    cout << "Tipo da conta alterado com sucesso.\n";
                }

                break;
            }

            case 5: {
                int numero;
                int posicao = -1;

                if (quantidadeContas == 0) {
                    cout << "\nNenhuma conta cadastrada.\n";
                    break;
                }

                cout << "\nDigite o numero da conta: ";
                cin >> numero;

                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numero) {
                        posicao = i;
                    }
                }

                if (posicao == -1) {
                    cout << "Conta nao encontrada.\n";
                } else {
                    if (contaAtiva[posicao]) {
                        contaAtiva[posicao] = false;
                        cout << "Conta desativada com sucesso.\n";
                    } else {
                        contaAtiva[posicao] = true;
                        cout << "Conta ativada com sucesso.\n";
                    }
                }

                break;
            }

            case 6:
                cout << "\nPrograma encerrado.\n";
                break;

            default:
                cout << "\nOpcao invalida. Digite um numero de 1 a 6.\n";
        }

    } while (opcao != 6);

    return 0;
}