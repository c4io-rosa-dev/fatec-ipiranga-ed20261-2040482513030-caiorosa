/*
 * Inserts em sequencia: 50, 30, 70, 20, 40, 60, 80, 10, 25, 45, 65
 *
 * ABB resultante:
 *
 *                       50
 *                      /  \
 *                    30    70
 *                   /  \   / \
 *                 20   40 60  80
 *                / \    \  \
 *              10  25   45  65
 *
 * Verificacao manual (3 nos):
 *   no 50  -> profundidade 0 | altura 3 | grau 2
 *   no 30  -> profundidade 1 | altura 2 | grau 2
 *   no 10  -> profundidade 3 | altura 0 | grau 0  (folha)
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dado;
    struct No *esq;
    struct No *dir;
} No;

No* inserir(No *raiz, int valor) {
    if (raiz == NULL) {
        No *novo = (No*) malloc(sizeof(No));
        novo->dado = valor;
        novo->esq  = NULL;
        novo->dir  = NULL;
        return novo;
    }
    if (valor < raiz->dado)
        raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->dado)
        raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}

int alturaNo(No *no) {
    if (no == NULL) return -1;
    int altE = alturaNo(no->esq);
    int altD = alturaNo(no->dir);
    return 1 + (altE > altD ? altE : altD);
}

int profundidadeNo(No *raiz, int valor, int prof) {
    if (raiz == NULL) return -1;
    if (raiz->dado == valor) return prof;
    if (valor < raiz->dado)
        return profundidadeNo(raiz->esq, valor, prof + 1);
    return profundidadeNo(raiz->dir, valor, prof + 1);
}

int grauNo(No *no) {
    if (no == NULL) return -1;
    int g = 0;
    if (no->esq != NULL) g++;
    if (no->dir != NULL) g++;
    return g;
}

static No* buscarNo(No *raiz, int valor) {
    if (raiz == NULL) return NULL;
    if (raiz->dado == valor) return raiz;
    if (valor < raiz->dado) return buscarNo(raiz->esq, valor);
    return buscarNo(raiz->dir, valor);
}

static void emOrdemGrau(No *raiz) {
    if (raiz == NULL) return;
    emOrdemGrau(raiz->esq);
    printf("  no %2d -> grau %d\n", raiz->dado, grauNo(raiz));
    emOrdemGrau(raiz->dir);
}

static void liberarArvore(No *raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

int main(void) {
    int valores[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 45, 65};
    int n = (int)(sizeof(valores) / sizeof(valores[0]));

    No *raiz = NULL;
    for (int i = 0; i < n; i++)
        raiz = inserir(raiz, valores[i]);

    printf("==== (a) Altura dos nos ====\n");
    int alvos_alt[] = {50, 30, 70, 20, 10};
    for (int i = 0; i < 5; i++) {
        No *no = buscarNo(raiz, alvos_alt[i]);
        printf("  altura(%2d) = %d\n", alvos_alt[i], alturaNo(no));
    }

    printf("\n==== (b) Profundidade dos nos ====\n");
    int alvos_prof[] = {50, 30, 70, 45, 10};
    for (int i = 0; i < 5; i++)
        printf("  profundidade(%2d) = %d\n",
               alvos_prof[i], profundidadeNo(raiz, alvos_prof[i], 0));

    printf("\n==== (c) Grau de cada no (percurso em-ordem) ====\n");
    emOrdemGrau(raiz);

    printf("\n==== (d) Altura total da arvore ====\n");
    printf("  altura(raiz=%d) = %d\n", raiz->dado, alturaNo(raiz));

    liberarArvore(raiz);
    return 0;
}
