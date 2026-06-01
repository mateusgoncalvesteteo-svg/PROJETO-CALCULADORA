#include <iostream> // cin e cout
#include <cmath> // operacoes matematicas
#include <cctype> // tolower e outros
#include <limits> // apenas numeros nao letras
#include <string>//vou usar string
#include <vector>//para criar um historico
#include <sstream>//importar texto para o historico

using namespace std;//estou mais acostumado a usar assim.

//funçao para cada operaçao matematica
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

    if (num2 != 0) {
        return num1 / num2;

    } else {
        cout << "Erro divisao por 0!\n";
        return 0;
    }
}

double potenciacao(double base, double expoente) {

    // em vez de deixar: digite o primeiro numero e o segundo
    // irei deixar:  digite a base e o expoente

    return pow(base, expoente);
}

double logaritmo(double num1, double num2) {

    // log(base) do logaritmando

    if (num1 <= 0 || num1 == 1 || num2 <= 0) {
        cout << "Logaritmo invalido\n";
        return 0;
    }

    return log(num2) / log(num1);
}

double lerNumero() {

    double num;

    while (true) {

        if (cin >> num) {
            return num;

        } else {

            cout << "Digite apenas numeros: ";

            cin.clear();
            
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );
        }
    }
}

void pedirNumeros(char operacao, double &num1, double &num2) {

    // funcao criada para evitar muitos ifs na main()

    switch (operacao) {

        case '5': // potenciacao

            cout << "Digite a base: ";
            num1 = lerNumero();

            cout << "Digite o expoente: ";
            num2 = lerNumero();

            break;

        case '6': // logaritmo

            cout << "Digite a base: ";
            num1 = lerNumero();

            cout << "Digite o logaritmando: ";
            num2 = lerNumero();

            break;

        default: // demais operacoes

            cout << "Digite o primeiro numero: ";
            num1 = lerNumero();

            cout << "Digite o segundo numero: ";
            num2 = lerNumero();

            break;
    }
}

double operacao(char op, double num1, double num2) {

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
            return 0;
    }
}

void limparTela() {//funçao de limpar a tela

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    
}


char menu() {//funcao menu

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
        cout << "8. Historico\n";//historico ira aparecere no menu

        cout << "Opcao: ";
        cin >> operacao;

        if (operacao < '1' || operacao > '8') {//todos os char do menu
            cout << "Apenas numeros da lista!\n";//funcionara como uma validaçao
        }

    } while (operacao < '1' || operacao > '8');

    return operacao;
}

void mostrarHistorico(vector<string>& historico) {//funcao mostrar historico

    cout << "\n========== HISTORICO ==========\n";

    if (historico.empty()) {

        cout << "Ainda nao houve nenhuma operacao.\n";//caso nao tenha sido feito nehuma operaçao

    } else {

        for (int i = 0; i < historico.size(); i++) {
    //para mostrar desde o indice 0 do vetor até o ultimo, todas as operaçoes feitas
            cout << i + 1 << ". " << historico[i] << endl;
        }
    }

    cout << "===============================\n";//uma estetica mais amigavel
}

void salvarHistorico(vector<string>& historico, string operacao) {//funçao para salvar o historico

    historico.push_back(operacao);//push_back vai estar armazenando tudo o que acontece
}

int main() {//funçao principal


    double num1, num2, resultado;

    char opcao;
    char continuar;
    
    vector<string> historico;

    do {

        limparTela();
        //minha maquina usa o sistema operacional do windows 11, mas eu adicionei um else na funçao pra caso tenha linux tbm ;)
        
        opcao = menu();

        if (opcao == '7') {
            break;
        }
        
        if (opcao == '8') {
        mostrarHistorico(historico);

        cout << "\nPressione ENTER para voltar ao menu...";//agora ele nao aparece e some instataneamente
    
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();

        continue;
        }

        // antes aqui existiam varios ifs
        // agora apenas uma funcao

        pedirNumeros(opcao, num1, num2);

        //antes existia um swicht(op) aqui
        resultado = operacao(opcao, num1, num2);
        
        stringstream ss;

        if (opcao == '6') {

        ss << "log base " << num1 << " de " << num2 << " = " << resultado;//esse caso é especifico para logaritmos.

        } else {

            char opChar;

            switch (opcao) {//quano o historico for selecionado , vai aparecer um historico bem mais bonito, do que so numeros soltos.
                case '1': opChar = '+'; break;
                case '2': opChar = '-'; break;
                case '3': opChar = '*'; break;
                case '4': opChar = '/'; break;
                case '5': opChar = '^'; break;
            }

        ss << num1 << " " << opChar << " " << num2 << " = " << resultado;
        }

        salvarHistorico(historico, ss.str());//passou aqui e quis rodar denovo fica salvo

        cout << "Resultado: " << resultado << endl;

        // validacao do char (s/n)

        do {

            cout << "Deseja rodar o codigo novamente? (s/n): ";
            cin >> continuar;

            continuar = tolower(continuar);

            if (continuar != 's' && continuar != 'n') {

                cout << "Entrada invalida!"
                     << " Digite apenas 's' ou 'n'.\n";
            }

        } while (continuar != 's' && continuar != 'n');

    } while (continuar == 's');

    cout << "Programa encerrado...\n";

    return 0;
}
