#include <stdio.h>

void hanoi(int n, char origem, char destino, char auxiliar) {
    if (n == 1) {
        printf("Mover disco 1 de %c para %c\n", origem, destino);
        return;
    }
    hanoi(n - 1, origem, auxiliar, destino);
    printf("Mover disco %d de %c para %c\n", n, origem, destino);
    hanoi(n - 1, auxiliar, destino, origem);
}

int main(void) {
    int testes[] = {1, 3, 4};
    int q = (int)(sizeof(testes) / sizeof(testes[0]));
    for (int i = 0; i < q; i++) {
        printf("\n========== n = %d ==========\n", testes[i]);
        hanoi(testes[i], 'A', 'C', 'B');
    }
    return 0;
}
