#include <iostream> // Entrada e saída de dados
#include <cmath> // Operações matemáticas e NAN
#include <cctype> // Funções como tolower()
#include <limits> // Controle de entrada inválida
#include <string> // Manipulação de strings
#include <vector> // Estrutura para armazenar histórico
#include <sstream> // Conversão de dados para texto formatado

using namespace std;

// ==================== OPERACOES MATEMATICAS ====================

double soma(double num1, double num2) {
    return num1 + num2;
}

double subtracao(double num1, double num2) {
    return num1 - num2;
}

double multiplicacao(double num1, double num2) {
    return num1 * num2;
}

double divisao(double num1, double num2) {
    // Evita divisao por zero
    if (num2 == 0.0) {
        cout << "Erro: divisao por zero!\n";
        return NAN;
    }
    return num1 / num2;
}

double potenciacao(double base, double expoente) {
    // Calcula potencia utilizando a funcao pow()
    return pow(base, expoente);
}

double logaritmo(double base, double logaritmando) {
    // Validacao matematica do logaritmo
    if (base <= 0.0 || base == 1.0 || logaritmando <= 0.0) {
        cout << "Logaritmo invalido!\n";
        return NAN;
    }
    return log(logaritmando) / log(base);
}

// ==================== VALIDACAO DE ENTRADA ====================

double lerNumero() {
    double num;
    while (true) {
        // Retorna o valor caso a entrada seja valida
        if (cin >> num) {
            return num;
        } else {
            cout << "Digite apenas numeros: ";
            // Limpa estado de erro do cin
            cin.clear();
            // Descarta caracteres invalidos restantes
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// ==================== ENTRADA DOS NUMEROS ====================

void pedirNumeros(char operacao, double& num1, double& num2) {
    // Personaliza a entrada dependendo da operacao
    switch (operacao) {
        case '5': // Potenciacao
            cout << "Digite a base: ";
            num1 = lerNumero();
            cout << "Digite o expoente: ";
            num2 = lerNumero();
            break;
        case '6': // Logaritmo
            cout << "Digite a base: ";
            num1 = lerNumero();
            cout << "Digite o logaritmando: ";
            num2 = lerNumero();
            break;
        default: // Demais operacoes
            cout << "Digite o primeiro numero: ";
            num1 = lerNumero();
            cout << "Digite o segundo numero: ";
            num2 = lerNumero();
            break;
    }
}

// ==================== EXECUCAO DAS OPERACOES ====================

double executarOperacao(char op, double num1, double num2) {
    switch (op) {
        case '1':
            return soma(num1, num2);
        case '2':
            return subtracao(num1, num2);
        case '3':
            return multiplicacao(num1, num2);
        case '4':
            return divisao(num1, num2);
        case '5':
            return potenciacao(num1, num2);
        case '6':
            return logaritmo(num1, num2);
        default:
            cout << "Operacao invalida!\n";
            return NAN;
    }
}

// ==================== LIMPEZA DE TELA ====================

void limparTela() {
    // Compatibilidade entre Windows e Linux
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ==================== MENU PRINCIPAL ====================

char menu() {
    char operacao;
    do {
        cout << "================================\n";
        cout << "Calculadora Simples em C++\n";
        cout << "================================\n";
        cout << "Selecione uma operacao:\n";
        cout << "1. Adicao [+]\n";
        cout << "2. Subtracao [-]\n";
        cout << "3. Multiplicacao [*]\n";
        cout << "4. Divisao [/]\n";
        cout << "5. Potencia [^]\n";
        cout << "6. Logaritmo [log]\n";
        cout << "7. Sair\n";
        cout << "8. Historico\n";
        cout << "Opcao: ";
        cin >> operacao;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpa buffer

        // Valida apenas opcoes existentes no menu
        if (operacao < '1' || operacao > '8') {
            cout << "Digite apenas numeros da lista!\n";
        }
    } while (operacao < '1' || operacao > '8');

    return operacao;
}

// ==================== HISTORICO ====================

void mostrarHistorico(const vector<string>& historico) {
    cout << "\n========== HISTORICO ==========\n";
    if (historico.empty()) {
        cout << "Nenhuma operacao realizada.\n";
    } else {
        // Exibe todas as operacoes armazenadas
        for (size_t i = 0; i < historico.size(); i++) {
            cout << i + 1 << ". " << historico[i] << '\n';
        }
    }
    cout << "===============================\n";
}

void salvarHistorico(vector<string>& historico, const string& operacao) {
    // Adiciona nova operacao ao vetor
    historico.push_back(operacao);
}

// ==================== FUNCAO PRINCIPAL ====================

int main() {
    double num1, num2, resultado;
    char opcao;
    char continuar;
    vector<string> historico;

    do {
        limparTela();
        opcao = menu();

        // Encerra o programa
        if (opcao == '7') {
            break;
        }

        // Exibe o historico de operacoes
        if (opcao == '8') {
            mostrarHistorico(historico);
            cout << "\nPressione ENTER para voltar ao menu...";
            cin.get();
            continue;
        }

        pedirNumeros(opcao, num1, num2);
        resultado = executarOperacao(opcao, num1, num2);

        stringstream ss;
        // Formatacao especial para logaritmo
        if (opcao == '6') {
            ss << "log base " << num1 << " de " << num2 << " = " << resultado;
        } else {
            char opChar; 
            // Define simbolo correspondente da operacao
            switch (opcao) {

                case '1': opChar = '+'; break;
                case '2': opChar = '-'; break;
                case '3': opChar = '*'; break;
                case '4': opChar = '/'; break;
                case '5': opChar = '^'; break;
            }

            ss << num1
               << " "
               << opChar
               << " "
               << num2
               << " = "
               << resultado;
        }

        salvarHistorico(historico, ss.str());

        // Verifica se o resultado e invalido
        if (isnan(resultado) || isinf(resultado)) {
            cout << "Nao foi possivel realizar a operacao.\n";
        } else {
            cout << "Resultado: " << resultado << '\n';
        }

        // Validacao da resposta do usuario
        do {
            cout << "Deseja rodar o codigo novamente? (s/n): ";
            cin >> continuar;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continuar = tolower(continuar);

            if (continuar!= 's' && continuar!= 'n') {
                cout << "Entrada invalida! Digite apenas 's' ou 'n'.\n";
            }
        } while (continuar!= 's' && continuar!= 'n');

    } while (continuar == 's');

    cout << "Programa encerrado...\n";
    return 0;
}
