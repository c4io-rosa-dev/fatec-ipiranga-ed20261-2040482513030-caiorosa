#include <stdio.h>

int main(void) {
    int v[] = {10, 20, 30, 40, 50};
    int n   = (int)(sizeof(v) / sizeof(v[0]));

    printf("==== (a) Elementos e enderecos ====\n");
    int *p   = v;
    int *fim = v + n;
    while (p < fim) {
        printf("valor = %2d  | endereco = %p\n",
               *p,            /* *p desreferencia: acessa o valor da posicao       */
               (void*)p);     /*  p ja eh ponteiro (endereco), nao precisa de &    */
        p++;
    }

    int soma = 0;
    for (p = v; p < fim; p++) {
        soma += *p;           /* *p le o valor apontado por p sem usar [] */
    }
    printf("\n==== (b) Soma dos elementos ====\n");
    printf("soma = %d\n", soma);

    int *esq = v;             /* &v[0] expresso como ponteiro (inicio do vetor)    */
    int *dir = v + n - 1;     /* &v[n-1] obtido por aritmetica de ponteiros        */
    while (esq < dir) {
        int aux = *esq;       /* *esq le o valor da posicao da esquerda            */
        *esq = *dir;          /* *esq escreve: sobrescreve esquerda com a direita  */
        *dir = aux;           /* *dir escreve: sobrescreve direita com aux         */
        esq++;
        dir--;
    }

    printf("\n==== (c) Vetor invertido in-place ====\n");
    for (p = v; p < fim; p++) {
        printf("valor = %2d  | endereco = %p\n", *p, (void*)p); /* *p le, p eh end */
    }
    return 0;
}
