#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>
#include <cmath>

using namespace std;

// Paulo Sergio Roque de Sa - Matricula 28612
// INF101 - Sistema Bancario - Etapa 3

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

int buscarConta(int numero) {
    for (int i = 0; i < quantidadeContas; i++) {
        if (numeroConta[i] == numero) {
            return i;
        }
    }

    return -1;
}

bool carregarContas() {
    ifstream arquivo("contas.txt");

    if (!arquivo.is_open()) {
        return true;
    }

    string linha;

    while (getline(arquivo, linha)) {
        if (linha.empty()) {
            continue;
        }

        if (quantidadeContas >= MAX_CONTAS) {
            cout << "O arquivo ultrapassa o limite de contas.\n";
            arquivo.close();
            return false;
        }

        // Troca os separadores para ler os campos por linha.
        for (int i = 0; i < (int)linha.size(); i++) {
            if (linha[i] == ';') {
                linha[i] = '\n';
            }
        }

        stringstream registro(linha);

        int numero;
        string nome;
        string documento;
        int tipo;
        double valor;
        int ativa;

        if (!(registro >> numero)) {
            cout << "Registro invalido em contas.txt.\n";
            arquivo.close();
            return false;
        }

        registro.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(registro, nome);
        getline(registro, documento);

        if (!(registro >> tipo >> valor >> ativa) ||
            numero <= 0 || nome.empty() || documento.empty() ||
            (tipo != 1 && tipo != 2) ||
            !isfinite(valor) || valor < 0 ||
            (ativa != 0 && ativa != 1) ||
            buscarConta(numero) != -1) {
            cout << "Dados invalidos em contas.txt.\n";
            arquivo.close();
            return false;
        }

        int posicao = quantidadeContas;

        numeroConta[posicao] = numero;
        nomeCliente[posicao] = nome;
        cpf[posicao] = documento;
        tipoConta[posicao] = tipo;
        saldo[posicao] = valor;
        contaAtiva[posicao] = (ativa == 1);

        quantidadeContas++;
    }

    bool leituraCorreta = !arquivo.bad();
    arquivo.close();

    return leituraCorreta;
}

bool carregarMovimentacoes() {
    ifstream arquivo("movimentacoes.txt");

    if (!arquivo.is_open()) {
        return true;
    }

    string linha;

    while (getline(arquivo, linha)) {
        if (linha.empty()) {
            continue;
        }

        if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES) {
            cout << "O arquivo ultrapassa o limite de movimentacoes.\n";
            arquivo.close();
            return false;
        }

        for (int i = 0; i < (int)linha.size(); i++) {
            if (linha[i] == ';') {
                linha[i] = ' ';
            }
        }

        stringstream registro(linha);

        int numero;
        char tipo;
        double valor;

        if (!(registro >> numero >> tipo >> valor) ||
            buscarConta(numero) == -1 ||
            (tipo != 'D' && tipo != 'S') ||
            !isfinite(valor) || valor <= 0) {
            cout << "Registro invalido em movimentacoes.txt.\n";
            arquivo.close();
            return false;
        }

        contaMovimentacao[quantidadeMovimentacoes] = numero;
        tipoMovimentacao[quantidadeMovimentacoes] = tipo;
        valorMovimentacao[quantidadeMovimentacoes] = valor;

        quantidadeMovimentacoes++;
    }

    bool leituraCorreta = !arquivo.bad();
    arquivo.close();

    return leituraCorreta;
}

bool salvarContas() {
    ofstream arquivo("contas.txt");

    if (!arquivo.is_open()) {
        cout << "Nao foi possivel abrir contas.txt para gravacao.\n";
        return false;
    }

    arquivo << fixed << setprecision(2);

    for (int i = 0; i < quantidadeContas; i++) {
        arquivo << numeroConta[i] << ";"
                << nomeCliente[i] << ";"
                << cpf[i] << ";"
                << tipoConta[i] << ";"
                << saldo[i] << ";"
                << contaAtiva[i] << "\n";
    }

    arquivo.close();

    if (arquivo.fail()) {
        cout << "Erro ao salvar contas.txt.\n";
        return false;
    }

    return true;
}

bool salvarMovimentacoes() {
    ofstream arquivo("movimentacoes.txt");

    if (!arquivo.is_open()) {
        cout << "Nao foi possivel abrir movimentacoes.txt para gravacao.\n";
        return false;
    }

    arquivo << fixed << setprecision(2);

    // Grava tambem os registros carregados de execucoes anteriores.
    for (int i = 0; i < quantidadeMovimentacoes; i++) {
        arquivo << contaMovimentacao[i] << ";"
                << tipoMovimentacao[i] << ";"
                << valorMovimentacao[i] << "\n";
    }

    arquivo.close();

    if (arquivo.fail()) {
        cout << "Erro ao salvar movimentacoes.txt.\n";
        return false;
    }

    return true;
}

