/*
 *   +---+------------------+-------------------+
 *   | n | Movimentos (cont)| 2^n - 1 (esperado)|
 *   +---+------------------+-------------------+
 *   | 1 |        1         |        1          |
 *   | 2 |        3         |        3          |
 *   | 3 |        7         |        7          |
 *   | 4 |       15         |       15          |
 *   | 5 |       31         |       31          |
 *   | 6 |       63         |       63          |
 *   +---+------------------+-------------------+
 */
#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>

static long long contador = 0;

void hanoi(int n, char origem, char destino, char auxiliar) {
    if (n == 1) {
        contador++;
        return;
    }
    hanoi(n - 1, origem, auxiliar, destino);
    contador++;
    hanoi(n - 1, auxiliar, destino, origem);
}

int main(void) {
    printf("+---+------------+------------+\n");
    printf("| n | Movimentos | 2^n - 1    |\n");
    printf("+---+------------+------------+\n");
    for (int n = 1; n <= 6; n++) {
        contador = 0;
        hanoi(n, 'A', 'C', 'B');
        long long esperado = (1LL << n) - 1LL;
        printf("| %d | %10lld | %10lld |\n", n, contador, esperado);
    }
    printf("+---+------------+------------+\n");
    return 0;
}
