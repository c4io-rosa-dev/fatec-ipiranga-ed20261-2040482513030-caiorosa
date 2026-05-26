#include <stdio.h>

static int chamadas = 0;

int buscaBinaria(int *vet, int inicio, int fim, int alvo) {
    chamadas++;
    if (inicio > fim) return -1;                /* caso base 1: intervalo vazio   */
    int meio = inicio + (fim - inicio) / 2;
    if (vet[meio] == alvo) return meio;         /* caso base 2: encontrou o alvo  */
    if (alvo < vet[meio])
        return buscaBinaria(vet, inicio, meio - 1, alvo);   /* caso recursivo esq */
    return buscaBinaria(vet, meio + 1, fim, alvo);          /* caso recursivo dir */
}

static void buscar_e_relatar(int *vet, int n, int alvo) {
    chamadas = 0;
    int idx = buscaBinaria(vet, 0, n - 1, alvo);
    if (idx == -1)
        printf("Alvo %2d -> NAO encontrado | chamadas recursivas: %d\n",
               alvo, chamadas);
    else
        printf("Alvo %2d -> indice %d         | chamadas recursivas: %d\n",
               alvo, idx, chamadas);
}

int main(void) {
    int dados[] = {2, 5, 8, 12, 16, 23, 38, 45, 72, 91};
    int n = (int)(sizeof(dados) / sizeof(dados[0]));

    printf("Vetor (%d elementos ordenados): ", n);
    for (int i = 0; i < n; i++) printf("%d ", dados[i]);
    printf("\n\n");

    buscar_e_relatar(dados, n, 23);
    buscar_e_relatar(dados, n, 50);
    buscar_e_relatar(dados, n,  2);
    buscar_e_relatar(dados, n, 91);
    return 0;
}
