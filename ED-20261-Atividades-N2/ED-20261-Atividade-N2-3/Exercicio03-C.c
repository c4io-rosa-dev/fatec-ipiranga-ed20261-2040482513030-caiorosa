#include <stdio.h>

static void indentar(int nivel) {
    for (int i = 0; i < nivel * 2; i++) putchar(' ');
}

void hanoi(int n, char origem, char destino, char auxiliar, int nivel) {
    if (n == 1) {
        indentar(nivel);
        printf("[nivel %d] Mover disco 1 de %c para %c\n", nivel, origem, destino);
        return;
    }
    hanoi(n - 1, origem, auxiliar, destino, nivel + 1);

    indentar(nivel);
    printf("[nivel %d] Mover disco %d de %c para %c\n", nivel, n, origem, destino);

    hanoi(n - 1, auxiliar, destino, origem, nivel + 1);
}

int main(void) {
    int testes[] = {1, 3, 4};
    int q = (int)(sizeof(testes) / sizeof(testes[0]));
    for (int i = 0; i < q; i++) {
        printf("\n========== n = %d (chamada inicial: nivel 0) ==========\n", testes[i]);
        hanoi(testes[i], 'A', 'C', 'B', 0);
    }
    return 0;
}
