/*
 * Comparacao do numero de chamadas (incluindo a chamada inicial):
 *   +-------+--------------------+----------------+
 *   | caso  | potenciaRapida     | ingenua O(n)   |
 *   +-------+--------------------+----------------+
 *   | 2^10  |  6 chamadas        | 11 chamadas    |
 *   | 3^7   |  6 chamadas        |  8 chamadas    |
 *   | 5^0   |  1 chamada         |  1 chamada     |
 *   | 7^12  |  6 chamadas        | 13 chamadas    |
 *   +-------+--------------------+----------------+
 * Mesmo no pior caso (alternancia par/impar), a rapida fica em
 * ~2*log2(n), enquanto a ingenua executa exatamente n+1 chamadas.
 */
#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>

static int chamadas = 0;

long long potenciaRapida(long long base, int exp) {
    chamadas++;
    if (exp == 0) return 1LL;                          /* caso base: b^0 = 1     */
    if (exp % 2 == 0) {
        long long meio = potenciaRapida(base, exp / 2);
        return meio * meio;                            /* caso recursivo par     */
    }
    return base * potenciaRapida(base, exp - 1);       /* caso recursivo impar   */
}

static int chamadas_ing = 0;
long long potenciaIngenua(long long base, int exp) {
    chamadas_ing++;
    if (exp == 0) return 1LL;                          /* caso base: b^0 = 1     */
    return base * potenciaIngenua(base, exp - 1);      /* caso recursivo unico   */
}

static void avaliar(long long base, int exp) {
    chamadas = 0;
    long long r1 = potenciaRapida(base, exp);
    int c_rap = chamadas;

    chamadas_ing = 0;
    long long r2 = potenciaIngenua(base, exp);
    int c_ing = chamadas_ing;

    printf("%lld^%-2d = %-12lld | rapida: %2d chamadas | ingenua: %2d chamadas\n",
           base, exp, r1, c_rap, c_ing);
    if (r1 != r2) printf("  [!] divergencia entre os algoritmos\n");
}

int main(void) {
    avaliar(2, 10);
    avaliar(3,  7);
    avaliar(5,  0);
    avaliar(7, 12);
    return 0;
}
