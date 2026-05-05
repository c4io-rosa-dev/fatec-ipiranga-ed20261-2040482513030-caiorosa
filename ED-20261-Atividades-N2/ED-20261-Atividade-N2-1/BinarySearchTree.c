#ifndef MINHABIB_H
#define MINHABIB_H
#include <stdio.h>

typedef struct No {
int valor;
struct No *esq;
struct No *dir;
} No;

// Função principal de diagnóstico da atividade
void analisar_arvore(No* raiz, int valorBusca);

// Funções auxiliares obrigatórias para organização
void imprimir_nos_internos(No* raiz){
     if (raiz == NULL) return;
    if (raiz->esq != NULL || raiz->dir != NULL) {
        printf("%d ", raiz->valor);
    }
    imprimir_nos_internos(raiz->esq);
    imprimir_nos_internos(raiz->dir);
}

void imprimir_folhas(No* raiz){
    if (raiz == NULL) return;
    if (raiz->esq == NULL && raiz->dir == NULL) {
        printf("%d ", raiz->valor);
    }
    imprimir_folhas(raiz->esq);
    imprimir_folhas(raiz->dir);
}

void imprimir_niveis(No* raiz, int nivel_atual){
    if (raiz == NULL) return;
    printf("Nivel %d -> No %d\n", nivel_atual, raiz->valor);
    imprimir_niveis(raiz->esq, nivel_atual + 1);
    imprimir_niveis(raiz->dir, nivel_atual + 1);
}

int calcular_altura(No* no){
    if (no == NULL) return -1;
    int alt_esq = calcular_altura(no->esq);
    int alt_dir = calcular_altura(no->dir);
    return 1 + (alt_esq > alt_dir ? alt_esq : alt_dir);
}

int calcular_profundidade(No* raiz, int valor, int profundidade_atual){
    if (raiz == NULL) return -1;
    if (raiz->valor == valor) return profundidade_atual;
    if (valor < raiz->valor) {
        return calcular_profundidade(raiz->esq, valor, profundidade_atual + 1);
    }
    return calcular_profundidade(raiz->dir, valor, profundidade_atual + 1);
}

void imprimir_ancestrais(No* raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor) return;

    if (valor < raiz->valor) {
        imprimir_ancestrais(raiz->esq, valor);
    } else {
        imprimir_ancestrais(raiz->dir, valor);
    }
    printf("%d ", raiz->valor);
}

void imprimir_descendentes(No* no) {
    if (no == NULL) return;
    if (no->esq != NULL) {
        printf("%d ", no->esq->valor);
        imprimir_descendentes(no->esq);
    }
    if (no->dir != NULL) {
        printf("%d ", no->dir->valor);
        imprimir_descendentes(no->dir);
    }
}

void analisar_arvore(No* raiz, int valorBusca) {
    if (raiz == NULL) {
        printf("Arvore vazia. Nada a analisar.\n");
        return;
    }

    /* ---------- FASE A: DIAGNOSTICO GERAL ---------- */
    printf("\n=================================================\n");
    printf("       FASE A - DIAGNOSTICO GERAL DA ARVORE       \n");
    printf("=================================================\n");

    printf("\n>> Raiz: %d  (endereco: %p)\n", raiz->valor, (void*)raiz);

    printf("\n>> Nos Internos (grau >= 1): ");
    imprimir_nos_internos(raiz);
    printf("\n");

    printf("\n>> Nos Externos / Folhas (grau 0): ");
    imprimir_folhas(raiz);
    printf("\n");

    printf("\n>> Exibicao por Niveis (Nivel 0 = raiz):\n");
    imprimir_niveis(raiz, 0);

    /* ---------- FASE B: DIAGNOSTICO ESPECIFICO ---------- */
    printf("\n=================================================\n");
    printf("   FASE B - DIAGNOSTICO ESPECIFICO (valor = %d)   \n", valorBusca);
    printf("=================================================\n");

    No* alvo = raiz;
    while (alvo != NULL && alvo->valor != valorBusca) {
        if (valorBusca < alvo->valor) {
            alvo = alvo->esq;
        } else {
            alvo = alvo->dir;
        }
    }

    if (alvo == NULL) {
        printf("\n[!] Valor %d nao foi encontrado na arvore.\n", valorBusca);
        return;
    }

    printf("\n>> No encontrado: %d  (endereco: %p)\n",
           alvo->valor, (void*)alvo);

    int grau = 0;
    if (alvo->esq != NULL) grau++;
    if (alvo->dir != NULL) grau++;
    printf("\n>> Grau do No: %d filho(s)", grau);
    if (grau == 0) printf("  -> trata-se de uma FOLHA");
    else if (grau == 1) printf("  -> no com apenas um filho");
    else printf("  -> no completo (dois filhos)");
    printf("\n");

    printf("\n>> Ancestrais (do no ate a raiz): ");
    if (alvo == raiz) {
        printf("(o no buscado e a propria raiz - nao ha ancestrais)");
    } else {
        imprimir_ancestrais(raiz, valorBusca);
    }
    printf("\n");

    printf("\n>> Descendentes: ");
    if (grau == 0) {
        printf("(nenhum - e uma folha)");
    } else {
        imprimir_descendentes(alvo);
    }
    printf("\n");

    printf("\n>> Altura do no: %d (arestas ate a folha mais distante abaixo)\n",
           calcular_altura(alvo));

    printf("\n>> Profundidade do no: %d (arestas da raiz principal ate este no)\n",
           calcular_profundidade(raiz, valorBusca, 0));

    /* ---------- FASE C: EXTRACAO DE SUBARVORE ---------- */
    printf("\n=================================================\n");
    printf("   FASE C - SUBARVORE COM RAIZ EM %d              \n", valorBusca);
    printf("=================================================\n");

    printf("\n>> Nova raiz da sub-arvore: %d\n", alvo->valor);

    printf("\n>> Nos Internos da sub-arvore: ");
    imprimir_nos_internos(alvo);
    printf("\n");

    printf("\n>> Folhas da sub-arvore: ");
    imprimir_folhas(alvo);
    printf("\n");

    printf("\n>> Niveis da sub-arvore (Nivel 0 = no buscado):\n");
    imprimir_niveis(alvo, 0);
}

#endif