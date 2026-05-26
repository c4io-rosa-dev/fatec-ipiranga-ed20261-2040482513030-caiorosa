#include <stdio.h>

float calcularMedia(float *vet, int n) {
    float soma = 0.0f;
    float *fim = vet + n;
    while (vet < fim) {
        soma += *vet;
        vet++;
    }
    return soma / (float)n;
}

void encontrarExtremos(float *vet, int n, float *maior, float *menor) {
    *maior = *vet;
    *menor = *vet;
    float *fim = vet + n;
    vet++;
    while (vet < fim) {
        if (*vet > *maior) *maior = *vet;
        if (*vet < *menor) *menor = *vet;
        vet++;
    }
}

void normalizar(float *vet, int n) {
    float max  = *vet;
    float *p   = vet + 1;
    float *fim = vet + n;
    while (p < fim) {
        if (*p > max) max = *p;
        p++;
    }
    if (max == 0.0f) return;

    p = vet;
    while (p < fim) {
        *p = *p / max;
        p++;
    }
}

void imprimirVetor(float *vet, int n, const char *titulo) {
    printf("%s [", titulo);
    float *fim = vet + n;
    while (vet < fim) {
        printf(" %.3f", *vet);
        vet++;
    }
    printf(" ]\n");
}

int main(void) {
    float notas[] = {7.5f, 3.2f, 9.8f, 6.0f, 5.5f, 8.1f};
    int n = (int)(sizeof(notas) / sizeof(notas[0]));

    imprimirVetor(notas, n, "Vetor original   :");

    float media = calcularMedia(notas, n);
    float maior, menor;
    encontrarExtremos(notas, n, &maior, &menor);

    printf("\nMedia : %.3f\n", media);
    printf("Maior : %.3f\n", maior);
    printf("Menor : %.3f\n", menor);

    normalizar(notas, n);
    imprimirVetor(notas, n, "\nVetor normalizado:");

    /*
     * Por que o vetor 'notas' do main foi alterado por normalizar()?
     * Quando passamos o nome do array para uma funcao, ele decai em float*,
     * ou seja, a funcao recebe o ENDERECO do primeiro elemento - nao uma
     * copia do vetor. Toda escrita via *p dentro de normalizar() ocorre na
     * mesma regiao de memoria do vetor declarado no main, por isso as
     * alteracoes persistem apos o retorno da funcao.
     */
    return 0;
}
