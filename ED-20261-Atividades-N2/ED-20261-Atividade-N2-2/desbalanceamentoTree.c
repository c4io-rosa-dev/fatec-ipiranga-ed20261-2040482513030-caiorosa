#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    int altura;
    struct No *esq;
    struct No *dir;
} No;

static No *criarNo(int valor) {
    No *n = (No *) malloc(sizeof(No));
    n->valor  = valor;
    n->esq    = NULL;
    n->dir    = NULL;
    n->altura = 0;
    return n;
}

int calcularAltura(No *n) {
    if (n == NULL)
        return -1;

    int altEsq = (n->esq == NULL) ? -1 : 1 + calcularAltura(n->esq);
    int altDir = (n->dir == NULL) ? -1 : 1 + calcularAltura(n->dir);

    n->altura = (altEsq > altDir) ? altEsq : altDir;
    return n->altura;
}

int obterFb(No *n) {
    if (n == NULL)
        return 0;

    return calcularAltura(n->esq) - calcularAltura(n->dir);
}

int main(void) {
    No *raiz = criarNo(20);
    raiz->esq = criarNo(10);
    raiz->esq->esq = criarNo(5);
    raiz->esq->esq->esq = criarNo(2);

    printf("Altura da arvore: %d\n", calcularAltura(raiz));
    printf("Fator de balanceamento da raiz (no %d): %d\n",
           raiz->valor, obterFb(raiz));

    free(raiz->esq->esq->esq);
    free(raiz->esq->esq);
    free(raiz->esq);
    free(raiz);

    return 0;
}
