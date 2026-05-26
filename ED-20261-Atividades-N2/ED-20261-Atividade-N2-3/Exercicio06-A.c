#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int dado;
    struct No *esq;
    struct No *dir;
} No;

static No* inserir(No *raiz, int valor) {
    if (raiz == NULL) {
        No *n = (No*) malloc(sizeof(No));
        n->dado = valor; n->esq = NULL; n->dir = NULL;
        return n;
    }
    if (valor < raiz->dado)      raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->dado) raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}
static int alturaNo(No *no) {
    if (no == NULL) return -1;
    int e = alturaNo(no->esq), d = alturaNo(no->dir);
    return 1 + (e > d ? e : d);
}
static int profundidadeNo(No *raiz, int valor, int prof) {
    if (raiz == NULL) return -1;
    if (raiz->dado == valor) return prof;
    if (valor < raiz->dado) return profundidadeNo(raiz->esq, valor, prof + 1);
    return profundidadeNo(raiz->dir, valor, prof + 1);
}
static int grauNo(No *no) {
    if (no == NULL) return -1;
    int g = 0;
    if (no->esq) g++;
    if (no->dir) g++;
    return g;
}
static No* buscarNo(No *raiz, int valor) {
    if (raiz == NULL) return NULL;
    if (raiz->dado == valor) return raiz;
    if (valor < raiz->dado) return buscarNo(raiz->esq, valor);
    return buscarNo(raiz->dir, valor);
}
static void liberarArvore(No *raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

void imprimirAncestral(No *raiz, int valor) {
    if (raiz == NULL) return;
    if (raiz->dado == valor) return;
    printf("%d ", raiz->dado);
    if (valor < raiz->dado) imprimirAncestral(raiz->esq, valor);
    else                    imprimirAncestral(raiz->dir, valor);
}

static void emOrdem(No *no) {
    if (no == NULL) return;
    emOrdem(no->esq);
    printf("%d ", no->dado);
    emOrdem(no->dir);
}

void imprimirDescendentes(No *raiz, int valor) {
    No *no = buscarNo(raiz, valor);
    if (no == NULL) { printf("(no nao encontrado)"); return; }
    emOrdem(no->esq);
    emOrdem(no->dir);
}

int contarDescendentes(No *no) {
    if (no == NULL) return 0;
    int total = 0;
    if (no->esq) total += 1 + contarDescendentes(no->esq);
    if (no->dir) total += 1 + contarDescendentes(no->dir);
    return total;
}

static int ancestrais_buf(No *raiz, int valor, char *buf, int pos) {
    if (raiz == NULL || raiz->dado == valor) return pos;
    pos += sprintf(buf + pos, "%d ", raiz->dado);
    if (valor < raiz->dado) return ancestrais_buf(raiz->esq, valor, buf, pos);
    return ancestrais_buf(raiz->dir, valor, buf, pos);
}
static int emordem_buf(No *no, char *buf, int pos) {
    if (no == NULL) return pos;
    pos = emordem_buf(no->esq, buf, pos);
    pos += sprintf(buf + pos, "%d ", no->dado);
    pos = emordem_buf(no->dir, buf, pos);
    return pos;
}

void relatorioNo(No *raiz, int valor) {
    No *no = buscarNo(raiz, valor);
    if (no == NULL) {
        printf("\n[!] No com valor %d nao existe na arvore.\n", valor);
        return;
    }

    printf("\n+----------------------------------+\n");
    printf("| RELATORIO DO NO: %-15d |\n", valor);
    printf("+----------------------------------+\n");
    printf("| Profundidade : %-17d |\n", profundidadeNo(raiz, valor, 0));
    printf("| Altura       : %-17d |\n", alturaNo(no));
    printf("| Grau         : %-17d |\n", grauNo(no));

    char buf[256] = {0};
    if (no == raiz) sprintf(buf, "(raiz - nenhum)");
    else            ancestrais_buf(raiz, valor, buf, 0);
    printf("| Ancestrais   : %-17s |\n", buf);

    buf[0] = '\0';
    if (grauNo(no) == 0) sprintf(buf, "(folha - nenhum)");
    else { emordem_buf(no->esq, buf, 0); emordem_buf(no->dir, buf, (int)strlen(buf)); }
    printf("| Descendentes : %-17s |\n", buf);

    printf("| Qtd Descend. : %-17d |\n", contarDescendentes(no));
    printf("+----------------------------------+\n");
}

int main(void) {
    int valores[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 45, 65};
    int n = (int)(sizeof(valores) / sizeof(valores[0]));

    No *raiz = NULL;
    for (int i = 0; i < n; i++)
        raiz = inserir(raiz, valores[i]);

    relatorioNo(raiz, 50);
    relatorioNo(raiz, 30);
    relatorioNo(raiz, 10);
    relatorioNo(raiz, 70);
    relatorioNo(raiz, 999);

    liberarArvore(raiz);
    return 0;
}
