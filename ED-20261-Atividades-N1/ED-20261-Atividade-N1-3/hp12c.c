#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

typedef struct Pilha {
    double T;
    double Z;
    double Y;
    double X;
} Pilha;

Pilha hp12c;
char expressao[300];
char *token;
int contador = 0;

void inicializarPilha() {
    hp12c.T = 0.0;
    hp12c.Z = 0.0;
    hp12c.Y = 0.0;
    hp12c.X = 0.0;
    printf("Todos os registradores foram zerados com sucesso.\n");
}

void push(double registrador) {
    hp12c.T = hp12c.Z;
    hp12c.Z = hp12c.Y;
    hp12c.Y = hp12c.X;
    hp12c.X = registrador;
}

void operacao(char operador) {
    switch(operador) {
        case '+':
            hp12c.X = hp12c.Y + hp12c.X;
            hp12c.Y = hp12c.Z;
            hp12c.Z = hp12c.T;
           
           printf("Operação de adição realizada com sucesso! O resultado é: %.2f", hp12c.X);
           break;
        
        case '-':
            hp12c.X = hp12c.Y - hp12c.X;
            hp12c.Y = hp12c.Z;
            hp12c.Z = hp12c.T;
           
           printf("Operação de subtração realizada com sucesso! O resultado é: %.2f", hp12c.X);
           break;

        case '*':
            hp12c.X = hp12c.Y * hp12c.X;
            hp12c.Y = hp12c.Z;
            hp12c.Z = hp12c.T;
           
           printf("Operação de multiplicação realizada com sucesso! O resultado é: %.2f", hp12c.X);
           break;

        case '/':
            if (hp12c.X == 0) {
                printf("Erro na operação. Algum dos valores inseridos não são válidos.");
            } else {
                hp12c.X = hp12c.Y / hp12c.X;
                hp12c.Y = hp12c.Z;
                hp12c.Z = hp12c.T;
                printf("Operação de divisão realizada com sucesso! O resultado é: %.2f", hp12c.X);
            }
           break;

        default:
            printf("Operador incorreto. Por favor, selecione um operador válido.");
    }
}

void exibirPilha() {
    printf("T: %.2f\n", hp12c.T);
    printf("Z: %.2f\n", hp12c.Z);
    printf("Y: %.2f\n", hp12c.Y);
    printf("X: %.2f\n \n", hp12c.X);
}

int main() {
    printf("Bem vindo a calculadora HP12C!\n");
    printf("\n Informe a expressão que deseja calcular: \n");
    fgets(expressao, 256, stdin);
    token = strtok(expressao, " \n");
    while (token != NULL) {
        if (strlen(token) == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')) {
            if (contador < 2) {
                printf("\n Não há operandos suficiente para realizar a operação com êxito. Encerrando...\n");
                return 1;
            }
            operacao(token[0]);
            exibirPilha();
            contador --;
        } else {
            push(atof(token));
            exibirPilha();
            contador ++;
        }
        token = strtok(NULL, " \n");
    }
    printf("\n O resultado da expressão algébrica é: %.2f", hp12c.X);
}