void registrarMovimentacao(int numero, char tipo, double valor) {
    contaMovimentacao[quantidadeMovimentacoes] = numero;
    tipoMovimentacao[quantidadeMovimentacoes] = tipo;
    valorMovimentacao[quantidadeMovimentacoes] = valor;

    quantidadeMovimentacoes++;
}

int main() {
    cout << fixed << setprecision(2);

    if (!carregarContas() || !carregarMovimentacoes()) {
        cout << "Confira os arquivos antes de executar novamente.\n";
        return 1;
    }

    cout << "Contas carregadas: " << quantidadeContas << "\n";
    cout << "Movimentacoes carregadas: "
         << quantidadeMovimentacoes << "\n";
    cout << "Use ponto para os centavos. Exemplo: 25.50\n";

    int opcao = 0;

    do {
        cout << "\n--- BANCO PAULO ---\n";
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
            if (cin.eof()) {
                break;
            }

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Digite uma opcao numerica.\n";
            continue;
        }

        bool alterouContas = false;
        bool alterouMovimentacoes = false;

        switch (opcao) {
            case 1: {
                if (quantidadeContas >= MAX_CONTAS) {
                    cout << "Limite de contas atingido.\n";
                    break;
                }

                int numero;
                int tipo;
                string nome;
                string documento;
                double valor;

                cout << "Numero da conta: ";
                if (!(cin >> numero)) break;

                if (numero <= 0) {
                    cout << "O numero deve ser maior que zero.\n";
                    break;
                }

                if (buscarConta(numero) != -1) {
                    cout << "Esse numero de conta ja existe.\n";
                    break;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Nome do cliente: ";
                getline(cin, nome);

                cout << "CPF: ";
                getline(cin, documento);

                if (nome.find_first_not_of(" \t\r") == string::npos ||
                    documento.find_first_not_of(" \t\r") == string::npos ||
                    nome.find(';') != string::npos ||
                    documento.find(';') != string::npos) {
                    cout << "Preencha nome e CPF sem usar ponto e virgula.\n";
                    break;
                }

                cout << "Tipo (1 - Corrente / 2 - Poupanca): ";
                if (!(cin >> tipo)) break;

                if (tipo != 1 && tipo != 2) {
                    cout << "Tipo invalido.\n";
                    break;
                }

                cout << "Saldo inicial: ";
                if (!(cin >> valor)) break;

                if (!isfinite(valor) || valor < 0) {
                    cout << "Saldo inicial invalido.\n";
                    break;
                }

                valor = round(valor * 100.0) / 100.0;

                int posicao = quantidadeContas;

                numeroConta[posicao] = numero;
                nomeCliente[posicao] = nome;
                cpf[posicao] = documento;
                tipoConta[posicao] = tipo;
                saldo[posicao] = valor;
                contaAtiva[posicao] = true;

                quantidadeContas++;
                alterouContas = true;

                cout << "Conta cadastrada.\n";
                break;
            }

            case 2: {
                if (quantidadeContas == 0) {
                    cout << "Nenhuma conta cadastrada.\n";
                    break;
                }

                for (int i = 0; i < quantidadeContas; i++) {
                    cout << "\nConta: " << numeroConta[i] << "\n";
                    cout << "Cliente: " << nomeCliente[i] << "\n";
                    cout << "Saldo: R$ " << saldo[i] << "\n";
                    cout << "Situacao: "
                         << (contaAtiva[i] ? "Ativa" : "Inativa")
                         << "\n";
                }

                break;
            }

            case 3:
            case 4:
            case 5:
            case 7:
            case 8:
            case 9: {
                int numero;

                cout << "Numero da conta: ";
                if (!(cin >> numero)) break;

                int posicao = buscarConta(numero);

                if (posicao == -1) {
                    cout << "Conta nao encontrada.\n";
                    break;
                }

                if (opcao == 3) {
                    cout << "\nNumero: " << numeroConta[posicao] << "\n";
                    cout << "Nome: " << nomeCliente[posicao] << "\n";
                    cout << "CPF: " << cpf[posicao] << "\n";
                    cout << "Tipo: "
                         << (tipoConta[posicao] == 1
                             ? "Corrente" : "Poupanca")
                         << "\n";
                    cout << "Saldo: R$ " << saldo[posicao] << "\n";
                    cout << "Situacao: "
                         << (contaAtiva[posicao] ? "Ativa" : "Inativa")
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
                    if (!(cin >> valor)) break;

                    if (!isfinite(valor) || valor <= 0) {
                        cout << "O valor deve ser positivo.\n";
                        break;
                    }

                    valor = round(valor * 100.0) / 100.0;

                    if (valor < 0.01) {
                        cout << "O valor minimo e R$ 0.01.\n";
                        break;
                    }

                    if (opcao == 5 && valor > saldo[posicao]) {
                        cout << "Saldo insuficiente.\n";
                        break;
                    }

                    if (opcao == 4) {
                        saldo[posicao] += valor;
                        registrarMovimentacao(numero, 'D', valor);
                    } else {
                        saldo[posicao] -= valor;
                        registrarMovimentacao(numero, 'S', valor);
                    }

                    saldo[posicao] =
                        round(saldo[posicao] * 100.0) / 100.0;

                    alterouContas = true;
                    alterouMovimentacoes = true;

                    cout << "Saldo atual: R$ " << saldo[posicao] << "\n";

                } else if (opcao == 7) {
                    bool encontrou = false;

                    cout << "\n--- EXTRATO ---\n";
                    cout << "Conta: " << numero << "\n";
                    cout << "Cliente: " << nomeCliente[posicao] << "\n";

                    for (int i = 0; i < quantidadeMovimentacoes; i++) {
                        if (contaMovimentacao[i] == numero) {
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
                    if (!(cin >> novoTipo)) break;

                    if (novoTipo != 1 && novoTipo != 2) {
                        cout << "Tipo invalido.\n";
                        break;
                    }

                    tipoConta[posicao] = novoTipo;
                    alterouContas = true;

                    cout << "Tipo alterado.\n";

                } else {
                    contaAtiva[posicao] = !contaAtiva[posicao];
                    alterouContas = true;

                    cout << (contaAtiva[posicao]
                             ? "Conta ativada.\n"
                             : "Conta desativada.\n");
                }

                break;
            }

            case 6: {
                int numeroOrigem;
                int numeroDestino;
                double valor;

                cout << "Conta de origem: ";
                if (!(cin >> numeroOrigem)) break;

                cout << "Conta de destino: ";
                if (!(cin >> numeroDestino)) break;

                int origem = buscarConta(numeroOrigem);
                int destino = buscarConta(numeroDestino);

                if (origem == -1 || destino == -1) {
                    cout << "Conta de origem ou destino nao encontrada.\n";
                    break;
                }

                if (origem == destino) {
                    cout << "As contas devem ser diferentes.\n";
                    break;
                }

                if (!contaAtiva[origem] || !contaAtiva[destino]) {
                    cout << "As duas contas precisam estar ativas.\n";
                    break;
                }

                if (quantidadeMovimentacoes + 2 > MAX_MOVIMENTACOES) {
                    cout << "Sem espaco para os dois registros.\n";
                    break;
                }

                cout << "Valor da transferencia: ";
                if (!(cin >> valor)) break;

                if (!isfinite(valor) || valor <= 0) {
                    cout << "O valor deve ser positivo.\n";
                    break;
                }

                valor = round(valor * 100.0) / 100.0;

                if (valor < 0.01) {
                    cout << "O valor minimo e R$ 0.01.\n";
                    break;
                }

                if (valor > saldo[origem]) {
                    cout << "Saldo insuficiente.\n";
                    break;
                }

                saldo[origem] =
                    round((saldo[origem] - valor) * 100.0) / 100.0;

                saldo[destino] =
                    round((saldo[destino] + valor) * 100.0) / 100.0;

                registrarMovimentacao(numeroOrigem, 'S', valor);
                registrarMovimentacao(numeroDestino, 'D', valor);

                alterouContas = true;
                alterouMovimentacoes = true;

                cout << "Transferencia realizada.\n";
                cout << "Saldo da origem: R$ " << saldo[origem] << "\n";
                cout << "Saldo do destino: R$ " << saldo[destino] << "\n";

                break;
            }

            case 0:
                cout << "Programa encerrado.\n";
                break;

            default:
                cout << "Opcao invalida.\n";
        }

        if (cin.fail()) {
            if (cin.eof()) {
                break;
            }

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Operacao cancelada.\n";
        }

        // Salva logo depois de cada alteracao.
        bool salvou = true;

        if (alterouContas && !salvarContas()) {
            salvou = false;
        }

        if (alterouMovimentacoes && !salvarMovimentacoes()) {
            salvou = false;
        }

        if (!salvou) {
            cout << "Falha na gravacao. Os arquivos podem estar "
                 << "incompletos ou inconsistentes.\n";
            cout << "O programa sera encerrado. Confira os arquivos.\n";
            return 1;
        }

        if (alterouContas || alterouMovimentacoes) {
            cout << "Dados salvos em arquivo.\n";
        }

    } while (opcao != 0);

    return 0;
}
